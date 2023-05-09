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

char cmdBuf[64];
int cmdBufCount = 0;

void setup() {

  Serial.begin(9600);

  for(int i = 0; i < 8; i++){
    pinMode(Leds[i].pin, OUTPUT);
    digitalWrite(Leds[i].pin, LOW);
  }
}

void loop() {

  if (Serial.available() > 0) {
    int byte = Serial.read();
    if (byte == '\n') {
      ProcessCommand();
      cmdBufCount = 0;
    }
    else if(cmdBufCount < (sizeof(cmdBuf) - 1))  {
      cmdBuf[cmdBufCount++] = byte;
      cmdBuf[cmdBufCount] = '\0';
    }
  }

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

void ProcessCommand() {
  Serial.print("cmdBuf=");
  Serial.println(cmdBuf);

  char * cmdStr = strtok (cmdBuf," ");
  char * arg1Str = strtok (NULL, " ");
  char * arg2Str = strtok (NULL, " ");

  if (cmdStr != NULL){
    Serial.print("cmdStr=");
    Serial.println(cmdStr);
  }

  if (arg1Str != NULL){
    Serial.print("arg1Str=");
    Serial.println(arg1Str);
  }

  if (arg2Str != NULL){
    Serial.print("arg2Str=");
    Serial.println(arg2Str);
  }
//--------------------------------------------------------------------------------------------------------------
  if (0 == strcmp("On", cmdStr))
  {
    if(arg1Str != NULL){
      if(0 == strcmp("all", arg1Str)){
        LedAllOn();
      }
      else if (CheckValidNumber(arg1Str) == true){
        LedOn(atoi(arg1Str));
      }
      else{
        Serial.println("Invalid Argument");
      }

    }
    else{
      Serial.println("Must define variables");
    }
  }
//--------------------------------------------------------------------------------------------------------------
  else if (0 == strcmp("Off", cmdStr))
  {
    if(arg1Str != NULL){
      if(0 == strcmp("all", arg1Str)){
        LedAllOff();
      }
      else if (CheckValidNumber(arg1Str)){
        LedOff(atoi(arg1Str));
      }
      else{
        Serial.println("Invalid Argument");
      }

    }
    else{
      Serial.println("Must define variables");
    }
  }
//--------------------------------------------------------------------------------------------------------------
  else if (0 == strcmp("Blink", cmdStr))
  {
    if(arg1Str != NULL){
      if(0 == strcmp("all", arg1Str)){
        if (CheckValidNumber(arg2Str)){
          StartAllLedBlink(atoi(arg2Str));
        }
        else {
          Serial.println("Invalid Argument");
        }
      }
      else if (CheckValidNumber(arg1Str)){
        StartLedBlink(atoi(arg1Str), atoi(arg2Str));
      }
      else{
        Serial.println("Invalid Argument");
      }
    }
    else{
      Serial.println("Must define variables");
    }
  }
  else
  {
    Serial.print("Command not found");
  }
}


bool CheckValidNumber( char *argstr ) {
  bool valid = false;

  for(int i = 0; argstr[i]!=0; i++){
    if( '0' <= argstr[i] && argstr[i] <= '9'){
      valid = true;
    }
    else {
      valid = false;
      break;
    }
  }

  return valid;
}
// output = strcmp(string1, string2);