##-----------------------------LICENSE NOTICE------------------------------------
##  This file is part of Basic Linux ANSI Terminal library
##  Copyright (C) 2020 Francisco J. Gallego-Durán (@FranGallegoBR, fjgallego@ua.es)
##
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU Lesser General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU Lesser General Public License for more details.
##
##  You should have received a copy of the GNU Lesser General Public License
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.
##------------------------------------------------------------------------------
###########
# MACROS
###########

# $(1) : Compile
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

# $(1) : Source file
define C20
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# $(1) : Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

###########
# CONFIG
###########
APP     := libterm.a
CFLAGS  := -Wall -pedantic
CCFLAGS := $(CFLAGS) -std=c++17 
CC      := clang++
C       := clang
AR		:= ar
ARFLAGS := -crs
RANLIB  := ranlib
MKDIR   := mkdir -p
SRC     := src
OBJ     := obj

ifdef RELEASE
	CCFLAGS += -O3
	SUFFIX = 
else
	CCFLAGS += -g
	SUFFIX = L
endif

LIBSDIR	   := lib
INCLUDE    := include
#LIBS	   := $(ALIBS) -lIrrlicht -L$(LIBSDIR)/ -lpthread -L$(LIBSDIR)/fmod -lfmod${SUFFIX} -lfmodstudio${SUFFIX}
INCDIRS	   := -I$(SRC) -I$(LIBSDIR) -I$(INCLUDE)

ALLCPPS     		 := $(shell find src/ -type f -iname *.cpp)
ALLCS      			 := $(shell find src/ -type f -iname *.c)
ALLOBJ     			 := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C20,$(F)))
SUBDIRS    			 := $(shell find $(SRC) -type d)
OBJSUBDIRS  		 := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
CURRENT_DIR 		 := $(shell pwd)

.PHONY: dir

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)

$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F)),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS)))

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))
	$(info $(ALLCOMPILECPPS))

$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

#CLEAN RULES
clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) -r "./$(APP)"	