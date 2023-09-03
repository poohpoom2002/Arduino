#include<EEPROM.h>
#include<TimerOne.h>

struct Time{
  int hour;
  int minute;
  int second;
};
Time time;
int eeAddress = 0;
void setup() {
  // put your setup code here, to run once:
  time.hour = 0;
  time.minute = 0;
  time.second = 0;
  EEPROM.put(eeAddress, time);
}

void loop() {
  // put your main code here, to run repeatedly:
}
