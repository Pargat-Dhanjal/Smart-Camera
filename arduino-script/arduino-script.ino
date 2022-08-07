#include<Servo.h>

Servo x, y;
int width = 640, height = 480;  // resolution of camera
int xpos = 90, ypos = 90;  // initial positions of Servos

void setup() {
  
  Serial.begin(9600);
  x.attach(9);
  y.attach(10);
  x.write(xpos);
  y.write(ypos);
}

const int angle = 1;   // degree of change

void loop() {
  if (Serial.available() > 0)
  {
    int x_mid, y_mid;
    if (Serial.read() == 'X')
    {
      x_mid = Serial.parseInt();  // read center x
      if (Serial.read() == 'Y')
        y_mid = Serial.parseInt(); // read center y
    }
    else if(Serial.read() == 'Z'){
      x.write(90);
      y.write(90);
      }

// Bring servo to the center tiny square

    if (x_mid > width / 2 + 40)
      xpos += angle;
    if (x_mid < width / 2 - 40)
      xpos -= angle;
    if (y_mid < height / 2 + 40)
      ypos -= angle;
    if (y_mid > height / 2 - 40)
      ypos += angle;

// if outside its range

    if (ypos >= 180)
      ypos = 180;
    else if (ypos <= 0)
      ypos = 0;

    x.write(xpos);
    y.write(ypos);

 
  }
}
