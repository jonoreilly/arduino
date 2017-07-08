#include "functions.h"

//leftbutton in pin 0 and right i 1
int RPF = 5;
int frames = 0;
int score = 0;

dsplay matrix;
car player;
rock enemy;

void refresh(){
  for(int f = 0; f < RPF; f++){
  for(int i = 0; i < 4; i++){
  matrix.line(i);
  delay(2);
}}
frames++;
score++;
}

void draw(){
  player.draw(matrix);
  enemy.draw(matrix);
}

void move(){
  player.move();
  if (frames >= enemy.spd){
  enemy.move();
  frames = 0;
  Serial.print(enemy.spd);
  Serial.print("        ");
  Serial.print(score);
  Serial.print("\n");
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  matrix.setup();
  matrix.clear();
  player.setup();
  
 
  Serial.print("setup done");

  for (int a = 2; a < 10; a++){
   digitalWrite(a, LOW);
  }

    for (int a = 10; a < 14; a++){
    digitalWrite(a, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1){
    draw();
    refresh();
    matrix.clear();
    move();
    if (enemy.posx > 5 && (enemy.posy == player.carpy)){break;}
  }

  Serial.print("Game over\n");
  delay (10000);
  enemy.clear();
/*
  digitalWrite(13, LOW);
  for (int i = 2; i < 10; i++){
    digitalWrite(i, HIGH);
  }
*/
}
