//blink_up_down
const int green_1 = 2, green_2 = 3, red_1 = 4, red_2 = 5, yellow_1 = 6, yellow_2 = 7, blue_1 = 8, blue_2 = 9;

struct LedControl {
  const uint8_t pin;
  uint8_t val;
  bool blink;
  unsigned long prev;
  unsigned long interval;
} Leds[8] {
  {.pin=green_1,  .val=LOW, .blink=false, .prev=0, .interval=0},
  {.pin=green_2,  .val=LOW, .blink=false, .prev=0, .interval=0},
  {.pin=red_1,    .val=LOW, .blink=false, .prev=0, .interval=0},
  {.pin=red_2,    .val=LOW, .blink=false, .prev=0, .interval=0},
  {.pin=yellow_1, .val=LOW, .blink=false, .prev=0, .interval=0},
  {.pin=yellow_2, .val=LOW, .blink=false, .prev=0, .interval=0},
  {.pin=blue_1,   .val=LOW, .blink=false, .prev=0, .interval=0},
  {.pin=blue_2,   .val=LOW, .blink=false, .prev=0, .interval=0}
};

unsigned long startAllBlink = 60000;
bool waitAllBlink = true;

void setup() {

  Serial.begin(9600);

  for(int i = 0; i < 8; i++){
    pinMode(Leds[i].pin, OUTPUT);
    digitalWrite(Leds[i].pin, LOW);
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

  if (waitAllBlink && (millis() >= startAllBlink)) {
    waitAllBlink = false;

    LedAllOff();
    StartAllLedBlink(500);
  };

  CheckAllLedBlink();
}

void LedOn(int iled) {
  Leds[iled].val = HIGH;
  Leds[iled].blink = false;

  digitalWrite(Leds[iled].pin, HIGH);
}

void LedOff(int iled) {
  Leds[iled].val = LOW;
  Leds[iled].blink = false;

  digitalWrite(Leds[iled].pin, LOW);
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
  Leds[iled].blink = true;
  Leds[iled].prev = millis();
  Leds[iled].interval = interval;
}

void StartAllLedBlink(long interval) {
  for (int iled=0; iled<8; iled++){
    StartLedBlink(iled, interval);
  }
}

void CheckLedBlink(int iled) {

  if (Leds[iled].blink) {
    unsigned long currentMillis = millis();

    if ((currentMillis - Leds[iled].prev) >= Leds[iled].interval) {
      Leds[iled].val = (Leds[iled].val == LOW) ? HIGH : LOW;
      digitalWrite(Leds[iled].pin, Leds[iled].val);
      Leds[iled].prev = currentMillis; 
    }
  }
}

void CheckAllLedBlink() {
  for (int iled=0; iled<8; iled++) {
    CheckLedBlink(iled);
  }
}