#include<SoftwareSerial.h>

#define TxD 3
#define RxD 2
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin D2
#define LED_PIN 13
DHT dht(dht_dpin, DHTTYPE);
SoftwareSerial bluetoothSerial(TxD,RxD);
int pin=A5;
int red=7;
int green=8;
int sensor;
int percent;
int motor=A3;

void setup() {
  // put your setup code here, to run once:
 
  bluetoothSerial.begin(9600);
  Serial.begin(9600);
  pinMode(pin,INPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  Serial.begin(9600);
  pinMode(motor,OUTPUT);
  pinMode(LED_PIN,OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  char c;
 dht.begin();
  sensor=analogRead(pin);
  percent=map(sensor,1030,250,0,100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();        
  Serial.println(t+"." + h + "." + percent);  
if(bluetoothSerial.available())
  {
    c = bluetoothSerial.read();
    Serial.println(c);
    if(c== '1')
    {
      analogWrite(motor,150);
    }
    if(c== '0')
    {
      analogWrite(motor,0);
      digitalWrite(LED_PIN,LOW);
    }
  }
}
