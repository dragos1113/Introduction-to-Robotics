const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12;
const int buttonPin = 1;
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;
int buttonState = LOW;
int lastButtonState = LOW;
int counting = false;
int lastDebounceTime;
int debounceDelay=1000;
int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4;
const int encodingsNumber = 16;
byte byteEncodings[encodingsNumber] = {
B11111100, // 0
B01100000, // 1
B11011010, // 2
B11110010, // 3
B01100110, // 4
B10110110, // 5
B10111110, // 6
B11100000, // 7
B11111110, // 8
B11110110, // 9
B11101110, // A
B00111110, // b
B10011100, // C
B01111010, // d
B10011110, // E
B10001110 // F
};
unsigned long lastIncrement = 0;
unsigned long delayCount = 50;
unsigned long number = 0;
void setup() {
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
pinMode(buttonPin,INPUT_PULLUP);
for (int i = 0; i < displayCount; i++) {
pinMode(displayDigits[i], OUTPUT);
digitalWrite(displayDigits[i], LOW);
}

Serial.begin(9600);
}
void loop() {
  buttonStart();
  if (counting) {
    if (millis() - lastIncrement > delayCount) {
      number++;
      number %= 10000; 
      lastIncrement = millis();
    }
  }
  writeNumber(number);
}
void writeReg(int digit) {
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, digit);
digitalWrite(latchPin, HIGH);
}
void buttonStart() {
  int buttonReading = digitalRead(buttonPin);

  if (buttonReading != lastButtonState && buttonReading == LOW) {
    counting = !counting;
  }

  lastButtonState = buttonReading;
}
void activateDisplay(int displayNumber) {
for (int i = 0; i < displayCount; i++) {
digitalWrite(displayDigits[i], HIGH);
}
digitalWrite(displayDigits[displayNumber], LOW);
}
void writeNumber(int number) {
int currentNumber = number;
int displayDigit = 3;
int lastDigit = 0;
while (currentNumber != 0) {
activateDisplay(displayDigit);
lastDigit = currentNumber % 10;
  if(displayDigit == 2)
  writeReg(byteEncodings[lastDigit] + 1);
  else
  writeReg(byteEncodings[lastDigit]);
currentNumber /= 10;
displayDigit--;
writeReg(B00000000);
}
}
