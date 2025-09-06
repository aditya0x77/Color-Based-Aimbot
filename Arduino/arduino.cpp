#include <Mouse.h>

void setup() {
  Serial.begin(9600);  
  Mouse.begin();      
}

void loop() {
  if (Serial.available() >= 3) {
    char buffer[3];
    Serial.readBytes(buffer, 3);

    int xMove = (int8_t)buffer[0];  
    int yMove = (int8_t)buffer[1];
    int flag  = buffer[2];

    if (flag == 0) {
     
      Mouse.move(xMove, yMove, 0);
    } 
    else if (flag == 1) {
     
      Mouse.press(MOUSE_LEFT);
      delay(10);
      Mouse.release(MOUSE_LEFT);
    }
  }
}
