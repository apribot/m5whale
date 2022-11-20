// Example sketch to demonstrate the drawing of X BitMap (XBM)
// format image onto the display.

// Information on the X BitMap (XBM) format can be found here:
// https://en.wikipedia.org/wiki/X_BitMap

// This example is part of the TFT_eSPI library:
// https://github.com/Bodmer/TFT_eSPI

// Created by Bodmer 23/14/18

#include "xbm.h"             // Sketch tab header for xbm images

#include <M5StickC.h>        // Hardware-specific library

int x = 30;
int y = 30;

bool isLeft = false;
bool mouthopened = false;
bool flapdown = false;

int bubblex = 0;
int bubbley = 0;
int bubblesize = 0;
bool isbubble = false;

bool chewtime = false;
int chewcount = 0;
bool chomp = false;

int hunger = 0;

int ticks = 0;
int sleeptick = 0;
bool asleep = false;

int offticks = 0;


void setup() {
  M5.begin();               // Initialise the display
  M5.Lcd.setRotation(1);
  M5.Axp.ScreenBreath(10);
  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
}

void loop() {



  if(sleeptick > 3000) {
    M5.Axp.ScreenBreath(0);
    asleep = true;
    offticks = offticks + 1;
  } else if (!asleep) {
    sleeptick = sleeptick + 1;
  }

  if(offticks > 6000) {
    offticks = 0;
    M5.Axp.PowerOff();
  }

  if(ticks < 200){
    M5.update(); 
    if (M5.BtnA.wasPressed()) {
      if(asleep) {
        asleep = false;
        sleeptick = 0;
        M5.Axp.ScreenBreath(10);
      } else {
        chewtime = true;
        chewcount = 5;
        chomp = true;
      }
    }    
    delay(10);
    ticks = ticks + 1;
  } else {
    ticks = 0;

    x = x + ((random(3) - 1)*4);
    y = y + ((random(3) - 1)*4);

    x = max(min(x, M5.Lcd.width() - whaleWidth), 0);
    y = max(min(y, M5.Lcd.height() - whaleHeight), 0);
    
  /*
  whale_r_open_up
  whale_r_open_down
  whale_r_closed_down
  whale_r_closed_up
  whale_l_open_up
  whale_l_open_down
  whale_l_closed_down
  whale_l_closed_up
  */


      M5.Lcd.fillScreen(BLACK);
      
      if(flapdown) {
        if(chewtime && chomp) {
          M5.Lcd.drawXBitmap(x, y, whale_r_closed_down, whaleWidth, whaleHeight, TFT_WHITE);
        } else {
          M5.Lcd.drawXBitmap(x, y, whale_r_open_down, whaleWidth, whaleHeight, TFT_WHITE);
        }
        flapdown = false;
      } else {
        if(chewtime && chomp) {
          M5.Lcd.drawXBitmap(x, y, whale_r_closed_up, whaleWidth, whaleHeight, TFT_WHITE);
        } else {
          M5.Lcd.drawXBitmap(x, y, whale_r_open_up, whaleWidth, whaleHeight, TFT_WHITE);
        }      
        flapdown = true;
      }
      
      if(!isbubble){
        isbubble = true;
        bubblex = x + 70;
        bubbley = y - 4;
        bubblesize = 1;
      }
      
      if(isbubble) {
        M5.Lcd.drawCircle(bubblex, bubbley, bubblesize, TFT_WHITE);
        bubbley = bubbley - 8;
        bubblesize = bubblesize + 1;
        bubblesize = min(3, bubblesize);
      }

      if(bubbley <= -50) {
        isbubble = false;
      }


    if(chewtime) {
      chewcount = chewcount - 1;
      if(chomp) {
        chomp = false;
      } else {
        chomp = true;
      }
    }
    if(chewtime && chewcount <= 0){
      chewtime = false;
    }

  }
}
