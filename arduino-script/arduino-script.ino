#include<Servo.h>

Servo x, y;
int width = 640, height = 480;  // resolution of feed
int xpos = 90, ypos = 90;  // initial positions of Servos

void setup() {
  
  Serial.begin(9600);
  x.attach(9);
  y.attach(10);
  x.write(xpos);
  y.write(ypos);
}

const int angle = 2;   // degree of change in angle

void loop() {
  if (Serial.available() > 0)
  {
    int x_mid, y_mid;
    if (Serial.read() == 'X')
    {
      x_mid = Serial.parseInt();  // read center x-coordinate
      if (Serial.read() == 'Y')
        y_mid = Serial.parseInt(); // read center y-coordinate
    }

// Bring servo to the center of tiny square

    if (x_mid > width / 2 + 30)
      xpos += angle;
    if (x_mid < width / 2 - 30)
      xpos -= angle;
    if (y_mid < height / 2 + 30)
      ypos -= angle;
    if (y_mid > height / 2 - 30)
      ypos += angle;

// if the servo degree is outside its range

    if (xpos >= 180)
      xpos = 180;
    else if (xpos <= 0)
      xpos = 0;
    if (ypos >= 180)
      ypos = 180;
    else if (ypos <= 0)
      ypos = 0;

    x.write(xpos);
    y.write(ypos);

 
  }
}
