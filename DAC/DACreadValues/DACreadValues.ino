
int value = 0;
byte pins[] = {6, 5, 4, 3, 2};
byte const pinQuantity = 5;
byte count = 0;
bool bus[] =  {0, 0, 0, 0, 0};
String inputString = "";

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < pinQuantity; i++)
  {
    pinMode(pins[i], OUTPUT);
  }

  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:

}


void serialEvent()
{
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') 
    {
      Serial.print("\n\nInput from 0 to 31:\n>");
      value = inputString.toInt();
      Serial.print(value);
      inputString = "";
        
      count = 0;
      
      while (value > 0)
      {
        bus[count] = value % 2;
        value = value / 2;
        count++;  
      }
    
      for (int i = 0; i < count; i++)
      {
          digitalWrite(pins[i], bus[i]);
      }

      for (int i = count; i < pinQuantity; i++)
      {
        digitalWrite(pins[i], LOW); 
      }
    }
  } 
}
