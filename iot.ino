//port 5 kiri

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLEP9TVAyR"
#define BLYNK_DEVICE_NAME "TIMBANGAN"
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266wifi.h>
BlynkTimer timer;

char auth[] = "crHZ02B5i8agQkMzjaQMxBVJ1XJOc-ha";
char ssid[] = "PULU PULU";
char pass[] = "16011601";
int tim1, tim2, tim, timtot;
int war, wartot;
int war1 = 0;
int war3 = 0;

SoftwareSerial NodeMCU1(D2, D1); //Timbangan
SoftwareSerial NodeMCU2(D4, D3); //Conveyor

void timbang() {
  if (NodeMCU1.available() > 0) { //jika data tersedia maka akan melanjutkan program
    tim = NodeMCU1.parseInt(); //menginisiasi variabel tim untuk mengubah tipe data input NodeMCU1 menjadi float
    if (NodeMCU1.read() == '\n') {
      Serial.println(tim); //menampilkan output variabel tim pada serial monitor
      if (tim >= 1000 && tim <= 1100) {
        tim1 = tim;
        tim1 = tim1 - 1000;
        Serial.print("tim1 : ");
        Serial.println(tim1); //menampilkan output variabel tim1 pada serial monitor
        Blynk.virtualWrite(V1, tim1); //menampilkan output variabel tim1 pada virtual pin V1 blynk
      }
      if (tim >= 10 && tim <= 110) {
        tim2 = tim;
        tim2 = tim2 - 10;
        Serial.print("tim2 : ");
        Serial.println(tim2); //menampilkan output variabel tim2 pada serial monitor
        Blynk.virtualWrite(V2, tim2); //menampilkan output variabel tim2 pada virtual pin V2 blynk
      }
    }
  }
}
/*  pada void timbang terdapat 2 input dari load cell, dikarenakan metode software serial
    tidak dapat mengetahui mana load cell 1 atau load cell 2 maka dilakukan rekayasa input
    pada program arduino agar tidak membingungkan nodemcu untuk membedakan input load cell 1 atau load cell 2,
    load cell 1 akan ditambah input sebesar 12(jika input = 2 maka akan menjadi 14). sedangkan pada,
    load cell 2 akan ditambah input sebesar 5 (jika input = 2 maka akan menjadi 7).
    setelah itu program nodemcu akan mendeteksi nilai inputan dari program arduino
    apabila nilai input lebih dari 12 dan kurang dari 17 maka input tersebut merupakan inputan dari load cell 1
    apabila nilai input lebih dari 5  dan kurang dari 10 maka input tersebut merupakan inputan dari load cell 2
    setelah itu nodemcu akan mengurangi input tersebut sesuai dengan pengelompokan load cell masing-masing
    (apabila nilai input termasuk kelompok load cell 1 maka nilai akan dikurangi 12)
    (apabila nilai input termasuk kelompok load cell 2 maka nilai akan dikurangi 5)
*/

void warna() {
  if (NodeMCU2.available() > 0) {
    war = NodeMCU2.parseInt(); //menginisiasi variabel tim untuk mengubah tipe data input NodeMCU2 menjadi integer
    if (NodeMCU2.read() == '\n') {
      Serial.println(war); //menampilkan output variabel war pada serial monitor
      if (war >= 10000 && war <= 10100) {
        war1 = war;
        war1 = war1 - 10000;
        Serial.print("Warna merah : ");
        Serial.println(war1);
        Blynk.virtualWrite(V5, war1); //menampilkan output variabel war1 pada virtual pin V5 blynk
        Blynk.virtualWrite(V3, HIGH); //mengubah nilai variabel V3 blynk menjadi high (LED)
        delay(2300);
        Blynk.virtualWrite(V3, LOW);
      }
      if (war >= 20000 && war <= 20200 ) {
        war3 = war;
        war3 = war3 - 20000;
        Serial.print("Warna coklat : ");
        Serial.println(war3);
        Blynk.virtualWrite(V7, war3); //menampilkan output variabel war1 pada virtual pin V7 blynk
        Blynk.virtualWrite(V4, HIGH);
        delay(2300);
        Blynk.virtualWrite(V4, LOW);
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  NodeMCU1.begin(9600);
  NodeMCU2.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
  timer.setInterval(400L, timbang);
  timer.setInterval(400L, warna);
}
