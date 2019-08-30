
int triggerh = 800;
int triggerl = 500;

long warmup = 100;

long timeout = 1000;

volatile long start, mid, last;

int outPin = 4;
int ledPin = 7;

bool value = false;


void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(outPin, OUTPUT);

  

  cli(); // clear interrupts

  // set timer 1 to 1 Hz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15644;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 pres            caler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();// allow interrupts

  Serial.begin(115200);
}

void loop() 
{
  //Serial.println(analogRead(3));
}


ISR(TIMER1_COMPA_vect)
{
  digitalWrite(outPin, HIGH);
  start = micros();
  while ((micros()-start) < 4*warmup){}
  
  digitalWrite(outPin, LOW);
  start = micros();
  while (micros()-start < warmup+(warmup*2*value)){}
  
  digitalWrite(outPin, HIGH);
  start = micros();
  while (micros()-start < warmup*(3-2*value)){}
  digitalWrite(outPin, LOW);

  digitalWrite(ledPin, value);
  value = !value;  
}




