//blink_up_down
const int green_1 = 2, green_2 = 3, red_1 = 4, red_2 = 5, yellow_1 = 6, yellow_2 = 7, blue_1 = 8, blue_2 = 9;
const int allPins[8] = {green_1, green_2, red_1, red_2, yellow_1, yellow_2, blue_1, blue_2};

//no_delayBlinker
int ledState1 = LOW;
unsigned long previousMillis1 = 0;
long OnTime1 = 250;
long OffTime1 = 750;

int ledState2 = LOW;
unsigned long previousMillis2 = 0;
long OnTime2 = 330;
long OffTime2 = 400;

//StartLedBlink
unsigned long previousMillis = 0;
int ledState = LOW;

//LED ARRAY

// const int ledArr[] = {
//   uint8-t pin[8] = {};
//   uint8-t val[8] = {};
// }

void setup() {

  Serial.begin(9600);

  for(int i = 0; i < 8; i++){
    pinMode(allPins[i], OUTPUT);
    digitalWrite(allPins[i], LOW);
  }

  LedOn( 0 );
  LedOff( 1 );
  StartLedBlink( 2, 500 );
  StartLedBlink( 3, 625 );
  StartLedBlink( 4, 237 );
  LedOff( 5 );
  LedOn( 6 );
  StartLedBlink( 7, 100 );
}

void loop() {
  StartLedBlink( 3, 625 );
  StartLedBlink( 7, 100 );
}

void no_delayBlinker() {
//LED 1
  unsigned long currentMillis = millis();
 
  if((ledState1 == HIGH) && (currentMillis - previousMillis1 >= OnTime1))
  {
    ledState1 = LOW;
    previousMillis1 = currentMillis;
    digitalWrite(yellow_1, ledState1);
  }
  else if ((ledState1 == LOW) && (currentMillis - previousMillis1 >= OffTime1))
  {
    ledState1 = HIGH;
    previousMillis1 = currentMillis;
    digitalWrite(yellow_1, ledState1);
  }
//-----------------------------------------------------------------------------------
//LED 2
  if((ledState2 == HIGH) && (currentMillis - previousMillis2 >= OnTime2))
  {
    ledState2 = LOW;
    previousMillis2 = currentMillis;
    digitalWrite(red_1, ledState2);
  }
  else if ((ledState2 == LOW) && (currentMillis - previousMillis2 >= OffTime2))
  {
    ledState2 = HIGH;
    previousMillis2 = currentMillis;
    digitalWrite(red_1, ledState2);
  }
}

void blink_up_down() {
  static int step = 0; // step index not the led number
  int led; // led to change


  if (step <= 3) {
    led = 2 * step;

    LedOn(led);
    delay(500);
    LedOff(led);

    step += 1;
  }
  else if(step <= 7) {
    led = 7 - 2 * (step-4);

    LedOn(led);
    delay(500);
    LedOff(led);

    step += 1;
  }
  else if (step == 8) {
    LedAllOn();
    delay(500);

    step += 1;
  }
  else if(step == 9) {
    LedAllOff();
    delay(500);

    step += 1;
  }
  else {
    step = 0;
  }
 
}

void blink_to_center() {

}

void LedOn(int iled) {
  digitalWrite(allPins[iled], HIGH);
}

void LedOff(int iled) {
  digitalWrite(allPins[iled], LOW);
}

void LedAllOn() {
  for (int iled=0; iled<8; iled++) {
    digitalWrite(allPins[iled], HIGH);
  }
}

void LedAllOff() {
  for (int iled=0; iled<8; iled++) {
    digitalWrite(allPins[iled], LOW);
  }
}

void StartLedBlink(int iled, long interval) {
 
  unsigned long currentMillis = millis();

  if((ledState == HIGH) && (currentMillis - previousMillis >= interval))
  {
    ledState = LOW;
    previousMillis = currentMillis;
    digitalWrite(allPins[iled], ledState);
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= interval))
  {
    ledState = HIGH;
    previousMillis = currentMillis;
    digitalWrite(allPins[iled], ledState);
  }
}

void CheckLedBlink() {

}

