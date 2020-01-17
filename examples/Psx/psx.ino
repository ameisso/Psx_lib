#include <Arduino.h>
#include <Psx.h> 
#define dataPin 11
#define cmndPin 12
#define attPin 15
#define clockPin 16

#define LEDPin 13

Psx psx; 

void R1Callback(bool state);
void L1Callback(bool state);
void R2Callback(bool state);
void L2Callback(bool state);
void crossCallback(bool state);
void roundCallback(bool state);
void triangleCallback(bool state);
void squareCallback(bool state);

void upCallback(bool state);
void downCallback(bool state);
void leftCallback(bool state);
void rightCallback(bool state);

void selectCallback(bool state);
void startCallback(bool state);



void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(300);
  }
  psx.setupPins(dataPin, cmndPin, attPin, clockPin, 50);
  psx.setR2Callback(R2Callback);
  psx.setL2Callback(L2Callback);
  psx.setR1Callback(R1Callback);
  psx.setL1Callback(L1Callback);

  psx.setCrossCallback(crossCallback);
  psx.setRoundCallback(roundCallback);
  psx.setTriangleCallback(triangleCallback);
  psx.setSquareCallback(squareCallback);

  psx.setUpCallback(upCallback);
  psx.setDownCallback(downCallback);
  psx.setRightCallback(rightCallback);
  psx.setLeftCallback(leftCallback);

  psx.setSelectCallback(selectCallback);
  psx.setStartCallback(startCallback);
  pinMode(LEDPin, OUTPUT);
}

void loop()
{
  psx.update();
  digitalWrite(LEDPin, psx.getStart());
}

void R2Callback(bool state)
{
  Serial.print("R2 ");
  Serial.println(state);
}

void L2Callback(bool state)
{
  Serial.print("L2 ");
  Serial.println(state);
}

void R1Callback(bool state)
{
  Serial.print("R1 ");
  Serial.println(state);
  digitalWrite(LEDPin, HIGH);
}

void L1Callback(bool state)
{
  Serial.print("L1 ");
  Serial.println(state);
  digitalWrite(LEDPin, LOW);
}

void crossCallback(bool state)
{
  Serial.print("X ");
  Serial.println(state);
}

void roundCallback(bool state)
{
  Serial.print("O ");
  Serial.println(state);
}

void triangleCallback(bool state)
{
  Serial.print("triangle ");
  Serial.println(state);
}

void squareCallback(bool state)
{
  Serial.print("square ");
  Serial.println(state);
}

void upCallback(bool state)
{
  Serial.print("up ");
  Serial.println(state);
}

void downCallback(bool state)
{
  Serial.print("down ");
  Serial.println(state);
}

void leftCallback(bool state)
{
  Serial.print("left ");
  Serial.println(state);
}

void rightCallback(bool state)
{
  Serial.print("right ");
  Serial.println(state);
}

void selectCallback(bool state)
{
  Serial.print("select ");
  Serial.println(state);
}

void startCallback(bool state)
{
  Serial.print("start ");
  Serial.println(state);
}
