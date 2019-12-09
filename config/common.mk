#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

export ATMOSPHERE_CONFIG_MAKE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export ATMOSPHERE_LIBRARY_DIR     := $(ATMOSPHERE_CONFIG_MAKE_DIR)/..

ifeq ($(strip $(ATMOSPHERE_BOARD)),)
export ATMOSPHERE_BOARD := nx-hac-001
endif

export ATMOSPHERE_DEFINES  := -DATMOSPHERE
export ATMOSPHERE_SETTINGS := -fPIE -g
export ATMOSPHERE_CFLAGS   := -Wall -ffunction-sections -fdata-sections -fno-strict-aliasing -fwrapv \
                          -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-stack-protector
export ATMOSPHERE_CXXFLAGS := -fno-rtti -fno-exceptions -std=gnu++17
export ATMOSPHERE_ASFLAGS  :=


ifeq ($(ATMOSPHERE_BOARD),nx-hac-001)
export ATMOSPHERE_ARCH_MAKE_DIR   := $(ATMOSPHERE_CONFIG_MAKE_DIR)/arch/arm64
export ATMOSPHERE_BOARD_MAKE_DIR  := $(ATMOSPHERE_CONFIG_MAKE_DIR)/board/nintendo/switch
endif

include $(ATMOSPHERE_ARCH_MAKE_DIR)/arch.mk
include $(ATMOSPHERE_BOARD_MAKE_DIR)/board.mk
