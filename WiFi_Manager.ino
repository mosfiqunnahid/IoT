#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void setup() {
Serial.begin(115200);
WiFiManager wifiManager;
Serial.println("Conecting....");
wifiManager.autoConnect("Mrinmoy");
Serial.println("Connected");
}
void loop(){
}
