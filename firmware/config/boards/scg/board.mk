# List of all the board related files.
BOARDCPPSRC = $(BOARD_DIR)/board_configuration.cpp

# MCU defines
DDEFS += -DSTM32F407xx

ifeq ($(VAR_DEF_ENGINE_TYPE),)
  VAR_DEF_ENGINE_TYPE = -DDEFAULT_ENGINE_TYPE=engine_type_e::DEFAULT_FRANKENSO
endif

# here we use different names for env variable and macro name in order to reduce confusion. overall this is about Frankenso builds defining FIRMWARE_ID
ifeq ($(FW_ID_ENV),)
  DDEFS += -DFIRMWARE_ID=\"community\"
else
  DDEFS += -D$(FW_ID_ENV)
endif

BUNDLE_OPENOCD = yes

# User can configure LIN/K-line interface
#DDEFS += -DEFI_KLINE=TRUE
#DDEFS += -DKLINE_SERIAL_DEVICE_RX=C11 -DKLINE_SERIAL_DEVICE_TX=C10
#DDEFS += -DKLINE_SERIAL_DEVICE=SD3

# DAC channel1 PA4
# DAC channel2 PA5
#DDEFS += -DEFI_DAC=TRUE -DHAL_USE_DAC=TRUE -DSTM32_DAC_USE_DAC1_CH1=TRUE -DSTM32_DAC_USE_DAC1_CH2=TRUE

#DDEFS += -DBOARD_TLE9104_COUNT=2
# EGT chip
#DDEFS += -DEFI_MAX_31855=TRUE

# We are running on Frankenso hardware!
DDEFS += -DHW_FRANKENSO=1
DDEFS += $(DEFAULT_ENGINE_TYPE)

DDEFS += -DSTM32_ADC_USE_ADC3=TRUE
# todo: make knock pin software-selectable?
#DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC3=TRUE

DDEFS += -DSTATIC_BOARD_ID=STATIC_BOARD_ID_SCG

# TS_SECONDARY_UxART_PORT
DDEFS += -DSTM32_SERIAL_USE_USART3=TRUE -DSTM32_SERIAL_USART3_PRIORITY=6
DDEFS += -DTS_SECONDARY_UxART_PORT=SD3 -DEFI_TS_SECONDARY_IS_SERIAL=TRUE

#DDEFS += -DEFI_WS2812=TRUE

ifndef IS_RE_BOOTLOADER
#DDEFS += -DHAL_USE_EEPROM=TRUE -DSTM32_I2C_USE_I2C3=TRUE
endif

DDEFS += -DUSB_DESCRIPTOR_STRING_CONTENT="'r', 0, 'u', 0, 's', 0, 'E', 0, 'F', 0, 'I', 0, ' ', 0, 'F', 0, 'o', 0, 'r', 0, 'g', 0, 'e', 0, 'E', 0, 'F', 0, 'I', 0"
