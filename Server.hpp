AsyncWebServer server(80);

int esta1 = false;
int esta2 = false;
int esta3 = false;
int esta4 = false;
int cortina = false;

//#include "ESP8266_Utils_Server.hpp"

void handleCoche(AsyncWebServerRequest *request)
{
  digitalWrite(15, esta1 ? LOW: HIGH );
  esta1 = !esta1;
  request->send(202,"text/plain", "Garaje encendido");
}

void handleSala(AsyncWebServerRequest *request){
  digitalWrite(13, esta2 ? LOW: HIGH );
  esta2 = !esta2;
  request->send(202,"text/plain", "Sala encendida");
}

void handleComedor(AsyncWebServerRequest *request){
  digitalWrite(12, esta3 ? LOW: HIGH );
  esta3 = !esta3;
  request->send(202,"text/plain", "Sala encendida");
}

void handleAlcoba(AsyncWebServerRequest *request){
  digitalWrite(14, esta4 ? LOW: HIGH );
  esta4 = !esta4;
  request->send(202,"text/plain", "Sala encendida");
}


void handlerTempe (AsyncWebServerRequest *request){
  Serial.println("tempe foto");
  digitalWrite(5,HIGH);
  int fo = analogRead(A0);
  digitalWrite(5,LOW);

  digitalWrite(4,HIGH);
  int tem = analogRead(A0);
  Serial.println(tem);
  digitalWrite(4,LOW);

  String res = String(fo)+"-"+String(tem);
  request->send(202,"text/plain", res);

   if (fo < 50){
    tone(0,220);
    digitalWrite(15,HIGH);
    Talanquera.write(180);
    esta1 = !esta1;
  }
}

void handlerAlarma (AsyncWebServerRequest *request){
  noTone(0);

  request->send(202,"text/plain", "ok");
}

void handlerCortina (AsyncWebServerRequest *request){
  if (cortina == true){
    Cortina.write(180);
    cortina = !cortina;
  }else{
    Cortina.write(0);
    cortina = !cortina;
  }
  request->send(202,"text/plain", "ok");
}

void handlerTalanquera (AsyncWebServerRequest *request){
   Talanquera.write(90);
   request->send(202,"text/plain", "ok");
}
void InitServer()
{
	server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

	server.on("/coche", HTTP_POST, handleCoche);
  server.on("/sala", HTTP_POST, handleSala);
  server.on("/comedor", HTTP_POST, handleComedor);
  server.on("/alcoba", HTTP_POST, handleAlcoba);

  
  server.on("/tempe", HTTP_POST, handlerTempe);

  server.on("/alarma", HTTP_POST, handlerAlarma);
  server.on("/cortina", HTTP_POST, handlerCortina);
  
  server.on("/talanquera", HTTP_POST, handlerTalanquera);
	server.onNotFound([](AsyncWebServerRequest *request) {
		request->send(400, "text/plain", "Not found");
	});
  
	server.begin();
    Serial.println("HTTP server started");
}
