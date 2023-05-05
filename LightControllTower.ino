const int green_1 = 2, green_2 = 3, red_1 = 4, red_2 = 5, yellow_1 = 6, yellow_2 = 7, blue_1 = 8, blue_2 = 9;
const int allPins[] = {green_1, green_2, red_1, red_2, yellow_1, yellow_2, blue_1, blue_2};

void setup() {

  Serial.begin(9600);

  for(int i = 0; i < 8; i++){
    pinMode(allPins[i], OUTPUT);
    digitalWrite(allPins[i], LOW);
  }
}


void blink_up_down() {
  static int i = 0;

  if (i <= 7) {
    LedOn(i);
    delay(500);
    LedOff(i);

    i += 1;
  }
  else if(i <= 13) {
    int j = 6 - (i-8);

    LedOn(j);
    delay(500);
    LedOff(j);

    i += 1;
  }
  else {
    i = 0;
  }
 
}

void tempo_blinker() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   

    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    digitalWrite(ledPin, ledState);
  }
}

void loop() {
  tempo_blinker();
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

