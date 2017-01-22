# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

# Ubuntu:
# sudo apt-get install arduino-mk python-serial

USER_LIB_PATH=lib

ARDUINO_LIBS=Wire SPI LiquidCrystal_I2C AM2320 RF24

BOARD_TAG    = uno
include /usr/share/arduino/Arduino.mk
