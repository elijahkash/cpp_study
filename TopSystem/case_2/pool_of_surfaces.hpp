/* ************************************************************************** */
/*                                                                            */
/*   Copyright (C) 2020 Ilya Kashnitskiy.                                     */
/*   Contact: elijahkash.code@gmail.com                                       */
/*                                                                            */
/*   This file is part of the 3DEngine project                                */
/*   https://github.com/elijahkash/3DEngine                                   */
/*                                                                            */
/*   GNU General Public License Usage                                         */
/*   This file may be used under the terms of the GNU General                 */
/*   Public license version 3. The licenses are as published by the           */
/*   Free Software Foundation and appearing in the file LICENSE.GPL3          */
/*   included in the packaging of this file. Please review the following      */
/*   information to ensure the GNU General Public License requirements will   */
/*   be met: https://www.gnu.org/licenses/gpl-3.0.html.                       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_POOL_OF_SURFACES_HPP_
#define ENGINE_POOL_OF_SURFACES_HPP_

#include <mutex>
#include <condition_variable>
#include <vector>
#include <stack>
#include <queue>
#include <optional>
#include <memory>

#include "surface.hpp"

// TODO: PoolConfig ???
class PoolOfSurfaces {
 public:
  /* surfacePoolSize can't = 0! */
  explicit PoolOfSurfaces(SurfaceConfig surfConf, unsigned surfacePoolSize);
  // TODO: should mutex lock?
  ~PoolOfSurfaces() = default;

  PoolOfSurfaces(const PoolOfSurfaces&) = delete;
  PoolOfSurfaces(PoolOfSurfaces&&) = delete;

  [[nodiscard]] bool isBusy();
  SurfaceConfig getSurfaceConfig();

  /* await (call interrupt) + notify */
  void setPoolSize(unsigned newPoolSize);
  /* await (call interrupt) + notify */
  void reConfigSurfaces(SurfaceConfig newConfig);

  class RenderingSurface;
  class ExportingSurface;

  /* free -> rendering
   * wait for no-interrupt, no current rendering
   * and at least one freeSurface present.
   * Object destructor call endOfRendering */
  [[nodiscard]] std::unique_ptr<RenderingSurface> startOfRendering();
  /* ready -> exporting
   * wait for no-interrupt, no current exporting
   * and at least one readySurface present.
   * Object destructor call endOfExporting */
  [[nodiscard]] std::unique_ptr<const ExportingSurface> startOfExporting();

 private:
  std::vector<SurfaceOwner> surfacePool;
  std::stack<SurfaceEditor> freeSurfaces;
  std::queue<SurfaceEditor> readySurfaces;

  std::optional<const SurfaceEditor> renderingSurface;
  std::optional<const SurfaceEditor> exportingSurface;

  // TODO: is this recursive or no-recursive mutex? may use recursive advantage?
  std::mutex accessMutex;
  std::condition_variable awaitingVar;

  bool interruptRequest;

  /* rendering -> ready
   * notifying method. using public copies SurfaceEditor and data after this
   * leads to UndefinedBehavior! */
  void endOfRendering();
  /* exporting -> free
   * notifying method. using public copies SurfaceEditor and data after this
   * leads to UndefinedBehavior! */
  void endOfExporting();

  /*
   * awaiting method (for end of rendering and exporting)
   * 'lock' should be locked
   * leave freeSurfaces empty. caller func should fill it from surfacePool */
  // TODO: test unique_lock move semantic!
  std::unique_lock<std::mutex> interrupt(std::unique_lock<std::mutex> lock);

  [[nodiscard]] bool _isBusy() const noexcept;

 public:
  class WorkingSurface : public SurfaceEditor {
   public:
    virtual ~WorkingSurface() = 0;

    WorkingSurface(const WorkingSurface&) = delete;
    WorkingSurface(WorkingSurface&&) = delete;

   protected:
    WorkingSurface(SurfaceEditor surface, PoolOfSurfaces* pool) noexcept;
    friend class PoolOfSurfaces;

    PoolOfSurfaces* pool;
  };

  class RenderingSurface final : public WorkingSurface {
   public:
    ~RenderingSurface() final;
   private:
    using WorkingSurface::WorkingSurface;
  };

  class ExportingSurface final : public WorkingSurface {
   public:
    ~ExportingSurface() final;
   private:
    using WorkingSurface::WorkingSurface;
  };
};

#endif  // ENGINE_POOL_OF_SURFACES_HPP_
