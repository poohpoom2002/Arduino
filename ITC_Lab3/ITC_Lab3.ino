int switch1 = 10;
int switch2 = 11;
int num = 1;
int check = 2;
int pressed;
int randomNo;
int n[13][8] =  {{ 1, 0, 0, 1, 1, 1, 1, 1 }, // 1
  { 0, 0, 1, 0, 0, 1, 0, 1 }, // 2
  { 0, 0, 0, 0, 1, 1, 0, 1 }, // 3
  { 1, 0, 0, 1, 1, 0, 0, 1 }, // 4
  { 0, 1, 0, 0, 1, 0, 0, 1 }, // 5
  { 0, 1, 0, 0, 0, 0, 0, 1 }, // 6
  { 0, 0, 0, 1, 1, 1, 1, 1 }, // 7
  { 0, 0, 0, 0, 0, 0, 0, 1 }, // 8
  { 0, 0, 0, 0, 1, 0, 0, 1 }, // 9
  { 1, 1, 1, 0, 0, 0, 1, 1 }, // L
  { 0, 0, 0, 0, 0, 0, 1, 1 }, // 0
  { 0, 1, 0, 0, 0, 0, 1, 1 }
};   // G
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  randomNo = random(1, 10);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(switch1) == HIGH) {           //When left switch got pressed.
    pressed = 0;
    check = 2;
    num++;
    if (num == 10) {
      num = 1;
    }
    delay(150);
  }
  while (digitalRead(switch2) == HIGH) {           //When right switch got pressed.
    pressed = 1;
    delay(100);
    if (num == randomNo) {                           //When your guess is correct.
      check = 0;
      randomNo = random(1, 10);
    }
    else if (num < randomNo) {                     //When your guess is less than correct answer.
      check = -1;
    }
    else if (num > randomNo) {                     //When your guess is greater than correct answer.
      check = 1;
    }
    delay(150);
  }
  for (int i = 1; i <= 9; i++) {                   //Display number.
    if (num == i && pressed != 1) {
      for (int j = 0; j <= 7; j++) {
        digitalWrite(j + 2, n[i - 1][j]);
      }
    }
  }
  for (int i = -1; i <= 1; i++) {                  //Display your guess result.
    if (check == i) {
      for (int j = 0; j <= 7; j++) {
        digitalWrite(j + 2, n[i + 10][j]);
      }
    }
  }
}
