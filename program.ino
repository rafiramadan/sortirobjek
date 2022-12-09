#include <SoftwareSerial.h>
SoftwareSerial warna (3, 2);
#include<Wire.h>
#include<Servo.h>

Servo rotasi;
Servo kiri;
Servo kanan;
Servo gripper;

const int EnB = 7;
const int In1 = 6;
const int sensorIR = 8;
const int S0 = 13; //pin S0 TCS3200 ke pin 4 Arduino
const int S1 = 12; //pin S1 TCS3200 ke pin 5 Arduino
const int S2 = 11; //pin S2 TCS3200 ke pin 6 Arduino
const int S3 = 10; //pin S3 TCS3200 ke pin 7 Arduino
const int sensorOut = 9;
int IR1;
int red = 0;
int green = 0;
int blue = 0;
int kunciWarna = 0;
int kunciIR;
int kunci;
int oranye = 0;
int merah = 0;
int a;
int b;
int c;
int d;

void capit() {
  for (d = 0; d <= 30; d++) {
    gripper.write(d);
    delay(5);
  }
}

void maju1() {
  for (b = 90; b >= 25; b--) {
    kiri.write(b);
    delay(20);
  }
}

void maju2() {
  for (b = 80; b >= 40; b--) {
    kiri.write(b);
    delay(20);
  }
}

void atas() {
  for (c = 84; c >= 70; c--) {
    kanan.write(c);
    delay(10);
  }
}

void mundur() {
  for (b = 32; b <= 82; b++) {
    kiri.write(b);
    delay(20);
  }
}

void pack1() {
  for (a = 5; a <= 90; a++) {
    rotasi.write(a);
    delay(20);
  }
}

void pack2() {
  for (a = 5; a <= 45; a++) {
    rotasi.write(a);
    delay(20);
  }
}

void armsatu() {
  capit(); //capit
  delay(2000);
  atas(); //atas
  delay(1000);
  mundur();
  delay(2000);
  pack1(); //rotasi
  delay(1000);
  gripper.write(0); //lepas
  delay(2000);
  rotasi.write(0); //rotasi
  delay(2000);
  kanan.write(85); //bawah
  delay(2000);
  maju1();
  delay(2000);
  gripper.write(0);
}


void armdua() {
  capit(); //capit
  delay(2000);
  atas(); //atas
  delay(1000);
  mundur();
  delay(2000);
  pack2(); //rotasi
  delay(2000);
  maju2(); //maju
  delay(2000);
  gripper.write(0); //lepas
  delay(1000);
  kiri.write(80); //mundur
  delay(1000);
  rotasi.write(0); //rotasi
  delay(1000);
  kanan.write(85); //bawah
  delay(2000);
  maju1();
  delay(2000);
  gripper.write(0);
}

void setup() {
  Serial.begin(115200);
  warna.begin(9600);
  pinMode(S0, INPUT); //tcs3200 ke pin 4 arduino
  pinMode(S1, INPUT); //tcs3200 ke pin 5 arduino
  pinMode(S2, INPUT); //tcs3200 ke pin 6 arduino
  pinMode(S3, INPUT); //tcs3200 ke pin 7 arduino
  pinMode(EnB, OUTPUT);
  pinMode(In1, INPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  rotasi.attach(30); //kanan kiri
  kiri.attach(31); //maju mundur
  kanan.attach(32); //atas bawah
  gripper.attach(4); //capit

  rotasi.write(0);
  delay(2000);
  kanan.write(84);
  delay(2000);
  maju1();
  delay(2000);
  gripper.write(0);
  delay(2000);
}

void loop() {
  kunciIR = 0;
  kunci = 0;

  IR1 = digitalRead(sensorIR);
  if (IR1 == 1) {
    digitalWrite(In1, HIGH);
    analogWrite(EnB, 150);
  } else {
    digitalWrite(In1, LOW);
    delay(1000);
  }

  //pembacaan filter RED photodioda TCS3200
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(sensorOut, LOW); //pulseIn untuk membaca pulsa HIGH atau LOW

  //pembacaan filter GREEN photodioda TCS3200
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = pulseIn(sensorOut, LOW);

  //pembacaan filter BLUE photodioda TCS3200
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = pulseIn(sensorOut, LOW);

  Serial.print("IR 1 Detect: ");
  Serial.print(IR1);
  Serial.print(" R Intensity: ");
  Serial.print(red);
  Serial.print(" G Intensity: ");
  Serial.print(green);
  Serial.print(" B Intensity : ");
  Serial.print(blue);
  Serial.println();

  if (red >= 8 && red <= 15 && green >= 8 && green <= 15 && blue >= 8 && blue <= 15 && kunciWarna == 0 && IR1 == 0) {
    Serial.println(" Objek Berwarna Merah");
    merah++;
    warna.print(merah + 10000);
    warna.println("\n");
    kunciWarna = 1;
    digitalWrite(In1, HIGH);
    analogWrite(EnB, 150);
    delay(2500);
    digitalWrite(In1, LOW);
    armsatu(); //memanggil fungsi armSatu
  }

  //jika parameter if terpenuhi (warna coklat terbaca) maka program akan dijalankan
  else if (red >= 0 && red <= 7 && green >= 0 && green <= 7 && blue >= 0 && blue <= 7 && kunciWarna == 0 && IR1 == 0) {
    Serial.println(" Objek Berwarna Oranye");
    oranye++;
    warna.print(oranye + 20000);
    warna.println("\n");
    kunciWarna = 1;
    digitalWrite(In1, HIGH);
    analogWrite(EnB, 150);
    delay(2500);
    digitalWrite(In1, LOW);
    armdua();
  }
  else if (IR1 == 1 && kunciWarna == 1) {
    kunciWarna = 0;
  }
}
