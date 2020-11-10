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

#include "pool_of_surfaces.hpp"

#include <utility>  // std::move

PoolOfSurfaces::PoolOfSurfaces(SurfaceConfig surfConf, unsigned surfacePoolSize)
  : renderingSurface(std::nullopt),
    exportingSurface(std::nullopt),
    interruptRequest(false) {
  // TODO: right way? (+ setPoolSize)
  if (not surfacePoolSize)
    throw std::logic_error("PoolOfSurfaces: surfacePoolSize can't = 0!");
  for (unsigned i = 0; i < surfacePoolSize; i++)
    surfacePool.emplace_back(surfConf);
  for (const auto& iter : surfacePool)
    freeSurfaces.push(SurfaceEditor(iter));
}

bool PoolOfSurfaces::isBusy() {
  std::lock_guard<std::mutex> lock(accessMutex);
  return _isBusy();
}

SurfaceConfig PoolOfSurfaces::getSurfaceConfig() {
  std::lock_guard<std::mutex> lock(accessMutex);
  return surfacePool[0];
}

void PoolOfSurfaces::setPoolSize(unsigned newPoolSize) {
  std::unique_lock<std::mutex> lock(accessMutex);
  if (not newPoolSize)
    throw std::logic_error("PoolOfSurfaces: surfacePoolSize can't = 0!");
  if (newPoolSize == surfacePool.size())
    return;
  lock = interrupt(std::move(lock));
  if (surfacePool.size() > newPoolSize) {
    while (surfacePool.size() > newPoolSize)
      surfacePool.pop_back();
  } else {
    SurfaceConfig tmp = surfacePool.front();
    while (surfacePool.size() < newPoolSize)
      surfacePool.emplace_back(tmp);
  }
  for (const auto& iter : surfacePool)
    freeSurfaces.push(SurfaceEditor(iter));
  awaitingVar.notify_all();
}

void PoolOfSurfaces::reConfigSurfaces(SurfaceConfig newConfig) {
  std::unique_lock<std::mutex> lock(accessMutex);
  if (surfacePool.front() == newConfig)
    return;
  lock = interrupt(std::move(lock));
  unsigned poolSize = surfacePool.size();
  surfacePool.clear();
  for (unsigned i = 0; i < poolSize; i++)
    surfacePool.emplace_back(newConfig);
  for (const auto& iter : surfacePool)
    freeSurfaces.push(SurfaceEditor(iter));
  awaitingVar.notify_all();
}

std::unique_ptr<PoolOfSurfaces::RenderingSurface>
PoolOfSurfaces::startOfRendering() {
  std::unique_lock<std::mutex> lock(accessMutex);
  auto waitCond = [this]() -> bool { return (not renderingSurface.has_value()
                                             and not freeSurfaces.empty()
                                             and not interruptRequest); };
  awaitingVar.wait(lock, waitCond);
  renderingSurface.reset();
  renderingSurface.emplace(freeSurfaces.top());
  freeSurfaces.pop();
  // can't use make_unique case of private RenderingSurface constructor!
  return std::unique_ptr<PoolOfSurfaces::RenderingSurface>(
      new RenderingSurface(renderingSurface.value(), this));
}

std::unique_ptr<const PoolOfSurfaces::ExportingSurface>
PoolOfSurfaces::startOfExporting() {
  std::unique_lock<std::mutex> lock(accessMutex);
  auto waitCond = [this]() -> bool { return (not exportingSurface.has_value()
                                             and not readySurfaces.empty()
                                             and not interruptRequest); };
  awaitingVar.wait(lock, waitCond);
  exportingSurface.emplace(readySurfaces.front());
  readySurfaces.pop();
  // can't use make_unique case of private ExportingSurface constructor!
  return std::unique_ptr<PoolOfSurfaces::ExportingSurface>(
      new ExportingSurface(exportingSurface.value(), this));
}

void PoolOfSurfaces::endOfRendering() {
  std::lock_guard<std::mutex> lock(accessMutex);
  readySurfaces.push(*renderingSurface);
  renderingSurface.reset();
  awaitingVar.notify_all();
}

void PoolOfSurfaces::endOfExporting() {
  std::lock_guard<std::mutex> lock(accessMutex);
  freeSurfaces.push(*exportingSurface);
  exportingSurface.reset();
  awaitingVar.notify_all();
}

std::unique_lock<std::mutex> PoolOfSurfaces::interrupt(
    std::unique_lock<std::mutex> lock) {
  interruptRequest = true;
  auto waitCond = [this]() -> bool { return not _isBusy(); };
  awaitingVar.wait(lock, waitCond);
  interruptRequest = false;
  while (not freeSurfaces.empty())
    freeSurfaces.pop();
  while (not readySurfaces.empty())
    readySurfaces.pop();
  return lock;
}

bool PoolOfSurfaces::_isBusy() const noexcept {
  return (renderingSurface or exportingSurface);
}

PoolOfSurfaces::WorkingSurface::WorkingSurface(SurfaceEditor surface,
                                               PoolOfSurfaces* pool) noexcept
  : SurfaceEditor(surface), pool(pool) {
}

PoolOfSurfaces::WorkingSurface::~WorkingSurface() = default;

PoolOfSurfaces::RenderingSurface::~RenderingSurface() {
  pool->endOfRendering();
}

PoolOfSurfaces::ExportingSurface::~ExportingSurface() {
  pool->endOfExporting();
}
