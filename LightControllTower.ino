//blink_up_down
const int green_1 = 2, green_2 = 3, red_1 = 4, red_2 = 5, yellow_1 = 6, yellow_2 = 7, blue_1 = 8, blue_2 = 9;
const uint8_t ledPins[8] = {green_1, green_2, red_1, red_2, yellow_1, yellow_2, blue_1, blue_2};
uint8_t ledVal[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
bool ledBlink[8] = {false, false, false, false, false, false, false, false};
unsigned long ledPrev[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long ledInterval[8] = {0, 0, 0, 0, 0, 0, 0, 0};



void setup() {

  Serial.begin(9600);

  for(int i = 0; i < 8; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
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
  CheckAllLedBlink();
}


void LedOn(int iled) {
  ledVal[iled] = HIGH;
  ledBlink[iled] = false;

  digitalWrite(ledPins[iled], HIGH);
}

void LedOff(int iled) {
  ledVal[iled] = LOW;
  ledBlink[iled] = false;

  digitalWrite(ledPins[iled], LOW);
}

void LedAllOn() {
  for (int iled=0; iled<8; iled++) {
    LedOn(iled);
  }
}

void LedAllOff() {
  for (int iled=0; iled<8; iled++) {
    LedOff(iled);
  }
}

void StartLedBlink(int iled, long interval) {
  ledBlink[iled] = true;
  ledPrev[iled] = millis();
  ledInterval[iled] = interval;
}

void CheckLedBlink(int iled) {

  if (ledBlink[iled]) {
    unsigned long currentMillis = millis();

    if ((currentMillis - ledPrev[iled]) >= ledInterval[iled]) {
      ledVal[iled] = (ledVal[iled] == LOW) ? HIGH : LOW;
      digitalWrite(ledPins[iled], ledVal[iled]);
      ledPrev[iled] = currentMillis; 
    }
  }
}

void CheckAllLedBlink() {
  for (int iled=0; iled<8; iled++) {
    CheckLedBlink(iled);
  }
}