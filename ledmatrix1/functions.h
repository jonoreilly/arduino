#pragma once

class dsplay{
public:
  int img[8][4], tall = 4, wide = 8, piny [4] = {10, 11, 12, 13}, pinx [8] = {9, 8, 7, 6, 5, 4, 3, 2};

  void setup(){
    for (int i = 0; i < tall; i++){
      pinMode(piny[i], OUTPUT);
      digitalWrite(piny[i], LOW);
    }
    for (int i = 0; i < wide; i++){
      pinMode(pinx[i], OUTPUT);
      digitalWrite(pinx[i], LOW);
  }
    Serial.print("setup display\n");
  }
  void clear(){
    for(int x = 0; x < wide; x++){
      for(int y = 0; y < tall; y++){
        img[x][y] = 0;
  }}}
  void drawbit(int x, int y){
    img [x][y] = 1;
  }
  void line(int line){
    for (int i = 0; i < tall; i++){
      digitalWrite(piny[i], HIGH);
    }
    for (int i = 0; i < wide; i++){
      if (img[i][line] == 1){
      digitalWrite (pinx[i], HIGH);
    }
      else{
      digitalWrite (pinx[i], LOW);
    }
    }
    digitalWrite(piny[line], LOW);
}};


class car{
public:
  int carpy = 1, Rbutton = 1, Lbutton = 0;

  void setup(){
    pinMode(Rbutton, INPUT_PULLUP);
    pinMode(Lbutton, INPUT_PULLUP);
      Serial.print("setup car\n");
  }
  void draw(dsplay& matrix){
    matrix.drawbit(6, carpy);
    matrix.drawbit(7, carpy);
  }
  void move(){
    if (digitalRead(Rbutton)==LOW){carpy++; if(carpy > 3){carpy = 3;}}
    if (digitalRead(Lbutton)==LOW){carpy--; if(carpy < 0){carpy = 0;}}
  }};


class rock{
public:
  int posy = random(4), posx = 0;

  void clear(){
   posx = 0;
   posy = random (4); 
  }
  void move(){
    posx++;
    if (posx > 7){
//    delete this;
      posx = 0;
      posy = random(4);
  }}
  void draw(dsplay& matrix){
    matrix.drawbit(posx, posy);
  }};
