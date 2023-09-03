#define LED_WEST_RED 12
#define LED_WEST_YELLOW 11
#define LED_WEST_GREEN 10
#define LED_SOUTH_RED 9
#define LED_SOUTH_YELLOW 8
#define LED_SOUTH_GREEN 7
#define LED_CROSSING_RED 6
#define LED_CROSSING_GREEN 5
#define EAST_CAR 4
#define NORTH_CAR 3
#define PEOPLE_CROSSING 2
#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
#define goC 4
#define offC1 5
#define onC 6
#define offC2 7

struct State {                                                                 //Define policy
  unsigned long ST_Out;
  unsigned long Time;
  unsigned long Next[8];
};

typedef const struct State SType;

SType FSM[8] = {                                                              //All states
  {B10000110, 2000, {goN, waitN, goN, waitN, waitN, waitN, waitN, waitN}},
  {B10001010, 500, {goE, goC, goE, goC, goE, goC, goE, goC}},
  {B00110010, 2000, {goE, waitE, waitE, waitE, goE, waitE, waitE, waitE}},
  {B01010010, 500, {goN, goC, goN, goC, goN, goC, goN, goN}},
  {B10010001, 2000, {goC, goC, offC1, offC1, offC1, offC1, offC1, offC1}},
  {B10010000, 350, {onC, onC, onC, onC, onC, onC, onC, onC}},
  {B10010001, 350, {offC2, offC2, offC2, offC2, offC2, offC2, offC2, offC2}},
  {B10010000, 350, {goC, goC, goN, goN, goE, goE, goE, goE}}
};
unsigned long s = 0;
void setup() {                                                                //Setup inputs and outputs
  // put your setup code here, to run once:
  pinMode(LED_WEST_RED, OUTPUT);
  pinMode(LED_WEST_YELLOW, OUTPUT);
  pinMode(LED_WEST_GREEN, OUTPUT);
  pinMode(LED_SOUTH_RED, OUTPUT);
  pinMode(LED_SOUTH_YELLOW, OUTPUT);
  pinMode(LED_SOUTH_GREEN, OUTPUT);
  pinMode(LED_CROSSING_RED, OUTPUT);
  pinMode(LED_CROSSING_GREEN, OUTPUT);
  pinMode(EAST_CAR, INPUT);
  pinMode(NORTH_CAR, INPUT);
  pinMode(PEOPLE_CROSSING, INPUT);

}
int input, input1 = 0, input2 = 0, input3 = 0;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_WEST_RED, FSM[s].ST_Out & B10000000);                    //Turn the light on if that bit = 1
  digitalWrite(LED_WEST_YELLOW, FSM[s].ST_Out & B01000000);
  digitalWrite(LED_WEST_GREEN, FSM[s].ST_Out & B00100000);
  digitalWrite(LED_SOUTH_RED, FSM[s].ST_Out & B00010000);
  digitalWrite(LED_SOUTH_YELLOW, FSM[s].ST_Out & B00001000);
  digitalWrite(LED_SOUTH_GREEN, FSM[s].ST_Out & B00000100);
  digitalWrite(LED_CROSSING_RED, FSM[s].ST_Out & B00000010);
  digitalWrite(LED_CROSSING_GREEN, FSM[s].ST_Out & B00000001);
  delay(FSM[s].Time);                                                      //Delay with the time state in policy
  if (digitalRead(EAST_CAR) == LOW) {                                      //If there is car on east side
    input1 = 1;
  }
  else {
    input1 = 0;
  }
  if (digitalRead(NORTH_CAR) == LOW) {                                     //If there is car on north side
    input2 = 1;
  }
  else {
    input2 = 0;
  }
  if (digitalRead(PEOPLE_CROSSING) == LOW) {                              //If there is people crossing
    input3 = 1;
  }
  else {
    input3 = 0;
  }
  input = input1 * 4 + input2 * 2 + input3;                               //Calculate three inputs to one input
  s = FSM[s].Next[input];                                                 //Work the next state

}
