#include <FirebaseArduino.h>
#include "DHT.h"

#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "server-sitter.firebaseio.com"
#define WIFI_SSID "Vivekananda Hostel" // Change the name of your WIFI
#define WIFI_PASSWORD "vh@12345" // Change the password of your WIFI

#define DHTPIN 14    // Data Pin of DHT 22 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 22
DHT dht(DHTPIN, DHTTYPE);

void setup() {

 
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {
 
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  delay(200);
}
