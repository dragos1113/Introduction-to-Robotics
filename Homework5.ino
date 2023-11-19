const int dim = 20;
char input[dim];
int index = 0;
enum{
  MAIN_MENU,SENSOR_MENU,SAMPLING_RATE,RESET_MENU,STATUS_MENU,LED_MENU
} menu;
int samplingRate = 0;
void setup() {
  // Initialize serial communication at 9600 bps
  Serial.begin(9600);
  printMainMenu();

}
bool readInput()
{
  if(index == dim-1)
  {
    input[index] = 0;
    index = 0;
    return true;
  }

  if(Serial.available() > 0)
  {
    char var = Serial.read();
    input[index] = var;
    index++;
    if(var == '\n')
    {
      input[index] = 0;
      index = 0;
      return true;
    }
  }

  return false;
}
void loop() 
{
  if(readInput())
  {
    int option = atoi(input);
    switch (menu)
    {
      case MAIN_MENU:
        mainMenu(option);
        break;
      case SENSOR_MENU:
        sensorMenu(option);
        break;
      case RESET_MENU:
        resetMenu(option);
        break;
      case STATUS_MENU:
        statusMenu(option);
        break; 
      case LED_MENU:
        LEDMenu(option);
        break;
      case SAMPLING_RATE:
        samplingMenu(option);
        break;
    }
  }
}
void printMainMenu()
{
  Serial.println("Choose an option:");
  Serial.println("1.Sensor Settings ");
  Serial.println("2. Reset Logger Data");
  Serial.println("3. System Status");
  Serial.println("4. RGB LED Control");
}
void mainMenu(int option) {
  switch (option)
  {
    case 1:
      menu = SENSOR_MENU;
      printSensorMenu();
      break;
    case 2:
      menu = RESET_MENU;
      prinResetMenu();
      break; 
    case 3:
      menu = STATUS_MENU;
      printStatusMenu();
      break; 
    case 4:
      menu = LED_MENU;
      printLEDMenu();
      break;  
  }
}
void printSensorMenu()
{
  Serial.println("1. Sensors Sampling Interval.");
  Serial.println("2. Ultrasonic Alert Threshold");
  Serial.println("3. LDR Alert Threshold");
  Serial.println("4. Back");
}
void sensorMenu(int option) {
  switch (option)
  {
    case 1:
      menu = SAMPLING_RATE;
      Serial.println("Choose a sampling rate from 1 to 10");
      break;
    case 4:
      menu = MAIN_MENU;
      printMainMenu();
      break;  
  }
}
void samplingMenu(int option)
{
  
  if(option <=10 && option >=1)
  {
  samplingRate = option;
  Serial.print("The sampling rate is:");
  Serial.println(samplingRate);
  }
  else
  Serial.println("Choose a valid sampling rate");
  menu = SENSOR_MENU;
  printSensorMenu();
}
void prinResetMenu()
{
  Serial.println("Are you sure?");
  Serial.println("1. Yes");
  Serial.println("2. No");
}
void resetMenu(int option)
{
  switch(option)
  {
    case 1:
      Serial.println("Data RESET");
    case 2:
      menu = MAIN_MENU;
      printMainMenu();
      break;
  }
}
void printStatusMenu()
{
  Serial.println("1. Current Sensor Readings");
  Serial.println("2. Current Sensor Settings");
  Serial.println("3. Display Logged Data");
  Serial.println("4. Back");
}
void statusMenu(int option)
{
  switch(option)
  {
    case 4:
      menu = MAIN_MENU;
      printMainMenu();
      break;
  }
}

void printLEDMenu()
{
  Serial.println("1. Manual Color Control");
  Serial.println("2. LED: Toggle Automatic ON/OFF");
  Serial.println("3. Back");
}

void LEDMenu(int option)
{
  switch(option)
  {
    case 3:
      menu = MAIN_MENU;
      printMainMenu();
      break;
  }
}

