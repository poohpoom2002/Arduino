#define red 4
#define yellow 3
#define green 2
int leftState;
int middleState;
int rightState;
int lastLeftState = LOW;
int lastMiddleState = LOW;
int lastRightState = HIGH;
int lastDebounceTime = 0;
int debounceDelay = 50;
int t = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(12,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int leftButtonRead = digitalRead(12);
  int middleButtonRead = digitalRead(11);
  int rightButtonRead = digitalRead(10);
  int i;
  // Debounce for left button
  if(leftButtonRead != lastLeftState){
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime) > debounceDelay){
    if(leftButtonRead == HIGH){
      digitalWrite(red, HIGH);
      for(i = 0; i<= 3000; i++){
       delay(1);
        if(leftButtonRead == CHANGE && digitalRead(red) == HIGH){
          digitalWrite(red, LOW);
          break;
        }
      }
    }
  }
    if(leftButtonRead != leftState){
      leftState = leftButtonRead;
    }
  lastLeftState = leftButtonRead;
  // Debounce for right button
  if(rightButtonRead != lastRightState){
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime) > debounceDelay){
    if(rightButtonRead == LOW && digitalRead(red) != HIGH){
      digitalWrite(green, HIGH);
      t = millis();
      if(millis()-t >= 3000){
        digitalWrite(green, LOW);
      }
    }
    if(rightButtonRead != rightState){
      rightState = rightButtonRead;
    }
  }
  lastRightState = rightButtonRead;
  // Debounce for middle button
  if(middleButtonRead != lastMiddleState){
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime) > debounceDelay){
    if(middleButtonRead == LOW && digitalRead(red) != HIGH && digitalRead(green) != HIGH){
      for(i = 0; i<2; i++){
        digitalWrite(yellow, HIGH);
        delay(500);
        digitalWrite(yellow, LOW);
        delay(500);
      }
    }
    if(middleButtonRead != middleState){
      middleState = middleButtonRead;
    }
  }
  lastMiddleState = middleButtonRead;
}
