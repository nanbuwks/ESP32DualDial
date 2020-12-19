#include "SPI.h"
// #include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <RotaryEncoder.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
// #include <Fonts/DSEG7Classic_Regular30pt7b.h>

#define TFT_RST 16
#define TFT_DC 17
#define TFT_CS 5
#define PUMP_PIN 15
#define OZON0_PIN 21
#define OZON1_PIN 32
#define OZON2_PIN 33
#define FAN_PIN 22
#define ENCODER1_A_PIN 26
#define ENCODER1_B_PIN 27
#define ENCODER1_SWITCH_PIN 25
#define ENCODER2_A_PIN 12
#define ENCODER2_B_PIN 13
#define ENCODER2_SWITCH_PIN 14
#define TFT_BACKLIGHT_PIN 4

RTC_DATA_ATTR int bootCount = 0;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_RST);
RotaryEncoder encoder1(ENCODER1_A_PIN,ENCODER1_B_PIN);
RotaryEncoder encoder2(ENCODER2_A_PIN,ENCODER2_B_PIN);



struct LABEL {
  int x1;
  int y1;
  int xlength;
  int ylength;
  int fgcolor;
  int bgcolor;
  String text;
  int scale;
  GFXfont font;
};

LABEL notifyTitle = {30, 70,240,40,ILI9341_BLACK ,ILI9341_YELLOW,"REVONISER",1,FreeSansBold12pt7b};
LABEL notifyVersion  = {40,130,240,40,ILI9341_BLACK,ILI9341_WHITE ,"URN-X",1,FreeSansBold24pt7b};
LABEL notifyCel  = {70,270,0,40,ILI9341_YELLOW,ILI9341_BLACK ,"o",1,FreeSansBold12pt7b};
LABEL notifyHemi  = {130,280,100,40,ILI9341_YELLOW,ILI9341_BLACK ,"78%",1,FreeSansBold24pt7b};
LABEL notifyTemp  = {130,280,100,40,ILI9341_YELLOW,ILI9341_BLACK ,"78%",1,FreeSansBold24pt7b};

LABEL timetitle  = {  20,  20,120,40,ILI9341_BLACK,ILI9341_WHITE, " TIME: ",1,FreeSansBold12pt7b};
LABEL timeRemain = {60,100,200,40,ILI9341_BLACK,ILI9341_WHITE,    " 1:30:00",1,FreeSansBold24pt7b};
LABEL timeState  = {  20, 60,100,40,ILI9341_BLACK,ILI9341_WHITE,   "start at",1,FreeSansBold12pt7b};
LABEL timeOzon   = { 120,180,80,40,ILI9341_BLACK,ILI9341_WHITE,   "OZON:",1,FreeSansBold12pt7b};
LABEL timePercent= {200,180,100,40,ILI9341_BLACK,ILI9341_WHITE," 20%",1,FreeSansBold12pt7b};

LABEL settitle = {0,0,150,50,ILI9341_BLACK,ILI9341_WHITE,"DOORPLATE:",1,FreeSansBold12pt7b};
LABEL setnode1 = {30,100,100,30,ILI9341_BLACK,ILI9341_WHITE,"PLATE(1)",1,FreeSansBold12pt7b};
LABEL setCONNECT = {0,280,100,40,ILI9341_BLACK,ILI9341_WHITE,"SCAN",1,FreeSansBold12pt7b};
LABEL setRETURN = {130,280,100,40,ILI9341_BLACK,ILI9341_WHITE,"RETURN",1,FreeSansBold12pt7b};


LABEL scantitle = {0,0,150,50,ILI9341_BLACK,ILI9341_WHITE,"SCAN:",1,FreeSansBold12pt7b};
LABEL scannode1 = {50,80,120,30,ILI9341_BLACK,ILI9341_WHITE,"PLATE(1)",1,FreeSansBold12pt7b};
LABEL scannode2 = {50,110,120,30,ILI9341_BLACK,ILI9341_WHITE,"PLATE(2)",1,FreeSansBold12pt7b};
LABEL scannode3 = {50,140,120,30,ILI9341_BLACK,ILI9341_WHITE,"PLATE(3)",1,FreeSansBold12pt7b};
LABEL scannode4 = {50,170,120,30,ILI9341_BLACK,ILI9341_WHITE,"PLATE(4)",1,FreeSansBold12pt7b};


LABEL m1title1 = {0,0,150,24,ILI9341_BLACK,ILI9341_BLUE,"UPTIME:",1,FreeSansBold12pt7b};
LABEL m110 = {30,24,220,24,ILI9341_BLACK,ILI9341_BLUE,"PUMP    00:00:00",1,FreeSansBold12pt7b};
LABEL m111 = {30,48,220,24,ILI9341_BLACK,ILI9341_BLUE,"OZON    00:00:00",1,FreeSansBold12pt7b};
LABEL m112 = {30,72,220,24,ILI9341_BLACK,ILI9341_BLUE,"FAN     00:00:00",1,FreeSansBold12pt7b};
LABEL m113 = {30,96,220,24,ILI9341_BLACK,ILI9341_BLUE,"ON COUNT       0",1,FreeSansBold12pt7b};
LABEL m1title2 = {20,120,250,24,ILI9341_BLACK,ILI9341_BLUE,"FORCE OPERATION:",1,FreeSansBold12pt7b};
LABEL m120 = {30,144,220,24,ILI9341_BLACK,ILI9341_BLUE,"PUMP        OFF",1,FreeSansBold12pt7b};
LABEL m121 = {30,168,220,24,ILI9341_BLACK,ILI9341_BLUE,"OZON 1      OFF",1,FreeSansBold12pt7b};
LABEL m122 = {30,192,220,24,ILI9341_BLACK,ILI9341_BLUE,"OZON 2      OFF",1,FreeSansBold12pt7b};
LABEL m123 = {30,216,220,24,ILI9341_BLACK,ILI9341_BLUE,"OZON 3      OFF",1,FreeSansBold12pt7b};



LABEL m2title1 = {0,0,150,24,ILI9341_BLACK,ILI9341_BLUE,"CHECK MODE:",1,FreeSansBold12pt7b};
LABEL m210 = {50, 24,220,24,ILI9341_BLACK,ILI9341_BLUE,"PUMP          ON",1,FreeSansBold12pt7b};
LABEL m211 = {50, 48,220,24,ILI9341_BLACK,ILI9341_BLUE,"OZON1         ON",1,FreeSansBold12pt7b};
LABEL m212 = {50, 72,220,24,ILI9341_BLACK,ILI9341_BLUE,"OZON2         ON",1,FreeSansBold12pt7b};
LABEL m213 = {50, 96,220,24,ILI9341_BLACK,ILI9341_BLUE,"OZON3         ON",1,FreeSansBold12pt7b};
LABEL m214 = {50,120,250,24,ILI9341_BLACK,ILI9341_BLUE," TIMER   CHECK  ",1,FreeSansBold12pt7b};
LABEL m215 = {50,144,220,24,ILI9341_BLACK,ILI9341_BLUE," BUZZER  CHECK  ",1,FreeSansBold12pt7b};
LABEL m216 = {50,168,220,24,ILI9341_BLACK,ILI9341_BLUE," ENCODER CHECK  ",1,FreeSansBold12pt7b};
LABEL m217 = {50,192,220,24,ILI9341_BLACK,ILI9341_BLUE," L/R SWITCH     ",1,FreeSansBold12pt7b};
LABEL m218 = {20,216,220,24,ILI9341_BLACK,ILI9341_BLUE,"L   0      R    0",1,FreeSansBold12pt7b};


LABEL timeLabels[3]={ timeRemain,timeOzon,timePercent};
LABEL setLabels[2]={ setCONNECT,setRETURN};
LABEL scanLabels[4]={ scannode1,scannode2,scannode3,scannode4};


String mode="set";  // set,run,resetting
int runRemain;      // remain countdown second
int settingRemain;   // setting second
int autoExitCounter; // countdown second
int timercounter=0;
int ozonpercent=0;
int ozondisplay=30;
static int encoder1Pushed=0;   // you must turn 0 after button check
static int encoder1Pushing=0;
static int encoder2Pushed=0;   // you must turn 0 after button check
static int encoder2Pushing=0;


hw_timer_t * timer = NULL;

void IRAM_ATTR onTimer() {  // each 20msec
    encoder1.tick(); // just call tick() to check the state.
  encoder2.tick(); // just call tick() to check the state.
  timercounter++;
  if ( ozonpercent == timercounter % 100 )
     digitalWrite(OZON0_PIN,HIGH);  
  if ( 0           == timercounter % 100 )  
     digitalWrite(OZON0_PIN,LOW);  
  if ( ozonpercent == ( timercounter + 33 ) % 100 ) 
     digitalWrite(OZON1_PIN,HIGH);  
  if ( 0           == ( timercounter + 33 ) % 100 )   
     digitalWrite(OZON1_PIN,LOW);  
  if ( ozonpercent == ( timercounter + 66 ) % 100 ) 
     digitalWrite(OZON2_PIN,HIGH);  
  if ( 0           == ( timercounter + 66 ) % 100 )   
     digitalWrite(OZON2_PIN,LOW);  
  if ( 0 == timercounter % 5 )
     countdown(); 
}

void IRAM_ATTR ISR() {
  encoder1.tick(); // just call tick() to check the state.
  encoder2.tick(); // just call tick() to check the state.
  
}



void IRAM_ATTR RELEASE1() {
  static unsigned long nowtime;
  static unsigned long oldtime=0;
  nowtime=millis();
  if ( 150 < ( nowtime - oldtime )){
  Serial.print("released!!!!!!!!!!");
  Serial.print(oldtime);
  Serial.print("  ");
  Serial.println(nowtime);
    Serial.print("1release");
    encoder1Pushed=1;
  
    encoder1Pushing=0;
  }
      Serial.print(" ");
      Serial.print(encoder1Pushed);
      Serial.print(" ");
      Serial.print(encoder1Pushing);
      Serial.print(" ");
      Serial.print(encoder2Pushed);
      Serial.print(" ");
      Serial.print(encoder2Pushing);
      Serial.println(" ");
    
  oldtime=nowtime;  
}
void IRAM_ATTR RELEASE2() {
  static unsigned long nowtime;
  static unsigned long oldtime=0;
  nowtime=millis();
  if ( 150 < ( nowtime - oldtime )){
  Serial.print("released!!!!!!!!!!");
  Serial.print(oldtime);
  Serial.print("  ");
  Serial.println(nowtime);
    Serial.print("2release");
    encoder2Pushed=1;
  
    encoder2Pushing=0;
  }
      Serial.print(" ");
      Serial.print(encoder1Pushed);
      Serial.print(" ");
      Serial.print(encoder1Pushing);
      Serial.print(" ");
      Serial.print(encoder2Pushed);
      Serial.print(" ");
      Serial.print(encoder2Pushing);
      Serial.println(" ");
    
  oldtime=nowtime;  
}

void countdown(){
  static int countdowncounter=0;
  countdowncounter++;
  //Serial.print(countdowncounter);
  // each 100 msec.

   if ( mode=="run" ){ 
//     Serial.println(countdowncounter);
     if ( 0 == countdowncounter % 10 )
     {
       timetitle.fgcolor=ILI9341_GREEN;
       labelText(timetitle);
     }
     if ( 5 == countdowncounter % 10 )
     {
       timetitle.fgcolor=ILI9341_BLACK;
       labelText(timetitle);
     }
     if ( 0 == countdowncounter % 10 )
     {
       runRemain--;
       if ( 0 > runRemain )
          runRemain=0;
       char buf[20];
       sprintf(buf,"%d:%02d:%02d",runRemain/3600,(runRemain/60)%60,runRemain%60);
       timeRemain.text=buf;
       labelText(timeRemain);
     }
   }
   if ( mode=="resetting" ){ 
     if ( 0 == countdowncounter % 5 )
     {
       timetitle.fgcolor=ILI9341_GREEN;
       labelText(timetitle);
     }
     if ( 2 == countdowncounter % 5 )
     {
       timetitle.fgcolor=ILI9341_BLACK;
       labelText(timetitle);
     }
     if ( 0 == countdowncounter % 10 )
     {
       runRemain--;
       if ( 0 > runRemain )
          runRemain=0;
       autoExitCounter--;
       if ( 0 > autoExitCounter )
          autoExitCounter=0;
     }
   
     ozondraw(ozondisplay);
     char buf[20];
     sprintf(buf,"%d:%02d:%02d",settingRemain/3600,(settingRemain/60)%60,settingRemain%60);
     timeRemain.text=buf;
     labelText(timeRemain);
      
   }

}

void selectLabelText(LABEL label) {
  unsigned long start = micros();
  tft.fillRect(label.x1, label.y1, label.xlength,label.ylength, label.fgcolor);
  int16_t xstart,ystart;
  uint16_t w,h;
  tft.setFont( &label.font);
  tft.setTextSize(label.scale);
  tft.getTextBounds( label.text,0,0,&xstart,&ystart,&w,&h);
  int xtextbase,ytextbase;
  xtextbase = label.x1+label.xlength/2 - w/2;
  ytextbase = label.y1+label.ylength/2 + h/2;
  tft.setCursor(xtextbase, ytextbase);
  tft.setTextColor(label.bgcolor);
  tft.println(label.text);  
}
void frameText(LABEL label) {
  unsigned long start = micros();
  tft.drawRect(label.x1, label.y1, label.xlength,label.ylength, label.bgcolor);
  int16_t xstart,ystart;
  uint16_t w,h;
  tft.setFont( &label.font);
  tft.setTextSize(label.scale);
  tft.getTextBounds( label.text,0,0,&xstart,&ystart,&w,&h);
  int xtextbase,ytextbase;
  xtextbase = label.x1+label.xlength/2 - w/2;
  ytextbase = label.y1+label.ylength/2 + h/2;
  tft.setCursor(xtextbase, ytextbase);
  tft.setTextColor(label.fgcolor);
  tft.println(label.text);  
}

void labelText(LABEL label) {
  unsigned long start = micros();
  tft.fillRect(label.x1, label.y1, label.xlength,label.ylength, label.bgcolor);
  int16_t xstart,ystart;
  uint16_t w,h;
  tft.setFont( &label.font);
  tft.setTextSize(label.scale);
  tft.getTextBounds( label.text,0,0,&xstart,&ystart,&w,&h);
  int xtextbase,ytextbase;
  xtextbase = label.x1+label.xlength/2 - w/2;
  ytextbase = label.y1+label.ylength/2 + h/2;
  tft.setCursor(xtextbase, ytextbase);
  tft.setTextColor(label.fgcolor);
  tft.println(label.text);  
}

void start(int percent){
  
 ozonpercent= percent;

}
void stop(){
  ozonpercent=0;
  mode="stop";
  timeRemain.text="0:00:00";
  for ( int i = 0; i< 3; i++)
  {
    timeRemain.fgcolor=ILI9341_GREEN;
    labelText(timeRemain);
    delay(500);
    timeRemain.fgcolor=ILI9341_BLACK;
    labelText(timeRemain);
    delay(500);
  }
}


void dispTempHemi() {
  tft.fillRect(0,280,240,320,ILI9341_BLACK);
  labelText(notifyTemp);
  labelText(notifyCel);  
  labelText(notifyHemi);
}
void notify() {
  tft.fillScreen(ILI9341_WHITE);
  labelText(notifyTitle);
  labelText(notifyVersion);
//  dispTempHemi();
  delay(2000);

}

int resetting(){
  mode="";
    unsigned long start = micros();
  static int timemin = 30;
  labelText(settitle);
  labelText(setnode1);
  int startpos1 = encoder1.getPosition();
  int pos1;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  ozondisplay=newPos2;
  pos1=newPos1;
  pos2=newPos2;
  
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="REMAIN:";
  labelText(timetitle);
  labelText(timeRemain);
  labelText(timeOzon);
  labelText(timePercent);
  settingRemain = runRemain;
  mode="resetting";
  autoExitCounter=5;
  while ( 1 )
  {
    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
    Serial.print(newPos1);
    Serial.print("            ");
    Serial.println(newPos2);
    // ozon percent setting 
    
    if (pos2 != newPos2) {
      autoExitCounter=5;
      Serial.print(" pos2  ");
      Serial.print(pos2);
      Serial.print("  ");
      Serial.print(newPos2);      
      if ( 100 < newPos2 ){
          newPos2 = 100;
          encoder2.setPosition(100);
      }
      if ( 0 >  newPos2 ){
          newPos2 = 0;
          encoder2.setPosition(0);
      }
      pos2 = newPos2;
      ozondisplay=newPos2;     
    }

    // time setting 
    if (pos1 != newPos1) {
      autoExitCounter=5;
      Serial.print(" pos1  ");
      Serial.print(pos1);
      Serial.print("  ");
      Serial.print(newPos1);
      if ( 0 >  newPos1 ){
          newPos1 = 0;
          encoder1.setPosition(0);
      }
      if ( 0 <=  newPos1  && newPos1 <= 600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 10;
          encoder1.setPosition(newPos1);
      }
      if ( 600 <  newPos1  && newPos1 <= 1200 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 30;
          encoder1.setPosition(newPos1);
      }
      if ( 1200 <  newPos1  && newPos1 <= 3600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 60;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 <  newPos1  && newPos1 <= 3600*6 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 600;
          encoder1.setPosition(newPos1);
      }
      if ( 3600*6 <  newPos1  &&  newPos1 <= 3600*12 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 1800;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 * 12 < newPos1 ){
          newPos1 = 3600 * 12;
          encoder1.setPosition(3600 * 12);
      }
      pos1 = newPos1;

      Serial.print("  ");
      Serial.println(newPos1);
      settingRemain=newPos1;

    }
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit
      if (1 == encoder1Pushed )
      {
         ozonpercent=ozondisplay;
         runRemain=settingRemain;
         encoder1Pushed=0;
         return (1);
      }
      if (1 == encoder2Pushed )
      {
         encoder2Pushed=0;
         return (2);
      }
    }
    if ( 0 == runRemain )
    {
       return(0);
    }  
    if ( 0 == autoExitCounter)
    {
       return(0);  
    }
    
    delay(50);
    
  }

  
  }

int programmode1resetting(){
  mode="";
    unsigned long start = micros();
  static int timemin = 30;
  labelText(settitle);
  labelText(setnode1);
  int startpos1 = encoder1.getPosition();
  int pos1;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  ozondisplay=newPos2;
  pos1=newPos1;
  pos2=newPos2;
  
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="REMAIN:";
  labelText(timetitle);
  labelText(timeRemain);
  labelText(timeOzon);
  labelText(timePercent);
  settingRemain = runRemain;
  mode="programmode1";
  autoExitCounter=5;
  while ( 1 )
  {
    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
    Serial.print(newPos1);
    Serial.print("            ");
    Serial.println(newPos2);
    // ozon percent setting 
    
    if (pos2 != newPos2) {
      autoExitCounter=5;
      Serial.print(" pos2  ");
      Serial.print(pos2);
      Serial.print("  ");
      Serial.print(newPos2);      
      if ( 100 < newPos2 ){
          newPos2 = 100;
          encoder2.setPosition(100);
      }
      if ( 0 >  newPos2 ){
          newPos2 = 0;
          encoder2.setPosition(0);
      }
      pos2 = newPos2;
      ozondisplay=newPos2;     
    }

    // time setting 
    if (pos1 != newPos1) {
      autoExitCounter=5;
      Serial.print(" pos1  ");
      Serial.print(pos1);
      Serial.print("  ");
      Serial.print(newPos1);
      if ( 0 >  newPos1 ){
          newPos1 = 0;
          encoder1.setPosition(0);
      }
      if ( 0 <=  newPos1  && newPos1 <= 600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 10;
          encoder1.setPosition(newPos1);
      }
      if ( 600 <  newPos1  && newPos1 <= 1200 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 30;
          encoder1.setPosition(newPos1);
      }
      if ( 1200 <  newPos1  && newPos1 <= 3600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 60;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 <  newPos1  && newPos1 <= 3600*6 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 600;
          encoder1.setPosition(newPos1);
      }
      if ( 3600*6 <  newPos1  &&  newPos1 <= 3600*12 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 1800;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 * 12 < newPos1 ){
          newPos1 = 3600 * 12;
          encoder1.setPosition(3600 * 12);
      }
      pos1 = newPos1;

      Serial.print("  ");
      Serial.println(newPos1);
      settingRemain=newPos1;

    }
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit
      if (1 == encoder1Pushed )
      {
         ozonpercent=ozondisplay;
         runRemain=settingRemain;
         encoder1Pushed=0;
         return (1);
      }
      if (1 == encoder2Pushed )
      {
         encoder2Pushed=0;
         return (2);
      }
    }
    if ( 0 == runRemain )
    {
       return(0);
    }  
    if ( 0 == autoExitCounter)
    {
       return(0);  
    }
    
    delay(50);
    
  }

  
}

int programmode2resetting(){
  mode="";
    unsigned long start = micros();
  static int timemin = 30;
  labelText(settitle);
  labelText(setnode1);
  int startpos1 = encoder1.getPosition();
  int pos1;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  ozondisplay=newPos2;
  pos1=newPos1;
  pos2=newPos2;
  
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="REMAIN:";
  labelText(timetitle);
  labelText(timeRemain);
  labelText(timeOzon);
  labelText(timePercent);
  settingRemain = runRemain;
  mode="programmode2";
  autoExitCounter=5;
  while ( 1 )
  {
    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
    Serial.print(newPos1);
    Serial.print("            ");
    Serial.println(newPos2);
    // ozon percent setting 
    
    if (pos2 != newPos2) {
      autoExitCounter=5;
      Serial.print(" pos2  ");
      Serial.print(pos2);
      Serial.print("  ");
      Serial.print(newPos2);      
      if ( 100 < newPos2 ){
          newPos2 = 100;
          encoder2.setPosition(100);
      }
      if ( 0 >  newPos2 ){
          newPos2 = 0;
          encoder2.setPosition(0);
      }
      pos2 = newPos2;
      ozondisplay=newPos2;     
    }

    // time setting 
    if (pos1 != newPos1) {
      autoExitCounter=5;
      Serial.print(" pos1  ");
      Serial.print(pos1);
      Serial.print("  ");
      Serial.print(newPos1);
      if ( 0 >  newPos1 ){
          newPos1 = 0;
          encoder1.setPosition(0);
      }
      if ( 0 <=  newPos1  && newPos1 <= 600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 10;
          encoder1.setPosition(newPos1);
      }
      if ( 600 <  newPos1  && newPos1 <= 1200 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 30;
          encoder1.setPosition(newPos1);
      }
      if ( 1200 <  newPos1  && newPos1 <= 3600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 60;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 <  newPos1  && newPos1 <= 3600*6 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 600;
          encoder1.setPosition(newPos1);
      }
      if ( 3600*6 <  newPos1  &&  newPos1 <= 3600*12 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 1800;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 * 12 < newPos1 ){
          newPos1 = 3600 * 12;
          encoder1.setPosition(3600 * 12);
      }
      pos1 = newPos1;

      Serial.print("  ");
      Serial.println(newPos1);
      settingRemain=newPos1;

    }
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit
      if (1 == encoder1Pushed )
      {
         ozonpercent=ozondisplay;
         runRemain=settingRemain;
         encoder1Pushed=0;
         return (1);
      }
      if (1 == encoder2Pushed )
      {
         encoder2Pushed=0;
         return (2);
      }
    }
    if ( 0 == runRemain )
    {
       return(0);
    }  
    if ( 0 == autoExitCounter)
    {
       return(0);  
    }
    
    delay(50);
    
  }

  
}
void ozondraw(int percent){

      if ( 30 <  percent ){
         tft.fillRect(0,0,320,15, ILI9341_RED );
         tft.fillRect(0,0,15,240, ILI9341_RED );
         tft.fillRect(0,225,320,15, ILI9341_RED );
         tft.fillRect(305,0,15,240, ILI9341_RED );
         timePercent.bgcolor=ILI9341_RED;
          
      }
      if ( 31 >  percent ){
         tft.fillRect(0,0,320,15, ILI9341_WHITE );
         tft.fillRect(0,0,15,240, ILI9341_WHITE );
         tft.fillRect(0,225,320,15, ILI9341_WHITE );
         tft.fillRect(305,0,15,240, ILI9341_WHITE );
         timePercent.bgcolor=ILI9341_WHITE;
          
      }
      
    //  Serial.print("percent=");
    //  Serial.print(percent);
    //  Serial.println();
      timePercent.text=String(percent) +" %";
      labelText(timePercent);

  
}
int run(){
  int startpos1 = encoder1.getPosition();
  int pos1 = startpos1;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2 = startpos2;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="REMAIN:";
  //labelText(timetitle);
  labelText(timeRemain);
  labelText(timeOzon);
  labelText(timePercent);
  runRemain = encoder1.getPosition();
  delay(800);
  mode="run";
  start(newPos2);  // start with ozon percent
  while(1){
    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
    // Serial.print("            ");
    // Serial.println(newPos2);

    // ozon percent setting 
    if ( pos2 != newPos2 || pos1 != newPos1 ) {
      Serial.println("mode=resetting enter");
      int returncode = resetting();
      Serial.println("mode=resetting exit");
      if ( 1 == returncode )
      {
        Serial.println("mode=resetting exit 1");
        // ozonpercent=ozondisplay;
        // runRemain=settingRemain;
        pos2 = ozonpercent;
        pos1 = runRemain;
        newPos1=pos1;
        newPos2=pos2;
        encoder1.setPosition(pos1);
        encoder2.setPosition(pos2);
        Serial.print("runRemain=");
        Serial.println(runRemain);
        mode="run";
      } else {
        Serial.println("mode=resetting exit without 1 ");
        newPos1 = pos1;
        newPos2 = pos2;
        encoder1.setPosition(pos1);
        encoder2.setPosition(pos2);
        mode="run";
      }
      Serial.println("mode=resetting exited");
    }
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit
  //    if (1 == encoder1Pushed )
  //    {
  //       encoder1Pushed=0;
  //       stop();
  //       return (1);
  //    }
      if (1 == encoder2Pushed )
      {
         encoder1Pushed=0;
         encoder2Pushed=0;
         stop();
         return (2);
      }
    }

    if ( 0 == runRemain )
    {
       encoder1Pushed=0;
       stop();
       return(0);
    }  
  }
}
int programmode1(){
  int startpos1 = encoder1.getPosition();
  int pos1 = startpos1;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2 = startpos2;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="REMAIN:";
  //labelText(timetitle);
  labelText(timeRemain);
  labelText(timeOzon);
  labelText(timePercent);
  runRemain = encoder1.getPosition();
  delay(800);
  mode="run";
  start(newPos2);  // start with ozon percent
  while(1){
    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
    // Serial.print("            ");
    // Serial.println(newPos2);

    // ozon percent setting 
    if ( pos2 != newPos2 || pos1 != newPos1 ) {
      Serial.println("mode=programmode1resetting enter");
      int returncode = programmode1resetting();
      Serial.println("mode=programmode1resetting exit");
      if ( 1 == returncode )
      {
        Serial.println("mode=programmode1resetting exit 1");
        // ozonpercent=ozondisplay;
        // runRemain=settingRemain;
        pos2 = ozonpercent;
        pos1 = runRemain;
        newPos1=pos1;
        newPos2=pos2;
        encoder1.setPosition(pos1);
        encoder2.setPosition(pos2);
        Serial.print("runRemain=");
        Serial.println(runRemain);
        mode="run";
      } else {
        Serial.println("mode=programmode1resetting exit without 1 ");
        newPos1 = pos1;
        newPos2 = pos2;
        encoder1.setPosition(pos1);
        encoder2.setPosition(pos2);
        mode="run";
      }
      Serial.println("mode=programmode1resetting exited");
    }
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit
  //    if (1 == encoder1Pushed )
  //    {
  //       encoder1Pushed=0;
  //       stop();
  //       return (1);
  //    }
      if (1 == encoder2Pushed )
      {
         encoder1Pushed=0;
         encoder2Pushed=0;
         stop();
         return (2);
      }
    }

    if ( 0 == runRemain )
    {
       encoder1Pushed=0;
       stop();
       return(0);
    }  
  }
}
int programmode2(){
  int startpos1 = encoder1.getPosition();
  int pos1 = startpos1;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2 = startpos2;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="REMAIN:";
  //labelText(timetitle);
  labelText(timeRemain);
  labelText(timeOzon);
  labelText(timePercent);
  runRemain = encoder1.getPosition();
  delay(800);
  mode="run";
  start(newPos2);  // start with ozon percent
  while(1){
    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
    // Serial.print("            ");
    // Serial.println(newPos2);

    // ozon percent setting 
    if ( pos2 != newPos2 || pos1 != newPos1 ) {
      Serial.println("mode=programmode2resetting enter");
      int returncode = programmode2resetting();
      Serial.println("mode=programmode2resetting exit");
      if ( 1 == returncode )
      {
        Serial.println("mode=programmode2resetting exit 1");
        // ozonpercent=ozondisplay;
        // runRemain=settingRemain;
        pos2 = ozonpercent;
        pos1 = runRemain;
        newPos1=pos1;
        newPos2=pos2;
        encoder1.setPosition(pos1);
        encoder2.setPosition(pos2);
        Serial.print("runRemain=");
        Serial.println(runRemain);
        mode="run";
      } else {
        Serial.println("mode=programmode2resetting exit without 1 ");
        newPos1 = pos1;
        newPos2 = pos2;
        encoder1.setPosition(pos1);
        encoder2.setPosition(pos2);
        mode="run";
      }
      Serial.println("mode=programmode2resetting exited");
    }
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit
  //    if (1 == encoder1Pushed )
  //    {
  //       encoder1Pushed=0;
  //       stop();
  //       return (1);
  //    }
      if (1 == encoder2Pushed )
      {
         encoder1Pushed=0;
         encoder2Pushed=0;
         stop();
         return (2);
      }
    }

    if ( 0 == runRemain )
    {
       encoder1Pushed=0;
       stop();
       return(0);
    }  
  }
}
int set() {
  mode="set";
  unsigned long start = micros();
  static int timemin = 30;
  int startpos1 = encoder1.getPosition();
  int pos1 = 100;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2 = 100;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  
  Serial.println("mode=set");
  timetitle.fgcolor=ILI9341_BLACK;
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="TIME:";
  labelText(timetitle);
  labelText(timeRemain);
  labelText(timeOzon);
  labelText(timePercent);
  delay(800);
  encoder2.setPosition(20);
  encoder1.setPosition(5999);
  newPos1 = encoder1.getPosition();
  pos1 = 6000;    
  while ( 1 )
  {

    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
  //  Serial.print("            ");
  //  Serial.println(newPos2);
    // ozon percent setting 
    if (pos2 != newPos2) {
      if ( 100 < newPos2 ){
          newPos2 = 100;
          encoder2.setPosition(100);
      }
      if ( 0 >  newPos2 ){
          newPos2 = 0;
          encoder2.setPosition(0);
      }
      pos2=newPos2;
      ozondraw(newPos2);
      delay(100);

    }

    // time setting 
    if (pos1 != newPos1) {
      Serial.print(pos1);
      Serial.print("  ");
      Serial.print(newPos1);
      if ( 0 >  newPos1 ){
          newPos1 = 0;
          encoder1.setPosition(0);
      }
      if ( 0 <=  newPos1  && newPos1 <= 600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 10;
          encoder1.setPosition(newPos1);
      }
      if ( 600 <  newPos1  && newPos1 <= 1200 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 30;
          encoder1.setPosition(newPos1);
      }
      if ( 1200 <  newPos1  && newPos1 <= 3600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 60;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 <  newPos1  && newPos1 <= 3600*6 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 600;
          encoder1.setPosition(newPos1);
      }
      if ( 3600*6 <  newPos1  &&  newPos1 <= 3600*12 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 1800;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 * 12 < newPos1 ){
          newPos1 = 3600 * 12;
          encoder1.setPosition(3600 * 12);
      }
      Serial.print("  ");
      Serial.println(newPos1);
      char buf[20];
      sprintf(buf,"%d:%02d:%02d",newPos1/3600,(newPos1/60)%60,newPos1%60);
      pos1 = newPos1;
      timeRemain.text=buf;
      labelText(timeRemain);
    }

    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit

      if (1 == encoder1Pushed && 0 == encoder1Pushing )
      {
         encoder1Pushed=0;
         return (1);
      }
      if (1 == encoder2Pushed && 0 == encoder2Pushing)
      {
         encoder2Pushed=0;
         return (2);
      }
    }
    
    delay(100);
  }
}



int setonstart() {
  mode="onstart";
  unsigned long start = micros();
  static int timemin = 30;
  int startpos1 = encoder1.getPosition();
  int pos1 = 100;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2 = 100;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  
  Serial.println("mode=ontimer");
  timetitle.fgcolor=ILI9341_BLACK;
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="ONTIMER:";
  labelText(timetitle);
  labelText(timeRemain);
  timeState.text="start at";
  labelText(timeState);
  labelText(timeOzon);
  labelText(timePercent);
  delay(800);
  encoder2.setPosition(20);
  encoder1.setPosition(5999);
  newPos1 = encoder1.getPosition();
  pos1 = 6000;    
  while ( 1 )
  {

    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
  //  Serial.print("            ");
  //  Serial.println(newPos2);
    // ozon percent setting 
    if (pos2 != newPos2) {
      if ( 100 < newPos2 ){
          newPos2 = 100;
          encoder2.setPosition(100);
      }
      if ( 0 >  newPos2 ){
          newPos2 = 0;
          encoder2.setPosition(0);
      }
      pos2=newPos2;
      ozondraw(newPos2);
      delay(100);

    }

    // time setting 
    if (pos1 != newPos1) {
      Serial.print(pos1);
      Serial.print("  ");
      Serial.print(newPos1);
      if ( 0 >  newPos1 ){
          newPos1 = 0;
          encoder1.setPosition(0);
      }
      if ( 0 <=  newPos1  && newPos1 <= 600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 10;
          encoder1.setPosition(newPos1);
      }
      if ( 600 <  newPos1  && newPos1 <= 1200 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 30;
          encoder1.setPosition(newPos1);
      }
      if ( 1200 <  newPos1  && newPos1 <= 3600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 60;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 <  newPos1  && newPos1 <= 3600*6 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 600;
          encoder1.setPosition(newPos1);
      }
      if ( 3600*6 <  newPos1  &&  newPos1 <= 3600*12 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 1800;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 * 12 < newPos1 ){
          newPos1 = 3600 * 12;
          encoder1.setPosition(3600 * 12);
      }
      Serial.print("  ");
      Serial.println(newPos1);
      char buf[20];
      sprintf(buf,"%d:%02d:%02d",newPos1/3600,(newPos1/60)%60,newPos1%60);
      pos1 = newPos1;
      timeRemain.text=buf;
      labelText(timeRemain);
    }

    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  

      if (1 == encoder1Pushed && 0 == encoder1Pushing )
      {
         encoder1Pushed=0;
         setonend();
      }
      if (1 == encoder2Pushed && 0 == encoder2Pushing)
      {
         encoder2Pushed=0;
         return (2);
      }
    }
    
    delay(100);
  }
}


int setonend() {
  mode="setonend";
  unsigned long start = micros();
  static int timemin = 30;
  int startpos1 = encoder1.getPosition();
  int pos1 = 100;
  int newPos1 = encoder1.getPosition();
  int startpos2 = encoder2.getPosition();
  int pos2 = 100;
  int newPos2 = encoder2.getPosition();
  int exitflag = 0;
  int selected;
  
  Serial.println("mode=ontimer");
  timetitle.fgcolor=ILI9341_BLACK;
  tft.fillScreen(ILI9341_WHITE);
  timetitle.text="ONTIMER:";
  labelText(timetitle);
  labelText(timeRemain);
  timeState.text="end to";
  labelText(timeState);
  labelText(timeOzon);
  labelText(timePercent);
  delay(800);
  encoder2.setPosition(20);
  encoder1.setPosition(5999);
  newPos1 = encoder1.getPosition();
  pos1 = 6000;    
  while ( 1 )
  {

    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
  //  Serial.print("            ");
  //  Serial.println(newPos2);
    // ozon percent setting 
    if (pos2 != newPos2) {
      if ( 100 < newPos2 ){
          newPos2 = 100;
          encoder2.setPosition(100);
      }
      if ( 0 >  newPos2 ){
          newPos2 = 0;
          encoder2.setPosition(0);
      }
      pos2=newPos2;
      ozondraw(newPos2);
      delay(100);

    }

    // time setting 
    if (pos1 != newPos1) {
      Serial.print(pos1);
      Serial.print("  ");
      Serial.print(newPos1);
      if ( 0 >  newPos1 ){
          newPos1 = 0;
          encoder1.setPosition(0);
      }
      if ( 0 <=  newPos1  && newPos1 <= 600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 10;
          encoder1.setPosition(newPos1);
      }
      if ( 600 <  newPos1  && newPos1 <= 1200 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 30;
          encoder1.setPosition(newPos1);
      }
      if ( 1200 <  newPos1  && newPos1 <= 3600 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 60;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 <  newPos1  && newPos1 <= 3600*6 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 600;
          encoder1.setPosition(newPos1);
      }
      if ( 3600*6 <  newPos1  &&  newPos1 <= 3600*12 ){
          newPos1 = pos1 + ( newPos1 - pos1 ) * 1800;
          encoder1.setPosition(newPos1);
      }
      if ( 3600 * 12 < newPos1 ){
          newPos1 = 3600 * 12;
          encoder1.setPosition(3600 * 12);
      }
      Serial.print("  ");
      Serial.println(newPos1);
      char buf[20];
      sprintf(buf,"%d:%02d:%02d",newPos1/3600,(newPos1/60)%60,newPos1%60);
      pos1 = newPos1;
      timeRemain.text=buf;
      labelText(timeRemain);
    }

    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {  // exit

      if (1 == encoder1Pushed && 0 == encoder1Pushing )
      {
         encoder1Pushed=0;
         programmode1();
      }
      if (1 == encoder2Pushed && 0 == encoder2Pushing)
      {
         encoder2Pushed=0;
         return (2);
      }
    }
    
    delay(100);
  }
}

void maintenancemode2(){

   tft.fillScreen(ILI9341_BLUE);
   labelText(m2title1);
   labelText(m210);
   labelText(m211);
   labelText(m212);
   labelText(m213);
   labelText(m214);
   labelText(m215);
   labelText(m216);
   labelText(m217);
   labelText(m218);
   while (1){ 
    delay(10); 
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {
      if (1 == encoder1Pushed )
      {
      }
      if (1 == encoder2Pushed )
      {
      }
    }
    
   }
}

void maintenancemode1(){

   tft.fillScreen(ILI9341_BLUE);
   labelText(m1title1);
   labelText(m1title2);
   labelText(m110);
   labelText(m111);
   labelText(m112);
   labelText(m113);
   labelText(m120);
   labelText(m121);
   labelText(m122);
   labelText(m123);
   while (1){ 
    delay(10); 
    if ( 1 == encoder1Pushed || 1 == encoder2Pushed )
    {
      if (1 == encoder1Pushed )
      {

      }
      if (1 == encoder2Pushed )
      {
         encoder2Pushed=0;
         maintenancemode2();
      }
    }
    
   }
}

void setup() {
  Serial.begin(115200);
  Serial.println("ILI9341 Test!"); 
  pinMode(TFT_BACKLIGHT_PIN,OUTPUT);
  pinMode(ENCODER1_SWITCH_PIN,INPUT_PULLUP);
  pinMode(ENCODER2_SWITCH_PIN,INPUT_PULLUP);
  digitalWrite(TFT_BACKLIGHT_PIN,HIGH);
  tft.begin();
  tft.setRotation(1);
  attachInterrupt(ENCODER1_A_PIN, ISR, CHANGE);   // rotary_encoder
  attachInterrupt(ENCODER1_B_PIN, ISR, CHANGE);   // rotary_encoder
  attachInterrupt(ENCODER1_SWITCH_PIN, RELEASE1, RISING);  // rotary_encoder push switch
  attachInterrupt(ENCODER2_A_PIN, ISR, CHANGE);   // rotary_encoder
  attachInterrupt(ENCODER2_B_PIN, ISR, CHANGE);   // rotary_encoder
  attachInterrupt(ENCODER2_SWITCH_PIN, RELEASE2, RISING);  // rotary_encoder push switch
  
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 20000, true);  // 20m sec
  timerAlarmEnable(timer);
  
  notify();

//  Serial.print(F("Rectangles (filled)      "));
//  Serial.println(testFilledRects(ILI9341_WHITE, ILI9341_BLUE));
//  delay(500);
  if (1 == encoder2Pushed && 1 == encoder1Pushed)
  {
     encoder1Pushed=0;
     encoder2Pushed=0;
     maintenancemode1();  
  }

}

void loop()
{
  static int powerstate=0;
  static int pos1=0;
  static int pos2=0;

  Serial.println("mode=set enter");
  int kekka=set();
  Serial.println("mode=set exited");
  if ( 1 == kekka ){
    Serial.println("mode=run enter");
    run();
    Serial.println("mode=run exited");
  }
  if ( 2 == kekka ){
    setonstart();
  }


}

//-------------------------------------------------------------------------------

void scan() {
  unsigned long start = micros();
  static int timemin = 30;
  tft.fillScreen(ILI9341_WHITE);
  labelText(scantitle);
  int startpos = encoder1.getPosition();
  int pos = 100;
  int newPos = encoder1.getPosition();
  int exitflag = 0;
  int selected;
  while ( 0 == exitflag )
  {
    newPos = encoder1.getPosition();
    Serial.print("            ");
    Serial.println(newPos);
    if (pos != newPos) {
      Serial.print("pos=");
      Serial.print(newPos);
      Serial.println();
      pos = newPos;
      selected=(( pos % 4) + 4 ) % 4; // negative modulo
      for ( int i=0; i<4; i++ ){
        if ( i == selected){ 
          selectLabelText(scanLabels[i]);
        } else {
          labelText(scanLabels[i]);
        }
      }
    }
    if ( 1 == encoder1Pushed ){
      encoder1Pushed = 0;   
      exitflag=1;
    }
    delay(100);
  }
  Serial.print("exit! ");
 }

void time() {

  tft.fillScreen(ILI9341_WHITE);
  labelText(notifyTitle);
  labelText(notifyVersion);
  static int timeminutes = 30;

  delay(1000);
  encoder1.setPosition(0);
  int startpos1 = encoder1.getPosition();
  int pos1 = 100;
  int newPos1 = encoder1.getPosition();
  int exitflag = 0;
  int selected;
  tft.fillScreen(ILI9341_WHITE);
  labelText(timetitle);
//  labelText(timemin);
  while ( 0 == exitflag )
  {
    newPos1 = encoder1.getPosition();
  //  Serial.print("            ");
  //   Serial.println(newPos1);
    if (pos1 != newPos1) {
      Serial.print("pos1=");
      Serial.print(newPos1);
      Serial.println();
      pos1 = newPos1;
      selected=(( pos1 % 3) + 3 ) % 3; // negative modulo
      for ( int i=0; i<3; i++ ){
        if ( i == selected){ 
          selectLabelText(timeLabels[i]);
        } else {
          labelText(timeLabels[i]);
        }
      }
    }
    if ( 1 == encoder1Pushed ){
      encoder1Pushed = 0;   
      switch(selected){
        case 0:
          Serial.print("enter! timeremain=");
          Serial.println(timeRemain.text);
          timeset();
          Serial.print("exited timeremain=");
          Serial.println(timeRemain.text);
          encoder1.setPosition(1);
          pos1=0;
          break;
        case 1:
          countdown();
          break;
        case 2:
          exitflag=1;
          break;
      }
    }
    delay(100);
  }
  Serial.print("exit! ");
}
void timeset() {
  tft.fillScreen(ILI9341_WHITE);
  unsigned long start = micros();
  static int timemin = 30;
  labelText(settitle);
  labelText(setnode1);
  int pos1;
  static int timeseconds;
  int startpos1 = encoder1.getPosition();
//  encoder1.setPosition( timeRemainMin);
//  int pos1 = timeRemainMin;
  int newPos1 = encoder1.getPosition();
//  int pos2 = timeRemainMin;
  int newPos2 = encoder1.getPosition();
  int exitflag = 0;
  int selected;
  while ( 0 == exitflag )
  {
    newPos1 = encoder1.getPosition();
    newPos2 = encoder2.getPosition();
    Serial.print("            ");
    Serial.print(newPos1);
    Serial.print("            ");
    Serial.println(newPos2);
    if (pos1 != newPos1) {
      Serial.print("pos1=");
      Serial.print(newPos1);
      Serial.println();
      pos1 = newPos1;
      timeRemain.text=String(newPos1);
      timeLabels[0].text=String(newPos1);
      selectLabelText(timeRemain);
    }
    if ( 1 == encoder1Pushed ){
      encoder1Pushed = 0;   
      exitflag=1;
    }
    delay(100);
  }
  Serial.print("exit! timeremain=");
  Serial.println(timeRemain.text);
}
