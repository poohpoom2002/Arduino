#include<EEPROM.h>
#include<Wire.h>
#include<SPI.h>
#include<TimerOne.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

int eeAddress = 0;
struct Time{
  int hour;
  int minute;
  int second;
};
Time time;
#define OLED 4
#define Button 12
void count();

void setup() {
  // put your setup code here, to run once:
  Adafruit_SSD1306 display(OLED);
  EEPROM.get(eeAddress, time);
  pinMode(Button, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(time.hour);
  display.println(time.minute);
  Timer1.initialize(60000000);
  Timer1.attachInterrupt(count);
  int eeAdress = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(Button) == HIGH){
    EEPROM.put(eeAddress, time);
}

void count() {
  time.second++;
  if(time.second == 60){
    time.minute++;
    time.second = 0;
  }
  if(time.minute == 60){
    time.hour++;
    time.minute = 0;
  }
  display.setCursor(0,0);
}
