#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Servo.h>
Servo Cortina;
Servo Talanquera;

#include "config.h"  
#include "Server.hpp"
#include "ESP8266_Utils.hpp"

// luces
const int coche = 15;
const int sala = 13;
const int comedor = 12;
const int alcoba = 14;
// servos 
const int persiana = 16;
const int talanquera = 2;
// altavoz
const int altavoz = 0;
// sensores analogos 
const int temperatura = 4;
const int fotoResistencia = 5;

void setup(void)
{
	pinMode(LED_BUILTIN, OUTPUT);

  //LUCES
  pinMode(coche, OUTPUT);
  pinMode(sala, OUTPUT);
  pinMode(comedor, OUTPUT);
  pinMode(alcoba, OUTPUT);
  //SENSORES ANALOGICOS 
  pinMode(temperatura, OUTPUT);
  pinMode(fotoResistencia, OUTPUT);
  //ALTAVOZ
  pinMode(altavoz,OUTPUT);
  //SERVOS
  Cortina.attach(persiana);
  Cortina.write(180);
  
  Talanquera.attach(talanquera);
  Talanquera.write(90);
  
	Serial.begin(115200);
	SPIFFS.begin();
 	
	ConnectWiFi_STA();
	InitServer();
}

void loop(void)
{
    
}
