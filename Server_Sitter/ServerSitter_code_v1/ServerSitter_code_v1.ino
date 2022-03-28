#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>;

/* DHT SENSOR SETUP */
#define DHTTYPE DHT22
#define DHTPIN1  D5
#define DHTPIN2  D6
#define DHTPIN3  D7
#define TEMP_LIMIT 30.0 //temperature limit for sending alert
#define DELAY_MINUTES 5 //Delay in minutes between sending alerts

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
float humidity1 = 0, humidity2, humidity3, temp_f1 = 0.0, temp_f2, temp_f3, humidity, temp_f;  // Values read from 

const char* ssid = "Computer Center";
const char* password = "cc@12345";

//define the parameters for the IFTTT
#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "Server_Room_Over_Heating"
#define IFTTTKEY "fG4mzp5izSc3z6Uze1F0V"

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht1.begin();
  delay(200);
  dht2.begin();
  delay(200);
  dht3.begin();
  delay(2000);
  temp_f1 = dht1.readTemperature();
  humidity1 = dht1.readHumidity();
  delay(200);
  temp_f2 = dht2.readTemperature();
  humidity2 = dht2.readHumidity();
  delay(200);
  temp_f3 = dht3.readTemperature();
  humidity3 = dht3.readHumidity();
  delay(200);
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
  temp_f1 = dht1.readTemperature();
  humidity1 = dht1.readHumidity();
  delay(200);
  temp_f2 = dht2.readTemperature();
  humidity2 = dht2.readHumidity();
  delay(200);
  temp_f3 = dht3.readTemperature();
  humidity3 = dht3.readHumidity();
  delay(200);

  Serial.println("Temperature Values: ");
  Serial.print(temp_f1);
  Serial.print("\t");
  Serial.print(temp_f2);
  Serial.print("\t");
  Serial.print(temp_f3);
  Serial.println("");
  Serial.println("Humidity Values: ");
  Serial.print(humidity1);
  Serial.print("\t");
  Serial.print(humidity2);
  Serial.print("\t");
  Serial.print(humidity3);
  Serial.println("");

  temp_f = temp_f1;
  if(temp_f <= temp_f2) temp_f = temp_f2;
  if(temp_f <= temp_f3) temp_f = temp_f3;

  humidity = humidity1;
  if(humidity <= humidity2) humidity = humidity2;
  if(humidity <= humidity3) humidity = humidity3;

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
    if(temp_f > TEMP_LIMIT) { 
      client.print(toSend);
      delay(1000*60*DELAY_MINUTES);
    }
    
  } else {
    Serial.println("Not Connected");
  }
  client.flush();
  client.stop();  
  delay(500);
  
}
