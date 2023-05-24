// Komfortblinker für Dacia Sandero Stepway
// mit Arduino Nano

int outputLeft = 3, outputRight = 2;
int inputLeft = 4, inputRight = 5;
bool isLeftActive = false;
bool isRightActive = false;
static unsigned long int waitSince = millis();
static unsigned long int waitSpan = 3300;


static unsigned long int pressedSince = 0;

static unsigned long int minPressedMillis = 100;


bool prevSignalLeft;
bool prevSignalRight;

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

  handleTurnSignal(&signalLeft, &prevSignalLeft, &isLeftActive, &isRightActive);

  handleTurnSignal(&signalRight, &prevSignalRight, &isRightActive, &isLeftActive);


/* Old verison
  if(!signalLeft && signalLeft != prevSignalLeft){ //button pressed
    pressedSince = millis();
  }else if( !signalLeft && signalLeft == prevSignalLeft && getIsPressedLongEnough()){
    // when input is active and was active for long enough
    waitSince = millis();
    waitSince = waitSince - minPressedMillis;
    isLeftActive = true;
    isRightActive = false;
    pressedSince = 0;
  }else if( isLeftActive && isTimeUp ){
    // when output is active but time is up -> set output inaktive
    isLeftActive = false;
  }else if (signalLeft && signalLeft != prevSignalLeft){
    // when input was active before and is inaktive now
    pressedSince = 0;
  }*/


  
/*
  if(!signalRight && signalRight != prevSignalRight){ //button pressed
    pressedSince = millis();
  }else if( !signalRight && getIsPressedLongEnough() ){
    waitSince = millis();
    waitSince = waitSince - minPressedMillis;
    isLeftActive = false;
    isRightActive = true;
    pressedSince = 0;
  }else if( isRightActive && isTimeUp ){ //button is not pressed and time is up
    isRightActive = false;
  }else{
    pressedSince = 0;
  }*/
  
 
  handleDigitalWrite();

  prevSignalLeft = signalLeft;
  prevSignalRight = signalRight;
}


void handleTurnSignal(bool *signal, bool *prevSignal, bool *isSideActive, bool *isOppSideActive){
  if(!*signal && *signal != *prevSignal){ //button pressed
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

bool getIsTimeUp(){
  return (millis() - waitSince >= waitSpan);
}

bool getIsPressedLongEnough(){
  return ((pressedSince > 0) && (millis() - pressedSince >= minPressedMillis));
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
