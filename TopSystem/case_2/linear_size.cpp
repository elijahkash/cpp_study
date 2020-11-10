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

#include "linear_size.hpp"

LinearSize2D::LinearSize2D(uint32_t width, uint32_t height) noexcept
  : width(width), height(height) {
}

bool operator==(const LinearSize2D& lhs, const LinearSize2D& rhs) noexcept {
  return (lhs.width == rhs.width and lhs.height == rhs.height);
}

LinearSize3D::LinearSize3D(uint32_t width, uint32_t height,
                           uint32_t depth) noexcept
  : width(width), height(height), depth(depth) {
}

bool operator==(const LinearSize3D& lhs, const LinearSize3D& rhs) noexcept {
  return (lhs.width == rhs.width and lhs.height == rhs.height
          and lhs.depth == rhs.depth);
}
