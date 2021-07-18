/*
 * start rewrite from:
 * https://github.com/adafruit/Adafruit-GFX-Library.git
 * https://github.com/daumemo/IPS_LCD_R61529_FT6236_Arduino_eSPI_Test
 * Data Sheet:
 * http://read.pudn.com/downloads648/ebook/2620902/R61529.pdf
 */
#ifndef _ARDUINO_R61529_H_
#define _ARDUINO_R61529_H_

#include <Arduino.h>
#include <Print.h>
#include "../Arduino_GFX.h"
#include "../Arduino_TFT.h"

#define R61529_TFTWIDTH 320  // R61529 max width
#define R61529_TFTHEIGHT 480 // R61529 max height

#define R61529_RST_DELAY 20    // delay ms wait for reset finish
#define R61529_SLPIN_DELAY 20  // delay ms wait for sleep in finish
#define R61529_SLPOUT_DELAY 200 // delay ms wait for sleep out finish

// User Command
#define R61529_NOP 0x00        // nop
#define R61529_SWRESET 0x01    // soft_reset
#define R61529_RDDID 0x04      // read_DDB_start
#define R61529_RDMODE 0x0A     // get_power_mode
#define R61529_RDMADCTL 0x0B   // get_address_mode
#define R61529_RDPIXFMT 0x0C   // get_pixel_format
#define R61529_RDIMGFMT 0x0D   // get_display_mode
#define R61529_RDSIGMODE 0x0E  // get_signal_mode
#define R61529_RDSELFDIAG 0x0F // get_diagnostic_result

#define R61529_SLPIN 0x10  // enter_sleep_mode
#define R61529_SLPOUT 0x11 // exit_sleep_mode
#define R61529_PTLON 0x12  // enter_partial_mode
#define R61529_NORON 0x13  // enter_normal_mode

#define R61529_INVOFF 0x20  // exit_invert_mode
#define R61529_INVON 0x21   // enter_invert_mode
#define R61529_DISPOFF 0x28 // set_display_off
#define R61529_DISPON 0x29  // set_display_on
#define R61529_CASET 0x2A   // set_column_address
#define R61529_PASET 0x2B   // set_page_address
#define R61529_RAMWR 0x2C   // write_memory_start
#define R61529_RAMRD 0x2E   // read_memory_start

#define R61529_PTLAR 0x30   // set_partial_area
#define R61529_TEAROFF 0x34 // set_tear_off
#define R61529_TEARON 0x35  // set_tear_on
#define R61529_MADCTL 0x36  // set_address_mode
#define R61529_IDLEOFF 0x38 // exit_idle_mode
#define R61529_IDLEON 0x39  // enter_idle_mode

#define R61529_PIXFMT 0x3A // set_pixel_format
#define R61529_WRMC 0x3C   // write_memory_continue
#define R61529_RDMC 0x3E   // read_memory_continue

#define R61529_SETTSL 0x44 // set_tear_scanline
#define R61529_GETSL 0x45  // get_scanline

#define R61529_RDDDBS 0xA1 // read_DDB_start

#define R61529_MCAP 0xB0     // Manufacturer Command Access Protect
#define R61529_LPMC 0xB1     // Low Power Mode Control
#define R61529_FMAIS 0xB3    // Frame Memory Access and Interface Setting
#define R61529_DISPMODE 0xB4 // Display Mode
#define R61529_RCEEC 0xB5    // Read Checksum and ECC Error Count
#define R61529_DSICTL 0xB6   // DSI Control
#define R61529_MDDICTL 0xB7  // MDDI Control
#define R61529_BLCTL1 0xB8   // Backlight Control (1)
#define R61529_BLCTL2 0xB9   // Backlight Control (2)
#define R61529_BLCTL3 0xBA   // Backlight Control (3)
#define R61529_DCRD 0xBF     // Device Code Read

#define R61529_PDS 0xC0       // Panel Driving Setting
#define R61529_DTSFNM 0xC1    // Display Timing Setting for Normal Mode
#define R61529_TESTMODE1 0xC3 // Test Mode 1
#define R61529_SGDTS 0xC4     // Source/Gate Driving Timing Setting
#define R61529_DPIPCTL 0xC6   // DPI Polarity Control
#define R61529_TESTMODE2 0xC7 // Test Mode 2
#define R61529_GAMMASETA 0xC8 // Gamma Setting A Set
#define R61529_GAMMASETB 0xC9 // Gamma Setting B Set
#define R61529_GAMMASETC 0xCA // Gamma Setting C Set
#define R61529_TESTMODE3 0xCC // Test Mode 3

#define R61529_PWSET 0xD0 // Power Setting (Charge Pump Setting)
#define R61529_VCOMSET 0xD1 // VCOM Setting
#define R61529_TESTMODE4 0xD6 // Test Mode 4
#define R61529_TESTMODE5 0xD7 // Test Mode 5
#define R61529_TESTMODE6 0xD8 // Test Mode 6
#define R61529_TESTMODE7 0xD9 // Test Mode 7
#define R61529_TESTMODE8 0xDA // Test Mode 8

#define R61529_NVMAC 0xE0 // NVM Access Control
#define R61529_SETDDBWRCTL 0xE1 // set_DDB_write_control
#define R61529_NVMLC 0xE2 // NVM Load Control
#define R61529_TESTMODE9 0xE4 // Test Mode 9
#define R61529_TESTMODE10 0xE5 // Test Mode 10
#define R61529_TESTMODE11 0xE6 // Test Mode 11
#define R61529_TESTMODE12 0xE7 // Test Mode 12

#define R61529_TESTMODE13 0xF3 // Test Mode 13
#define R61529_RDMODEIN 0xF5 // Read Mode In for DBI Only
#define R61529_RDMODEOUT 0xF6 // Read Mode Out for DBI Only
#define R61529_TESTMODE14 0xF8 // Test Mode 14
#define R61529_TESTMODE15 0xFA // Test Mode 15
#define R61529_TESTMODE16 0xFC // Test Mode 16
#define R61529_TESTMODE17 0xFD // Test Mode 17
#define R61529_TESTMODE18 0xFE // Test Mode 18

// parameters
#define R61529_MADCTL_MY 0x80  // Bottom to top
#define R61529_MADCTL_MX 0x40  // Right to left
#define R61529_MADCTL_MV 0x20  // Reverse Mode
#define R61529_MADCTL_ML 0x10  // LCD refresh Bottom to top
#define R61529_MADCTL_RGB 0x00 // Red-Green-Blue pixel order
#define R61529_MADCTL_BGR 0x08 // Blue-Green-Red pixel order
#define R61529_MADCTL_MH 0x04  // LCD refresh right to left
#define R61529_MADCTL_SS 0x02
#define R61529_MADCTL_GS 0x01

class Arduino_R61529 : public Arduino_TFT
{
public:
  Arduino_R61529(Arduino_DataBus *bus, int8_t rst = -1, uint8_t r = 0, bool ips = false);

  void begin(int32_t speed = 0) override;
  void writeAddrWindow(int16_t x, int16_t y, uint16_t w, uint16_t h) override;
  void setRotation(uint8_t r) override;
  void invertDisplay(bool) override;
  void displayOn() override;
  void displayOff() override;

protected:
  void tftInit() override;

private:
};

#endif
