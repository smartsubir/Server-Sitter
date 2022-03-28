#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>;

/* DHT SENSOR SETUP */
#define DHTTYPE DHT22
#define DHTPIN  D6

DHT dht(DHTPIN, DHTTYPE,11);
float humidity, temp_f;  // Values read from 

const char* ssid = "Smart_PC";
const char* password = "subir_pc";

//define the parameters for the IFTTT
#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "ESP_DHT22"
#define IFTTTKEY "bFIu_YatRT40VVWYIY2VpyianAo-gjSFZAfxtcVwe0k"

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  delay(2000);
  temp_f = dht.readTemperature();
  humidity = dht.readHumidity();
  WiFi.begin(ssid, password);
  client.setInsecure();
  client.setTimeout(5000);
  Serial.println("");
  Serial.print("Waiting to connect to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  Serial.print("Initial Temp: ");
  Serial.print(temp_f);
  Serial.print(" Cel.\nInitial Humi: ");
  Serial.print(humidity);
  Serial.print("%\n");
}
void loop() { 
  //close any previous connection
    //delay(180000);
    temp_f = dht.readTemperature();
    humidity = dht.readHumidity();

  if (client.connected())
  {
    client.stop();
  }
  // wait until all the data has been sent
  client.flush();

  String toSend = "GET /trigger/";
    //String toSend = "GET /trigger/ESP_DHT22/with/key/bFIu_YatRT40VVWYIY2VpyianAo-gjSFZAfxtcVwe0k"
    toSend += EVENTO;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += temp_f;
    toSend += "&value2=";
    toSend += humidity;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";
    Serial.println(toSend);
//    client.setInsecure();
//    client.setTimeout(5000);
  if (client.connect(HOSTIFTTT,443)) {
    Serial.println("Connected");
    // build the HTTP request
    if(temp_f > 25.0) { 
      client.print(toSend);
      delay(1000*60*1);
    }
    
  } else {
    Serial.println("Not Connected");
  }
  client.flush();
  client.stop();  
  delay(500);
  
}
