/*********
 Kelvin Carrington Tichana
 IoTFinal Project
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT.h"
#include "EEPROM.h"
#include <HTTPClient.h>
#include <Ethernet.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define EEPROM_SIZE 2
#define hbled 26
float HumidityData;
float TemperatureData;
const int sensorPin = 34;
const int ledPin = 33;

//Set up some global variables for the light level an initial value.
int lightInit;  // initial value
int lightVal;   // light reading
float humidityData;
float temperatureData[10] ={};
float LightIntensity;
float Temperature;
float values[10] = {};

DHT dht(DHTPIN, DHTTYPE);


// Replace with your network credentials
const char* ssid = "Kelvin";
const char* password = "epoch500";
//WiFiClient client;
char host[] = "localhost";   //eg: 192.168.0.222
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address
WiFiClient client;
IPAddress ip(172,16,0,223); 
//EthernetClient client1; 
// Set LED GPIO for the heartbeat
const int ledPin2 = 25;
// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncEventSource events("/events");

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin2)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
}
 String processor2(const String& var){
  
  //Serial.println(var);
  if(var == "HumidityData"){
    return String(HumidityData);
  }
  
  
}
 
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(hbled, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
  

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin2, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin2, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
//Route to display sensor values
server.on("/HumidityData", HTTP_GET, [](AsyncWebServerRequest *request){
    //HumidityData;    
    request->send(SPIFFS, "/index.html", String(), false, processor2);
  });
  // Start server
  server.begin();
  Serial.println(F("DHT22 test!"));
  // We'll set up the LED pin to be an output.
  pinMode(ledPin, OUTPUT);
  lightInit = analogRead(sensorPin);
  dht.begin();
  EEPROM.begin(EEPROM_SIZE);
  HumidityData = EEPROM.read(0);
  TemperatureData = EEPROM.read(1);
}
 
void loop(){
  lightVal = analogRead(sensorPin); // read the current light levels
 
  //if lightVal is less than our initial reading withing a threshold then it is dark.
  if(lightVal - lightInit < 3)
  {
      digitalWrite (ledPin, HIGH); // turn on light
  }
  
  //otherwise, it is bright
  else
  {
    digitalWrite (ledPin, LOW); // turn off light
  }
  LightIntensity = lightVal - lightInit;
 Serial.print("LightIntensity");
Serial.println(lightVal - lightInit);
// Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  for(int i; i<10;i++){
    EEPROM.write(0, HumidityData);
    EEPROM.write(1, TemperatureData);
  }
  EEPROM.commit();
  // Read temperature as Celsius (the default)
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, Humidity);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(Temperature, Humidity, false);

  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  //Sending_To_phpmyadmindatabase(); 
  
  digitalWrite(hbled, HIGH);
  delay(1000);
  digitalWrite(hbled, LOW);
  delay(1000);
  doReq();
  delay(3000); // interval of 3 seconds
}




/**
//function to send to db
void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(host, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET http://localhost/iot/HelloWorld.php?Humidity=");
    client.print("GET http://localhost/iot/HelloWorld.php?Humidity=");     //YOUR URL
    Serial.println(humidityData);
    client.print(humidityData);
    Serial.println(LightIntensity);
    client.print(LightIntensity);
    client.print("&Temperature=");
    Serial.println("&Temperature=");
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: Your Local IP");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
}
**/
void doReq(){
  
  if((WiFi.status() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        
        http.begin(("http://172.20.10.10/iot/HelloWorld.php?""LightIntensity="+String(LightIntensity)+ "&Temperature="+String(Temperature)).c_str()); //HTTP
       

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    
   // server.handleClient();

  //EEPROM.write(0, humid);
  //EEPROM.commit();
}
