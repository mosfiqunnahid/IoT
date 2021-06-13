#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
int led = D1;   
int button = D4; 
int temp = 0;    

void setup() {
  pinMode(led, OUTPUT);  
  pinMode(button, INPUT);
  Serial.begin(115200);
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led, HIGH);
    Serial.println("Not Connected - LED Turned ON");
  }
  WiFiManager wifiManager;
  Serial.println("Conecting....");
  wifiManager.autoConnect("Mrinmoy");
  Serial.println("Connected");
}

void resetWifi() {
  WiFiManager wm;
  wm.resetSettings();
  Serial.println("Reset Done!");
}

void loop() {
  temp = digitalRead(button);

  Serial.println(temp);

  if (temp == LOW) {
    resetWifi();
    ESP.restart();
  }
  else {
    digitalWrite(led, LOW);
    Serial.println("Connected - LED Turned OFF");
  }
}
