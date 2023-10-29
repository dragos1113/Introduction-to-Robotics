const int pinLed1 = 13;
const int pinButton1 = 12;
const int pinLed2 = 8;
const int pinButton2 = 7;
const int pinLed3 = 4;
const int pinButton3 = 2;
const int pinLed4 = 11;


byte buttonState1 = HIGH;
byte ledState1 = HIGH;
byte lastButtonState1 = HIGH;
unsigned long lastDebounceTime1 = 0;
unsigned long debounceDelay = 10;

byte buttonState2 = HIGH;
byte ledState2 = LOW;
byte lastButtonState2 = HIGH;
unsigned long lastDebounceTime2 = 0;

byte buttonState3 = HIGH;
byte ledState3 = LOW;
byte lastButtonState3 = HIGH;
unsigned long lastDebounceTime3 = 0;

unsigned long lastLEDChangeTime = 0;
unsigned long ledChangeInterval = 1000;

int target=1;

byte lastLedState1=ledState1;
byte lastLedState2=ledState2;
byte lastLedState3=ledState3;

bool moving = 0;

byte pinBuzzer = 10;
int freqMove = 220;
int freqArrive = 880;
int timeBuzzer = 1000;

unsigned long lastLedFlicker=0;
unsigned long flickerDelay=200;

byte ledState4 = LOW;

void setup() {
  pinMode(pinLed1, OUTPUT);
  pinMode(pinButton1, INPUT_PULLUP);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinButton2, INPUT_PULLUP);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinButton3, INPUT_PULLUP);
  digitalWrite(pinLed1,ledState1);
  digitalWrite(pinLed2,ledState2);
  digitalWrite(pinLed3,ledState3);
  pinMode(pinBuzzer,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  if(currentTime - lastLedFlicker >= flickerDelay)
  {
    ledState4=!ledState4;
    lastLedFlicker = currentTime;
  }
  digitalWrite(pinLed4,ledState4 && moving);
  if (target==1 && ledState1==LOW)
  {
    if(lastLedState2==HIGH)
    {

      ledState2 = LOW;
      digitalWrite(pinLed2, ledState2);
      if(currentTime - lastLEDChangeTime >= ledChangeInterval)
      {
        ledState1 = HIGH;
        digitalWrite(pinLed1, ledState1);
        tone(pinBuzzer,freqArrive,timeBuzzer);
        moving = false;
      
      }
    }
    if(lastLedState3==HIGH)
    {
      ledState3=LOW;
      digitalWrite(pinLed3,ledState3);
      if(currentTime - lastLEDChangeTime >= ledChangeInterval)
      {
        ledState2 = HIGH;
        digitalWrite(pinLed2, ledState2);
        
      }
      if(currentTime - lastLEDChangeTime >= 2 * ledChangeInterval)
      {
        lastLEDChangeTime = currentTime;
        lastLedState1 = ledState1;
        lastLedState2 = ledState2;
        lastLedState3 = ledState3;
      }
    }  
  }  

    if (target==2 && ledState2==LOW)
  {
      ledState1 = LOW;
      digitalWrite(pinLed1, ledState1);
      ledState3 = LOW;
      digitalWrite(pinLed3, ledState3);

      if(currentTime - lastLEDChangeTime >= ledChangeInterval)
      {
        ledState2 = HIGH;
        digitalWrite(pinLed2, ledState2);
        tone(pinBuzzer,freqArrive,timeBuzzer);
        moving = false;
      }
  }   

    if (target==3 && ledState3==LOW)
  {
    if(lastLedState2==HIGH)
    {
      ledState2 = LOW;
      digitalWrite(pinLed2, ledState2);
      if(currentTime - lastLEDChangeTime >= ledChangeInterval)
      {
        ledState3 = HIGH;
        digitalWrite(pinLed3, ledState3);
        tone(pinBuzzer,freqArrive,timeBuzzer);
        moving = false;
      }
    }
    if(lastLedState1==HIGH)
    {
      ledState1=LOW;
      digitalWrite(pinLed1,ledState1);
      if(currentTime - lastLEDChangeTime >= ledChangeInterval)
      {
        ledState2 = HIGH;
        digitalWrite(pinLed2, ledState2);

      }
      if(currentTime - lastLEDChangeTime >= 2 * ledChangeInterval)
      {
        lastLEDChangeTime = currentTime;
        lastLedState1 = ledState1;
        lastLedState2 = ledState2;
        lastLedState3 = ledState3;
      }
    }  
  }  
  if(ledState1 != 0 || ledState2 != 0 || ledState3!=0)
  {
  if (buttonState1 != lastButtonState1) {
    lastDebounceTime1 = currentTime;
  }

  if (currentTime - lastDebounceTime1 > debounceDelay) {
    buttonState1 = digitalRead(pinButton1);
    if (buttonState1 == LOW && buttonState1 != lastButtonState1 && ledState1 == LOW) {
      target = 1;
      tone(pinBuzzer,freqMove);
      moving = true;
      lastLEDChangeTime = currentTime;
      lastLedState1 = ledState1;
      lastLedState2 = ledState2;
      lastLedState3 = ledState3;
    }
  lastButtonState1 = buttonState1;
  }


  if (buttonState2 != lastButtonState2) {
    lastDebounceTime2 = currentTime;
  }

  if (currentTime - lastDebounceTime2 > debounceDelay) {
    buttonState2 = digitalRead(pinButton2);
    if (buttonState2 == LOW && buttonState2 != lastButtonState2 && ledState2 == LOW) {
      target = 2;
      tone(pinBuzzer,freqMove);
      moving = true;
      lastLEDChangeTime = currentTime;
      lastLedState1 = ledState1;
      lastLedState2 = ledState2;
      lastLedState3 = ledState3;
    }
    lastButtonState2 = buttonState2;
  }
  

  if (buttonState3 != lastButtonState3) {
    lastDebounceTime3 = currentTime;
  }
  if (currentTime - lastDebounceTime3 > debounceDelay) {
    buttonState3 = digitalRead(pinButton3);
    if (buttonState3 == LOW && buttonState3 != lastButtonState3 && ledState3 == LOW) {
      target = 3;
      tone(pinBuzzer,freqMove);
      moving = true;
      lastLEDChangeTime = currentTime;
      lastLedState1 = ledState1;
      lastLedState2 = ledState2;
      lastLedState3 = ledState3;
    }
  lastButtonState3 = buttonState3;
  }
 }
}