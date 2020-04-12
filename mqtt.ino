#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "nodemcu";
const char* password =  "espconnect";

const char* mqttServer = "localhost";
const int mqttPort = 1883;
const char* mqttUser = "macuser";
const char* mqttPassword = "macpassword";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from the other side!!");
  client.subscribe("esp/test");
 
}

void loop() {
  
}

