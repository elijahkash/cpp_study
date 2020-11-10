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

#ifndef UTILITY_LINEAR_SIZE_HPP_
#define UTILITY_LINEAR_SIZE_HPP_

#include <cstdint>  // uint32_t

/*
std::is_trivially_copyable<linearSize>::value = 1
std::is_trivial<linearSize>::value = 0
std::is_standard_layout<linearSize>::value = 1
std::is_aggregate<linearSize>::value = 0
*/

struct LinearSize2D {
  uint32_t width = 0;
  uint32_t height = 0;

  LinearSize2D() = default;
  LinearSize2D(uint32_t width, uint32_t height) noexcept;
};

[[nodiscard]] bool operator==(const LinearSize2D& lhs,
                              const LinearSize2D& rhs) noexcept;

struct LinearSize3D {
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t depth = 0;

  LinearSize3D() = default;
  LinearSize3D(uint32_t width, uint32_t height, uint32_t depth) noexcept;
};

[[nodiscard]] bool operator==(const LinearSize3D& lhs,
                              const LinearSize3D& rhs) noexcept;

#endif  // UTILITY_LINEAR_SIZE_HPP_
