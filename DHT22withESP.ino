#include <DHT.h>;

//Constants
#define DHTPIN D2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup()
{
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
    delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(10000); //Delay 2 sec.
}































//#include "DHTesp.h"
//#ifdef ESP32
//#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
//#error Select ESP8266 board.
//#endif
//DHTesp dht;
//void setup()
//{
//  Serial.begin(115200);
//  Serial.println();
//  Serial.println("Status\tHumidity (%)\tTemperature (C)");
//  // Autodetect is not working reliable, don't use the following line
//  // dht.setup(17);
//  // use this instead: 
//  dht.setup(5, DHTesp::DHT22); // Connect DHT sensor to GPIO 5
//}
//void loop()
//{
//  delay(2000);
//  float humidity = dht.getHumidity();
//  float temperature = dht.getTemperature();
//  Serial.print(dht.getStatusString());
//  Serial.print("\t");
//  Serial.print(humidity, 1);
//  Serial.print("\t\t");
//  Serial.println(temperature, 1);
//}
