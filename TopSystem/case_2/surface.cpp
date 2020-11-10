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

#include "surface.hpp"

// TODO: SIZE_T_MAX not portable!!!!!
// #include <climits>  // SIZE_T_MAX
#include <limits>
#include <stdexcept>
#include <utility>  // std::move

// SurfaceConfig================================================================

SurfaceConfig::SurfaceConfig(LinearSize2D resolution) : resolution(resolution) {
  if (resolution.width > (std::numeric_limits<size_t>::max() / resolution.height)
      or pixelCount() > (std::numeric_limits<size_t>::max() / sizeof(Color)))
    throw std::overflow_error("Overflow in SurfaceConfig");
}

LinearSize2D SurfaceConfig::getInfo() const noexcept {
  return resolution;
}

std::size_t SurfaceConfig::pixelCount() const noexcept {
  return resolution.width * resolution.height;
}

std::size_t SurfaceConfig::requiredMemSize() const noexcept {
  return pixelCount() * sizeof(Color);
}

bool operator==(const SurfaceConfig &lhs, const SurfaceConfig &rhs) noexcept {
  return (lhs.resolution == rhs.resolution);
}

// SurfaceOwner=================================================================

SurfaceOwner::SurfaceOwner(SurfaceConfig config)
  : SurfaceConfig(config), mem(std::make_unique<Color[]>(requiredMemSize())) {
}

SurfaceOwner::SurfaceOwner(SurfaceOwner&& src) noexcept
  : SurfaceConfig(src), mem(std::move(src.mem)) {
}

// SurfaceEditor================================================================

SurfaceEditor::SurfaceEditor(const SurfaceOwner& owner) noexcept
  : SurfaceConfig(owner.getInfo()),
  rawPixels(owner.mem.get(), pixelCount()) {
}

std::span<Color> SurfaceEditor::operator[](std::size_t index) {
  return std::span<Color>(rawPixels.data() + resolution.height * index,
                          resolution.height);
}

std::span<const Color> SurfaceEditor::operator[](std::size_t index) const {
  return std::span<const Color>(rawPixels.data() + resolution.height * index,
                          resolution.height);
}

Color& SurfaceEditor::operator()(uint32_t width, uint32_t height) {
  return rawPixels[width * resolution.height + height];
}

const Color& SurfaceEditor::operator()(uint32_t width, uint32_t height) const {
  return rawPixels[width * resolution.height + height];
}

std::span<Color> SurfaceEditor::data() noexcept {
  return rawPixels;
}

std::span<const Color> SurfaceEditor::data() const noexcept {
  return rawPixels;
}
