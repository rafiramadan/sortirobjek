#include<Wire.h>
#include<Servo.h>

Servo rotasi;
Servo kiri;
Servo kanan;
Servo gripper;

int a;
int b;

void maju(){
  for(b=90;b>=75;b--){
    kiri.write(b);
    delay(20);
    }
  }
  
void pack1(){
  for(a=5;a<=90;a++){
    rotasi.write(a);
    delay(5);
  }
 }

 void pack2(){
  for(a=5;a<=45;a++){
    rotasi.write(a);
    delay(5);
  }
 }
 
void armsatu(){
  rotasi.write(5);
  delay(2000);
  kanan.write(130);
  delay(2000);
  maju();
  delay(2000);
  gripper.write(20);
  delay(5000);
  gripper.write(90);
  delay(2000);
  kanan.write(60);
  delay(1000);
  pack1();
  delay(2000);
  kiri.write(120);
  delay(2000);
  kanan.write(90);
  delay(2000);
  gripper.write(20);
  delay(2000);
  }


void armdua(){
  rotasi.write(5);
  delay(1000);
  kanan.write(130);
  delay(1000);
  kiri.write(75);
  delay(1000);
  gripper.write(20);
  delay(1000);
  gripper.write(90);
  delay(1000);
  kanan.write(60);
  delay(1000);
  pack2();
  delay(1000);
  kiri.write(80);
  delay(1000);
  kanan.write(110);
  delay(1000);
  gripper.write(20);
  delay(1000);
  }
  
void setup(){
  rotasi.attach(9); //kanan kiri
  kiri.attach(10); //maju mundur
  kanan.attach(11); //atas bawah
  gripper.attach(12); //capit
}

void loop(){
  armsatu();
  //armdua();
}
