const int lowFloat = 10;
const int highFloat = 11;
const int manualSwitch = 12;

const int greenLED = 4;
const int redLED = 2;

const int motorEnable = 5;
const int motorIn1 = 7;
const int motorIn2 = 8;

bool pumpRunning = false;
bool faultState = false;

void setup()
{
  pinMode(lowFloat, INPUT);
  pinMode(highFloat, INPUT);
  pinMode(manualSwitch, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(motorEnable, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
}

void loop()
{
  int lowLevel = digitalRead(lowFloat);
  int highLevel = digitalRead(highFloat);
  int manualMode = digitalRead(manualSwitch);

  // Fault Detection
  if(lowLevel == HIGH && highLevel == HIGH)
  {
    faultState = true;
  }
  else
  {
    faultState = false;
  }

  if(faultState)
  {
    analogWrite(motorEnable,0);
    
    digitalWrite(greenLED,!digitalRead(greenLED));
    digitalWrite(redLED,!digitalRead(redLED));
    
    delay(300);
    return;
  }

  // Automatic Mode
  if(manualMode == LOW)
  {
    digitalWrite(greenLED,HIGH);
    
    if(lowLevel == HIGH)
    {
      pumpRunning = true;
    }
    
    if(highLevel == HIGH)
    {
      pumpRunning = false;
    }
  }
  // Manual Override Mode
  else
  {
    digitalWrite(greenLED,LOW);
    
    if(highLevel == HIGH)
    {
      pumpRunning = false;
    }
    else
    {
      pumpRunning = true;
    }
  }

  if(pumpRunning)
  {
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
    analogWrite(motorEnable,220);
    
    digitalWrite(redLED,HIGH);
  }
  else
  {
    analogWrite(motorEnable,0);
    digitalWrite(redLED,LOW);
  }
  delay(50);
}