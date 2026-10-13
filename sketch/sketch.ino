#include <SPI.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// Include the image array you generated
#include "asset_4.h"

// ---------------- LovyanGFX Setup ----------------
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 _panel_instance;
  lgfx::Bus_SPI      _bus_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read  = 16000000;
      cfg.spi_3wire  = false;
      cfg.use_lock   = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      
      cfg.pin_sclk = 12; 
      cfg.pin_mosi = 11; 
      cfg.pin_miso = 13; 
      cfg.pin_dc   = 46; 
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs           = 45; 
      cfg.pin_rst          = 47; 
      cfg.pin_busy         = -1;
      cfg.panel_width      = 240;
      cfg.panel_height     = 320;
      cfg.offset_x         = 0;
      cfg.offset_y         = 0;
      cfg.offset_rotation  = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;
      cfg.readable         = true;
      cfg.invert           = true; 
      cfg.rgb_order        = false;
      cfg.dlen_16bit       = false;
      cfg.bus_shared       = true; 
      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);
  }
};

LGFX tft; 

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize display
  tft.init();
  tft.fillScreen(TFT_WHITE); // White background to match the logo style

  Serial.println("Drawing PNG...");

  // Draw the PNG image
  // tft.drawPng(array_name, array_size, x_position, y_position);
  // Using 0, 0 will draw it starting from the top-left corner.
  tft.drawPng(Asset_4, sizeof(Asset_4), 0, 0);
}

void loop() {
  // Do nothing
}