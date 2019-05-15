#include <TimerOne.h>

const int Trig = 11; //Çıkış yüzeyinden dalganın salınmasını sağlayan çıkış pini
const int Echo = 12; //Giriş yüzeyine yansıyan dalganın ulaştığını Arduino'ya haber veren giriş pini

const int Buzzer = 13; //Buzzer pin çıkışı
const int KirmiziLED = 10; //Kapı açıldığı zaman yanan ledin çıkış pini
const int SariLED = 9; //Kapı kapalıyken yanan ledin çıkış pini
const int MaviLED = 8; //Interrupt için kulllanılan ve kapı açıkken yanıp sönen ledin çıkış pini

String LEDDurumu = "OFF";
int  Sure  = 0;
int  Mesafe = 0;

void setup() {

  pinMode (Trig , OUTPUT);
  pinMode (Echo , INPUT);

  pinMode (Buzzer , OUTPUT);
  pinMode (KirmiziLED , OUTPUT);
  pinMode (SariLED , OUTPUT);
  pinMode (MaviLED , OUTPUT);

  Timer1.initialize(500000);
  Timer1.attachInterrupt( MaviLedInterrupt );
  Serial.begin(9600);
}

void loop() {
  digitalWrite(Trig , HIGH); //Sensöre ses dalgasını üretmesi için emir verildi
  delayMicroseconds(1000);
  digitalWrite(Trig, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

  Sure = pulseIn(Echo , HIGH); //Ses dalgasının geri dönmesi için geçen süre ölçülüyor
  Mesafe = (Sure / 2) / 28.5; //Ölçülen süre uzaklığa çevriliyor
  Serial.println(Mesafe);
  if ( Mesafe >= 10 )
  {
    digitalWrite(Buzzer , HIGH); 
    delay(25);
    digitalWrite(Buzzer , LOW); 
    delay(15);
    digitalWrite(KirmiziLED , HIGH);
    digitalWrite(SariLED , LOW);
  }
  else
  {
    digitalWrite(Buzzer , LOW);
    digitalWrite(KirmiziLED , LOW);
    digitalWrite(SariLED , HIGH);
  }
}

void MaviLedInterrupt() //Interrupt kodu
{
  if ( Mesafe >= 10 ) //Kapı açıksa mavi led yanıp söner
  {
    if (LEDDurumu == "ON") {
      digitalWrite(MaviLED, LOW);
      LEDDurumu = "OFF";
      return;
    }
    if (LEDDurumu == "OFF") {
      digitalWrite(MaviLED, HIGH);
      LEDDurumu = "ON";
      return;
    }
  }
  digitalWrite(MaviLED, LOW); //Kapı kapanınca mavi led söner
}


