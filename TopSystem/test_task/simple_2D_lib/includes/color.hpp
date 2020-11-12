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

#ifndef UTILITY_COLOR_HPP_
#define UTILITY_COLOR_HPP_

#include <cstdint>  // uint8_t

struct Color {
 public:
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  Color() = default;
  Color(uint8_t r, uint8_t g, uint8_t b) noexcept;
};

[[nodiscard]] bool operator==(const Color& lhs, const Color&rhs) noexcept;

#endif  // UTILITY_COLOR_HPP_
