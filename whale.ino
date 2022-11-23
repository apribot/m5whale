// it's a whale, you can feed em and they love it.


#include "xbm.h"             

#include <M5StickC.h>       

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

bool eating = false;
int shrimptick = 0;

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

  if(ticks < 100){
    M5.update(); 
    if (M5.BtnA.wasPressed()) {
      if(asleep) {
        asleep = false;
        sleeptick = 0;
        M5.Axp.ScreenBreath(10);
      } else {
        sleeptick = 0;
        if (!eating) {
          chewtime = true;
          chewcount = 5;
          chomp = true;
          eating = true;
          shrimptick = 4;
        }
      }

    }    
    delay(10);
    ticks = ticks + 1;
  } else {
    ticks = 0;

    if(eating) {
      x = x + 4;
      if(y > M5.Lcd.height() - (whaleHeight / 2) ) {
        y = y + 4;
      } else {
        y = y - 4;
      }
    } else {
      x = x + ((random(3) - 1)*4);
      y = y + ((random(3) - 1)*4);
    }



    x = max(min(x, M5.Lcd.width() - whaleWidth - shrimpWidth), 0);
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
        M5.Lcd.drawXBitmap(x, y, whale_r_closed_down, whaleWidth, whaleHeight, TFT_NAVY);
      } else {
        M5.Lcd.drawXBitmap(x, y, whale_r_open_down, whaleWidth, whaleHeight, TFT_NAVY);
      }
      flapdown = false;
    } else {
      if(chewtime && chomp) {
        M5.Lcd.drawXBitmap(x, y, whale_r_closed_up, whaleWidth, whaleHeight, TFT_NAVY);
      } else {
        M5.Lcd.drawXBitmap(x, y, whale_r_open_up, whaleWidth, whaleHeight, TFT_NAVY);
      }      
      flapdown = true;
    }
    
    // yeah i know, i'm tired.
    if(eating) {
      if(shrimptick == 4) {
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimpfill1, shrimpWidth, shrimpHeight, TFT_PINK);
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimp1, shrimpWidth, shrimpHeight, TFT_MAROON);
      } else if (shrimptick == 3) {
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimpfill2, shrimpWidth, shrimpHeight, TFT_PINK);
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimp2, shrimpWidth, shrimpHeight, TFT_MAROON);
      } else if (shrimptick == 2) {
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimpfill3, shrimpWidth, shrimpHeight, TFT_PINK);
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimp3, shrimpWidth, shrimpHeight, TFT_MAROON);
      } else if (shrimptick == 1) {
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimpfill4, shrimpWidth, shrimpHeight, TFT_PINK);
        M5.Lcd.drawXBitmap(M5.Lcd.width() - shrimpWidth, (M5.Lcd.height() / 2) - 8, shrimp4, shrimpWidth, shrimpHeight, TFT_MAROON);
      }
      shrimptick = shrimptick - 1;
      if(shrimptick < 1) {
        eating = false;
      }
    }
    
    if(!isbubble){
      isbubble = true;
      bubblex = x + 70;
      bubbley = y - 4;
      bubblesize = 1;
    }
    
    if(isbubble) {
      M5.Lcd.drawCircle(bubblex, bubbley, bubblesize, TFT_BLUE);
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
      // so lazy, sorry.
      M5.Lcd.drawXBitmap(x + 58, y + 19, heart, heartWidth, heartHeight, TFT_PINK);
      delay(1000);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.drawXBitmap(x, y, whale_r_open_up, whaleWidth, whaleHeight, TFT_NAVY);
      delay(1000);
      M5.Lcd.drawXBitmap(x + 58, y + 19, heart, heartWidth, heartHeight, TFT_PINK);
      delay(1000);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.drawXBitmap(x, y, whale_r_open_up, whaleWidth, whaleHeight, TFT_NAVY);
      delay(1000);
      M5.Lcd.drawXBitmap(x + 58, y + 19, heart, heartWidth, heartHeight, TFT_PINK);
      delay(1000);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.drawXBitmap(x, y, whale_r_open_up, whaleWidth, whaleHeight, TFT_NAVY);        
    }

  }
}
