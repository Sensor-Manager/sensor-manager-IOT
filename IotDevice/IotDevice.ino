#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> 
#include "DHT.h"        
#define DHTTYPE DHT11

#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE);

String humi = "";
String temp = "";

void setup() {
  Serial.begin(9600);
  
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature\n\n");
  delay(700);

  
  WiFi.begin("wifi name here", "Wifi password here");
  
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.println("."); 
    delay(500);
  } 

   Serial.println(""); 
  Serial.println("Wi-Fi connected"); 
  Serial.println("IP Address : ");
   Serial.println(WiFi.localIP()); 

  
}

void loop() 
{
  char buf1[64];
  char buf2[64];
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  humi = String(h);
  temp = String(t);
  sprintf (buf1, "The Humidity currently is %f percentage \r\n", h);
  sprintf (buf2, "The temperature currently is %f C\r\n", t);
  Serial.print(buf1);
  Serial.print(buf2);
  delay(800);

  
  WiFiClient client;
  HTTPClient http;
  http.addHeader( "Content-Type", "application/json");
  http.addHeader("Accept", "application/json");

  DynamicJsonDocument postMessage(2048);
  postMessage["temperature"] = temp;
  postMessage["humidity"] = humi;
  String jsonBody;
  serializeJson(postMessage, jsonBody);
  

  http.begin(client,"http://192.168.0.11:8080/");
  int resCode = http.POST(jsonBody);

  Serial.print(resCode);
  
  String res = http.getString();
  Serial.print(res);

  parserMessage(res);
  delay(3000);
}

void parserMessage(String res){
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, res);
  const char* _message = doc["message"];
  const char* _name = doc["name"];
  Serial.print("message: ");
  Serial.println(_message);

 Serial.print("name: ");
  Serial.println(_name);
}
