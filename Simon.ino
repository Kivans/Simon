const int BUTTON_1 = 12;
const int LED_1 = 13;

const int BUTTON_2 = 8;
const int LED_2 = 9;

const int BUTTON_3 = 4;
const int LED_3 = 5;

bool scanning;

int clickedButton;

int LEDpins[] = {LED_1, LED_2, LED_3 };
const int numOfLEDs = 3;

int buttonPins[] = {BUTTON_1, BUTTON_2, BUTTON_3};
const int numOfButtons = 3;

int sequenceArray[42];
int level;
int score;
int currentLED;

void setup() 
{
  randomSeed(analogRead(0));
  
  //Initialize pins:
  //LEDs
  for (int i = 0; i < numOfLEDs; i++)
    pinMode(LEDpins[i], OUTPUT);  

  //Buttons
  for (int i = 0; i < numOfButtons; i++)
    pinMode(buttonPins[i], OUTPUT);  

  score = 0;
  level = 1;
  currentLED = 0;
  
  initiateArray();
  playSequence();
}

void loop() 
{
  if (scanning)
  scan();
}

void LEDpower(int LED, bool value)
{
  if (value)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);
}

void playSequence()
{
  for (int i = 0; i < level; i++)
  {
    LEDpower(sequenceArray[i], true); //Turn LED on
    delay(750); //Wait
    LEDpower(sequenceArray[i], false); //Turn LED off
    if (i != level - 1)
    delay(350); //Wait
  }
  scanning = true;
}

void initiateArray()
{
  bool temp;
  for (int i = 0; i < 42; i++)
  {
    sequenceArray[i] = LEDpins[random(3)];
  }
}

void scan() //Stay in while loop until the user has pressed one of the three buttons
{  
  scanning = false;
  while (true)
  {
    if (digitalRead(BUTTON_1) || digitalRead(BUTTON_2) || digitalRead(BUTTON_3))
    break;
  }
    if (digitalRead(BUTTON_1))           
          clickedButton = BUTTON_1;        
              
      else if (digitalRead(BUTTON_2))        
          clickedButton = BUTTON_2;              
        
      else      
        clickedButton = BUTTON_3;

        verify();
}

void verify()
{
  int led = clickedButton + 1;
  
  currentLED = sequenceArray[score];
  
  if (led == currentLED) //User is correct, keep going
  {
    score++;
    
    LEDpower(led, true); //Turn on the clicked LED for half a second, and then turn it off
    delay(400);
    LEDpower(led, false);

    
    if (score == level) //Last LED, play another sequence, this time more LED to remember
    {
      delay(250);
      score = 0;
      level++;
      playSequence();
    }

    else //Not the last LED, keep going
    {
      scanning = true;
    }
  }
  else //Incorrect, start all over
  {
    gameOver();
  }
}

void gameOver()
{
  delay(250);
  for (int j = 0; j < 5; j++)
  {
    for (int i = 0; i < numOfLEDs; i++)
    {
      LEDpower(LEDpins[i], true);  
    }
    delay(250);
    for (int i = 0; i < numOfLEDs; i++)
    {
      LEDpower(LEDpins[i], false);  
    }
    delay(250);
  }
  delay(650);
  
  setup();
}



