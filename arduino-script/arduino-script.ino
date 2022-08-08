#include <Servo.h>

Servo x, y;
int width = 640, height = 480; // Camera resoulution
int xPos = 90, yPos = 90;      // initial positions of Servos

void setup()
{
  Serial.begin(9600);
  x.attach(9);
  y.attach(10);
  x.write(xPos);
  y.write(yPos);
}

const int angle = 1; // Change in degree

void loop()
{
  if (Serial.available() > 0)
  {
    int x_mid, y_mid;
    if (Serial.read() == 'X')
    {
      x_mid = Serial.parseInt(); // Get x coordinate from arduino
      if (Serial.read() == 'Y')
        y_mid = Serial.parseInt(); // Get y coordinate from arduino
    }

    // Bring servo to the center tiny square

    if (x_mid > width / 2 + 35)
      xPos += angle;
    if (x_mid < width / 2 - 35)
      xPos -= angle;
    if (y_mid < height / 2 + 35)
      yPos -= angle;
    if (y_mid > height / 2 - 35)
      yPos += angle;

    // if outside y servo is out of its range

    if (yPos >= 180)
      yPos = 180;
    else if (yPos <= 0)
      yPos = 0;

    // Wrting the calculated values

    x.write(xPos);
    y.write(yPos);
  }
}
