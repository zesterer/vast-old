#
# file : makefile
#
# Copyright (c) 2017 Joshua Barretto <joshua.s.barretto@gmail.com>
#
# This file is part of Tupai.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

# Definitions
# -----------

EXEC_NAME = vast

# Build type : 'release' or 'debug'
BUILD_TYPE = debug

SRC_ROOT = $(abspath .)
TGT_ROOT ?= $(SRC_ROOT)/build

EXEC ?= $(TGT_ROOT)/$(EXEC_NAME)
TGT_DIRS += $(dir $(EXEC))

DATA_DIR = $(SRC_ROOT)/data

# Libraries
# ---------

# GLFW
INC_DIRS += glfw
LINK_LIBS += X11 glfw

# GLBinding
INC_DIRS += glbinding
LINK_LIBS += glbinding

# GLM
INC_DIRS += glm

# SOIL
INC_DIRS += SOIL
LINK_LIBS += SOIL

# C++ Flags
# ---------

INC_DIRS += $(SRC_ROOT)/include
CPP_FLAGS += $(addprefix -I, $(INC_DIRS))

CPP_FLAGS += -std=c++14 -Wall -Wextra
ifeq ($(BUILD_TYPE), release)
	CPP_FLAGS += -O3
else ifeq ($(BUILD_TYPE), debug)
	CPP_FLAGS += -g -fsanitize=address
	CPP_FLAGS += -DDEBUG_BUILD
endif

# Link Flags
# ----------

LINK_FLAGS += $(addprefix -l, $(LINK_LIBS))
LINK_FLAGS += -pedantic -lpthread -lm

# Tools
# -----

TOOL_PREFIX ?=

AS  = $(TOOL_PREFIX)gcc
CC  = $(TOOL_PREFIX)gcc
CPP = $(TOOL_PREFIX)g++
LD  = $(TOOL_PREFIX)g++
AR  = $(TOOL_PREFIX)ar

TOOL_DIR ?= $(abspath $(dir $(shell which $(CC))))

# Source files
# ------------

SRC_RFILES += $(shell ls $(SRC_ROOT)/src/*.{s,S,c,cpp} 2> /dev/null)

SRC_FILES = $(abspath $(SRC_RFILES))

OBJ_FILES += $(subst $(SRC_ROOT), $(TGT_ROOT), $(addsuffix .o, $(SRC_FILES)))
DEP_FILES += $(subst $(SRC_ROOT), $(TGT_ROOT), $(addsuffix .d, $(SRC_FILES)))

TGT_DIRS += $(dir $(OBJ_FILES) $(DEP_FILES))

# Rules
# -----

.PHONY : all clean

all : tree $(EXEC)

rebuild : clean all

run : all
	@echo "[`date "+%H:%M:%S"`] Running '$(EXEC)'..."
	@$(EXEC)

tree :
	@mkdir -p $(TGT_DIRS)

clean :
	@rm -r -f $(EXEC) $(OBJ_FILES) $(DEP_FILES) $(TGT_DIRS)

$(EXEC) : $(OBJ_FILES)
	@#echo "[`date "+%H:%M:%S"`] Linking '$@'..."
	@$(TOOL_DIR)/$(LD) $(CPP_FLAGS) -o $@ $(OBJ_FILES) $(LINK_FLAGS)
	@echo "[`date "+%H:%M:%S"`] Linked '$@'."

-include $(DEP_FILES)

# Compile .s files
$(TGT_ROOT)/%.s.o : $(SRC_ROOT)/%.s
	@#echo "[`date "+%H:%M:%S"`] Compiling '$<'..."
	@$(TOOL_DIR)/$(AS) -c -o $@ $< $(CPP_FLAGS)
	@echo "[`date "+%H:%M:%S"`] Compiled '$@'."

# Compile .S files
$(TGT_ROOT)/%.S.o : $(SRC_ROOT)/%.S
	@#echo "[`date "+%H:%M:%S"`] Compiling '$<'..."
	@$(TOOL_DIR)/$(AS) -c -o $@ $< $(CPP_FLAGS)
	@echo "[`date "+%H:%M:%S"`] Compiled '$@'."

# Compile .c files
$(TGT_ROOT)/%.c.o : $(SRC_ROOT)/%.c
	@#echo "[`date "+%H:%M:%S"`] Compiling '$<'..."
	@$(TOOL_DIR)/$(CC) -MMD -c -o $@ $< $(CPP_FLAGS)
	@echo "[`date "+%H:%M:%S"`] Compiled '$@'."

# Compile .cpp files
$(TGT_ROOT)/%.cpp.o : $(SRC_ROOT)/%.cpp
	@#echo "[`date "+%H:%M:%S"`] Compiling '$<'..."
	@$(TOOL_DIR)/$(CPP) -MMD -c -o $@ $< $(CPP_FLAGS)
	@echo "[`date "+%H:%M:%S"`] Compiled '$@'."
