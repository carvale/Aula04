/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.


  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleDHT.h>
int pinDHT11 = D6; // Pino onte está conectado o DHT11
SimpleDHT11 dht11(pinDHT11);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "seu codigo";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IoT 2019";
char pass[] = "12345678";


BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  //Variáveis
      byte temperatura = 20;
      byte umidade = 50;
      int err = SimpleDHTErrSuccess;

      if ((err = dht11.read(&temperatura, &umidade, NULL)) != SimpleDHTErrSuccess) {
        Serial.print("Leitua DHT11 com falha, err="); 
        Serial.println(err);
        delay(1000);
        return;
      }
      
      Serial.print("Leitura OK: ");
      Serial.print((int)temperatura); Serial.print(" *C, "); 
      Serial.print((int)umidade); Serial.println(" %");

      
      
      digitalWrite(D4, LOW);//Pisca
      delay(500);
 
  Blynk.virtualWrite(V5, (int)umidade);
  Blynk.virtualWrite(V6, (int)temperatura);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(D4, OUTPUT); // Incializa o D4  como saída

  Blynk.begin(auth, ssid, pass);


  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}