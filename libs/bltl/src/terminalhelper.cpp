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
#include "terminalhelper.hpp"
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

namespace TERM {

Terminal_t::Terminal_t() noexcept { 
   set_nonblocking(); 
}

 
Terminal_t::~Terminal_t() noexcept { 
   restore(); 
}

void 
Terminal_t::set_nonblocking() noexcept {
   struct termios newterm;
   tcgetattr(fileno(stdin), &oldterm);
   newterm=oldterm;
   newterm.c_lflag = IXON|ICRNL;
   tcsetattr(fileno(stdin), TCSADRAIN, &newterm);
}

bool 
Terminal_t::isKeyPressed () const noexcept {
   fd_set in;
   struct timeval tim;
   FD_ZERO(&in);
   FD_SET(STDIN,&in);
   tim.tv_sec = 0;
   tim.tv_usec = 400;
   return (select (STDIN+1,&in,NULL,NULL,&tim));
}

void 
Terminal_t::restore() noexcept {
   tcsetattr(fileno(stdin), TCSADRAIN, &oldterm);
}

void
Terminal_t::clearBuffer () noexcept {
   int flags = fcntl(STDIN,F_GETFL);
   fcntl(STDIN,F_SETFL,O_NONBLOCK);
   while (getchar() != -1);
   fcntl(STDIN,F_SETFL,flags);
}

void 
Terminal_t::waitKey(int const k) const noexcept {
   while(isKeyPressed());
   for(;;) {
      if (  isKeyPressed() 
         && std::getchar() == k)
         break;
   }
}

int
Terminal_t::wait4NextKeyPress() const noexcept {
   while(isKeyPressed());
   for(;;) {
      if ( isKeyPressed() )
         return std::getchar();
   }
}

} // namespace TERM
