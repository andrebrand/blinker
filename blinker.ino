// Komfortblinker für Dacia Sandero Stepway
// mit Arduino Nano

int outputLeft = 3, outputRight = 2;
int inputLeft = 4, inputRight = 5;
bool isLeftActive = false;
bool isRightActive = false;
static unsigned long int waitSince = millis(); // millisec timestamp at wich the signal was activated
static unsigned long int waitSpan = 3300; // time turn signal will be active (in ms)


static unsigned long int pressedSince = 0; // millisec timestamp at wich a new input was given
static unsigned long int minPressedMillis = 100; // time input singal was consistent (in ms)


bool prevSignalLeft; // previous signal left
bool prevSignalRight; // previous singal right

void setup()
{
  pinMode(outputLeft, OUTPUT);
  pinMode(outputRight, OUTPUT);
  prevSignalLeft = digitalRead(inputLeft);
  prevSignalRight = digitalRead(inputRight);
  Serial.begin(9600);
}



void loop()
{
  bool signalLeft = digitalRead(inputLeft);
  bool signalRight = digitalRead(inputRight);

  handleTurnSignal(&signalLeft, &prevSignalLeft, &isLeftActive, &isRightActive); // all params are passed by reference

  handleTurnSignal(&signalRight, &prevSignalRight, &isRightActive, &isLeftActive); // all params are passed by reference
 
  handleDigitalWrite();

  prevSignalLeft = signalLeft;
  prevSignalRight = signalRight;
}


void handleTurnSignal(bool *signal, bool *prevSignal, bool *isSideActive, bool *isOppSideActive){
  if(!*signal && *signal != *prevSignal){ 
    // when button is pressed for the "first" time
    pressedSince = millis();
  }else if( !*signal && *signal == *prevSignal && getIsPressedLongEnough()){
    // when input is active and was active for long enough
    waitSince = millis();
    waitSince = waitSince;
    *isSideActive = true;
    *isOppSideActive = false;
    pressedSince = 0;
  }else if( *isSideActive && getIsTimeUp() ){
    // when output is active but time is up -> set output inaktive
    *isSideActive = false;
  }else if (*signal && *signal != *prevSignal){
    // when input was active before and is inaktive now
    pressedSince = 0;
  }
}

void handleDigitalWrite(){
  if(isLeftActive){
    digitalWrite(outputLeft,HIGH);
  }else{
    digitalWrite(outputLeft,LOW);  
  }

  if(isRightActive){
    digitalWrite(outputRight,HIGH);
  }else{
    digitalWrite(outputRight,LOW);  
  }
}

bool getIsTimeUp(){
  return (millis() - waitSince >= waitSpan);
}

bool getIsPressedLongEnough(){
  return ((pressedSince > 0) && (millis() - pressedSince >= minPressedMillis));
}
