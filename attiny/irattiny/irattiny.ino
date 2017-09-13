int iron = 1, spd = 14, iroff = 5;
bool sonypower [12] = {1,0,1,0,1,0,0,1,0,0,0,0} ;
float wait = 0.5, preamble = 2.5, data [2] = {0.75,1.25};

// ______------_--_-_--_-_--_-_-_--_-_-_-_-_________



void ir ( int pin, float milsec ) {
  float ciclos = milsec / 0.02631 ; //in mili seconds
  for ( int i = 0 ; i < ciclos ; i++ ) {
    //this cilce lasts 0.000 026 31 secs at 38kHz
    digitalWrite(pin, HIGH);
    delayMicroseconds(spd);
    digitalWrite(pin, LOW);
    delayMicroseconds(spd);  
}}


void output ( bool transmission [] ) {
  ir (iron, preamble);
  for (int e = 0; e < sizeof sonypower; e++ ) {
    ir (iroff, wait);
    ir (iron, data[transmission[e]]);
    }
}


void setup() {
  pinMode (iron, OUTPUT);
  pinMode (iroff, OUTPUT);
}


void loop() {
  delay(20000);
  output(sonypower);
}
