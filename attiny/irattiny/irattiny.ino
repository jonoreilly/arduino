int ir = 1, spd = 14;

void iron ( float milsec ) {
float ciclos = milsec / 0.02631 ; //in mili seconds
for ( int i = 0 ; i < ciclos ; i++ ) {
  //this cilce lasts 0.000 026 31 secs at 38kHz
  digitalWrite(ir, HIGH);
  delayMicroseconds(spd);
  digitalWrite(ir, LOW);
  delayMicroseconds(spd);  
}}


void setup() {
  pinMode (ir, OUTPUT);
}

void loop() {
  iron(2);
}
