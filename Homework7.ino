#include "LedControl.h" 

const int pinSW = 2;
const int pinX = 0;
const int pinY = 1;
const int wallsNumber = 32;              
const int dinPin = 12;                                   
const int clockPin = 11;                                
const int loadPin = 10;                                 
const int matrixSize = 8;   
const int matrixLength = matrixSize * matrixSize;
int playerPosition = 0;
bool isSpawned = 0;
unsigned long playerBlinkTime = 100;
unsigned long lastPlayerBlink = 0;
bool isBlinking = 0;
byte swState = LOW;
const int minTreshold = 400;
const int maxTreshold = 600;
bool joyMoved = false;
bool joyIsNeutral = false;
int debounceDelay = 50;

bool walls[matrixSize*matrixSize];

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); 

void setup()
{
  Serial.begin(9600);

  lc.shutdown(0, false);                 // turn off power saving, enables display
  lc.setIntensity(0, 1);                 // sets brightness (0~15 possible values)
  lc.clearDisplay(0);                    // clear screen
  
  randomSeed(analogRead(0));

  spawnPlayer();
  generateWorld();
}

void spawnPlayer()
{
  playerPosition = random(0, matrixLength);
}

void movePlayer()
{
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);
  if (xValue >= minTreshold && xValue <= maxTreshold && yValue >= minTreshold && yValue <=maxTreshold) 
    joyIsNeutral = true;
 
  if(xValue > maxTreshold && walls[playerPosition + 1] == false && joyIsNeutral)
  {
    
    playerPosition++;
    joyIsNeutral = false;
  }
  if(xValue < minTreshold && walls[playerPosition - 1] == false && joyIsNeutral)
  {
    playerPosition--;
    joyIsNeutral = false;
  }
  if(yValue > maxTreshold && walls[playerPosition + matrixSize] == false && joyIsNeutral)
  {
    playerPosition = playerPosition + matrixSize;
    joyIsNeutral = false;
  }
  if(yValue < minTreshold && walls[playerPosition - matrixSize] == false && joyIsNeutral)
  {
    playerPosition = playerPosition - matrixSize;
    joyIsNeutral = false;  
  }
}

void spawnBomb()
{

}
void generateWorld()
{
  int wallCount = 0;
  int off[5] = {0, 1, -1, matrixSize, -matrixSize};

  while (wallCount < wallsNumber)
  {
    int i = random(0, matrixLength);
    
    bool valid = !walls[i];

    for (int j = 0; j< 5; j++)
    {
      if(playerPosition == i + off[j])
      {
        valid = false;
        break;
      }    
    }

    if (valid)
    {
      walls[i] = true;
      wallCount++;
    } 
  }
}

void draw()
{
  while (millis() - lastPlayerBlink >= playerBlinkTime)
  {
    isBlinking = !isBlinking;
    lastPlayerBlink = millis();
  }

  for(int i = 0; i< matrixLength; i++)
    lc.setLed(0, i%matrixSize,i/matrixSize,(i == playerPosition) ? isBlinking : walls[i]);
}

void loop()
{
  draw();
  movePlayer();
}