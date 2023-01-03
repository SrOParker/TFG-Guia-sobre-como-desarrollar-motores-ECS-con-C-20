//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of Basic Linux ANSI Terminal library
//  Copyright (C) 2020 Francisco J. Gallego-Durán (@FranGallegoBR, fjgallego@ua.es)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------
#pragma once
#include <termios.h>
#include "termcolours.hpp"

namespace TERM {

struct Terminal_t {
   constexpr static int STDIN { 0 };
   struct termios oldterm;

   Terminal_t() noexcept;
   ~Terminal_t() noexcept;

   void  set_nonblocking() noexcept ;
   bool  isKeyPressed() const noexcept;
   void  restore() noexcept;
   void  clearBuffer() noexcept;
   void  waitKey(int const k) const noexcept;
   int   wait4NextKeyPress() const noexcept;
};

} // namespace TERM
