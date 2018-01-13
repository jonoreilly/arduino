
int led = 4;
int button = 5; 
bool sendinfo[] = {HIGH, LOW, HIGH};
const int datasize = 3;

class protocol 
{
  public:
    int din, dout, cin, cout;
    
  void set (int datain, int dataout, int clockin, int clockout)
  {
    din = datain;
    dout = dataout;
    cin = clockin;
    cout = clockout;
    start();
  }
  
  void start () 
  {
    pinMode(din, INPUT);
    pinMode(dout, OUTPUT);
    digitalWrite(dout, LOW);
    pinMode(cin, INPUT);
    pinMode(cout, OUTPUT);
    digitalWrite(cout, LOW);
  }

  bool tell (bool data[])
  {
    digitalWrite(dout, LOW);
    digitalWrite(cout, LOW);
    if ((digitalRead(din) == HIGH) || (digitalRead(dout) == HIGH)) {return LOW;}
    digitalWrite(dout, HIGH);
    while (digitalRead(cin) != HIGH){}
    digitalWrite(dout, LOW);
    while (digitalRead(cin) != LOW){}
    delay(10);
    for (int i = 0; i < datasize; i++)
    {
      digitalWrite(dout, data[i]);
      delay(10);
      digitalWrite(cout, HIGH);
      delay(20);
      digitalWrite(cout, LOW);
      digitalWrite(dout, LOW);
      delay(10);
    }
    while (digitalRead(cin) != HIGH) {}
    return digitalRead(din); 
  }

  bool * recieve ()
  {
    static bool recieved[datasize];
    digitalWrite(cout, HIGH);
    while (digitalRead(din) != LOW) {}
    digitalWrite(cout, LOW);
    for (int i = 0; i < datasize; i++)
    {
      while (digitalRead(cin) != HIGH) {}
      recieved[i] = digitalRead(cin);
      while (digitalRead(cin) != LOW) {}
    }
    digitalWrite(dout, HIGH);
    digitalWrite(cout, HIGH);
    delay(20);
    digitalWrite(dout, LOW);
    digitalWrite(cout, LOW);
    return recieved;
  }
};





protocol joncom;
void setup() {
  // put your setup code here, to run once:
   pinMode(led, OUTPUT);
   pinMode(button, INPUT_PULLUP);
   joncom.set(0, 1, 2, 3); //din, dout, cin, cout
}

void loop() {
  // put your main code here, to run repeatedly:
  while ((digitalRead(button) == HIGH) && (digitalRead(joncom.din) == LOW)) {}
  if (digitalRead(joncom.din) == HIGH)
  {
      bool * pointer;
      pointer = joncom.recieve();
      digitalWrite (led, HIGH);
      for (int i = 0; i < 3; i++)
      {
        bool data = *(pointer+i);
        if (sendinfo[i] != data){digitalWrite(led, LOW);}  
      }
  }
  else
  {
    bool checker = LOW;
    if (digitalRead(button) == LOW)
    {
      while (checker == LOW)
      {
        checker = joncom.tell(sendinfo);
        delay(100);  
      }
      digitalWrite(led, LOW);
    }  
  }
}
