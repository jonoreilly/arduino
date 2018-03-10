int shakerPin = 10;
int readerPin = 2;
float before = 0;
float value = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode (shakerPin, OUTPUT);
  pinMode (readerPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  before = analogRead(readerPin);
  value = before/1000*255;
  analogWrite (shakerPin, value);
  Serial.println(before);
  //Serial.println(value);
}
