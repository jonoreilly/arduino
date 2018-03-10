const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;

bool stepperDirection = true; // true = right
long stepperSpeed = 50;
bool stepperStopped = false;

int stepperPosition = 0;
int stepperPins [4] = {2,3,4,5};


bool stepperPositions [8][4] = {{1,0,0,0},{1,1,0,0},
                               {0,1,0,0},{0,1,1,0},
                               {0,0,1,0},{0,0,1,1},
                               {0,0,0,1},{1,0,0,1}};

bool stepperPositionsBasic [4][4] = {{1,0,0,0},
                               {0,1,0,0},
                               {0,0,1,0},
                               {0,0,0,1}};

long lastMili = 0;

void setup() {
  for (int i = 0; i < 4; i ++)
  {
    pinMode(stepperPins[i], OUTPUT);
  }

  Serial.begin(9600);
  Serial.println("stop, right or left");
}


void loop() {
  recieve();
  printstepper();
  movestepper();
}



void recieve() 
{
  if (!newData)
  {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    while (Serial.available() > 0 && newData == false) 
    {
      rc = Serial.read();
      if (rc != endMarker) 
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) 
        {
          ndx = numChars - 1;
        }
      }
      else 
      {
        receivedChars[ndx] = '\0'; // terminate the string
        ndx = 0;
        newData = true;
      }
    }
  }
}


void printstepper() 
{
  if (newData == true) 
  {
    String recievedString = String(receivedChars);
    newData = false;
    
    if (recievedString == "stop")
    {
      stepperStopped = true;
      Serial.println("stepper stopped");
    }

    if (recievedString == "left")
    {
      stepperStopped = false;
      stepperDirection = true;
      Serial.println("going left");
    }

    if (recievedString == "right")
    {
      stepperStopped = false;
      stepperDirection = false;
      Serial.println("going right");
    }
  }
}


void movestepper()
{
  if (!stepperStopped)
  {
    if (millis() > lastMili + stepperSpeed || millis() < lastMili)
    {
      lastMili = millis();
      if (stepperDirection)
      {
        stepperPosition += 1;
        //if (stepperPosition == 8)
        if (stepperPosition == 4)
        {
          stepperPosition = 0;
        }
      }
      else
      {
        stepperPosition -= 1;
        if (stepperPosition == -1)
        {
          //stepperPosition = 7;
          stepperPosition = 3;
        }
      }
      
  
      for (int i = 0; i < 4; i++)
      {
        //digitalWrite(stepperPins[i], stepperPositions[stepperPosition][i]);
        digitalWrite(stepperPins[i], stepperPositionsBasic[stepperPosition][i]);
      }
    }
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(stepperPins[i], LOW);
    }
    delay(500);
  }
}



