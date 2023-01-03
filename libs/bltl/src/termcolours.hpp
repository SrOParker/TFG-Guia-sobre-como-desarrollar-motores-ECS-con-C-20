//-----------------------------LICENSE NOTICE------------------------------------
//  Basic Linux ANSI Terminal library
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

namespace TERM {

// Attributes
enum {
      AT_Normal    = 0
   ,  AT_Bold      = 1
   ,  AT_Faint     = 2
   ,  AT_Italic    = 3
   ,  AT_Underline = 4
   ,  AT_SlowBlink = 5
   ,  AT_FastBlink = 6
   ,  AT_Reverse   = 7
   ,  AT_Conceal   = 8
   ,  AT_Crossed   = 9
   ,  AT_Default   = 10
};

// Foreground colours
enum {
      FG_Black    = 30
   ,  FG_Red      = 31
   ,  FG_Green    = 32
   ,  FG_Yellow   = 33
   ,  FG_Blue     = 34
   ,  FG_Magenta  = 35
   ,  FG_Cyan     = 36
   ,  FG_White    = 37
   ,  FG_Default  = 39
};

// Background colours
enum {
      BG_Black    = 40
   ,  BG_Red      = 41
   ,  BG_Green    = 42
   ,  BG_Yellow   = 43
   ,  BG_Blue     = 44
   ,  BG_Magenta  = 45
   ,  BG_Cyan     = 46
   ,  BG_White    = 47
   ,  BG_Default  = 49
};

} // namespace TERM