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

#ifndef ENGINE_SURFACE_HPP_
#define ENGINE_SURFACE_HPP_

#include <span>
#include <cstddef>  // size_t
#include <memory>

#include "linear_size.hpp"
#include "color.hpp"

class SurfaceConfig {
 public:
  /*
   * std::overflow_error possible if too big values.
   * depend from class Color! */
  explicit SurfaceConfig(LinearSize2D resolution);

  [[nodiscard]] LinearSize2D getInfo() const noexcept;
  [[nodiscard]] std::size_t pixelCount() const noexcept;
  [[nodiscard]] std::size_t requiredMemSize() const noexcept;

 protected:
  LinearSize2D resolution;

  friend bool operator==(const SurfaceConfig& lhs,
                         const SurfaceConfig& rhs) noexcept;
};

[[nodiscard]] bool operator==(const SurfaceConfig& lhs,
                              const SurfaceConfig& rhs) noexcept;

class SurfaceOwner : public SurfaceConfig {
 public:
  explicit SurfaceOwner(SurfaceConfig config);

  SurfaceOwner(const SurfaceOwner&) = delete;
  SurfaceOwner(SurfaceOwner&& src) noexcept;

 private:
  std::unique_ptr<Color[]> mem;

  friend class SurfaceEditor;
};

class SurfaceEditor : public SurfaceConfig {
 public:
  explicit SurfaceEditor(const SurfaceOwner& owner) noexcept;

  std::span<Color> operator[](std::size_t index);
  std::span<const Color> operator[](std::size_t index) const;

  Color& operator()(uint32_t width, uint32_t height);
  const Color& operator()(uint32_t width, uint32_t height) const;

  [[nodiscard]] std::span<Color> data() noexcept;
  [[nodiscard]] std::span<const Color> data() const noexcept;

 protected:
  std::span<Color> rawPixels;
};

#endif  // ENGINE_SURFACE_HPP_
