#include<Wire.h>
#include <Servo.h> 

Servo myservo;

void setup(){
myservo.attach(9);
myservo.write(0);
}

void loop(){  
  myservo.write(30);
  delay(2000);
  myservo.write(60);
  delay(2000);
}
