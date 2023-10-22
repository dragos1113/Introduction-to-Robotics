int redPin = 10;
int greenPin = 9;
int bluePin = 11;
 
int potPin_red = A2;
int potPin_green = A1;
int potPin_blue = A0;
 
int potVal_red;
int potVal_green;
int potVal_blue;
 
int writeVal_red;
int writeVal_green;
int writeVal_blue; 
 
int potMin = 0;
int potMax = 1023;
int outputMin = 0;
int outputMax = 255;

void setup() {
  pinMode(potPin_red, INPUT);
  pinMode(potPin_green, INPUT);
  pinMode(potPin_blue, INPUT);
  
  pinMode(redPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin, OUTPUT);
}
 
void loop() {
  potVal_red = analogRead(potPin_red);
  potVal_green = analogRead(potPin_green);
  potVal_blue = analogRead(potPin_blue);
  
  writeVal_red = map(potVal_red, potMin, potMax, outputMin, outputMax);
  writeVal_green = map(potVal_green, potMin, potMax, outputMin, outputMax);
  writeVal_blue = map(potVal_blue, potMin, potMax, outputMin, outputMax);

  analogWrite(redPin,writeVal_red);
  analogWrite(greenPin,writeVal_green);
  analogWrite(bluePin,writeVal_blue);
}