#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>
#include "DHT.h"
#define DHTTYPE DHT22 

const int DHTPin = D2; 
DHT dht(DHTPin, DHTTYPE);

#define ON_Board_LED 2  

const char* host = "script.google.com";
const int httpsPort = 443;


WiFiClientSecure client; 
String GAS_ID = "";


void setup() {

  Serial.begin(115200);
  delay(500);
  WiFiManager wifiManager;
  Serial.println("Conecting....");
  wifiManager.autoConnect("Mrinmoy");
  Serial.println("Connected");

  dht.begin(); 
  delay(500);

  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  
  digitalWrite(ON_Board_LED, HIGH); 
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  client.setInsecure();
}

void loop() {

  int h = dht.readHumidity();

  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor !");
    delay(500);
    return;
  }
  String Temp = "Temperature : " + String(t) + " °C";
  String Humi = "Humidity : " + String(h) + " %";
  Serial.println(Temp);
  Serial.println(Humi);
  
  sendData(t, h);
  delay(2000);
}


void sendData(float tem, int hum) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String string_temperature =  String(tem);
  // String string_temperature =  String(tem, DEC); 
  String string_humidity =  String(hum, DEC); 
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + string_temperature + "&humidity=" + string_humidity;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();

} 
