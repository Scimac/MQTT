#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "nodemcu";
const char* password =  "espconnect";

const char* mqttServer = "localhost";
const int mqttPort = 1883;
const char* mqttUser = "macuser";
const char* mqttPassword = "macpassword";
int   sensor_data;
string converted_data;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 
 pinMode(A0,INPUT) 
 
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
 
  client.publish("esp/test",converted_data);
  client.subscribe("esp/test");
 
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
 sensor_data= analogRead(A0);
 sensor_data= sensor_data*1024/5; // You can scale the data according to the sensor values general
  converted_data = sensor_data;    // formula being sensor_data= sensor_data*x/5 , x is the scale to be chosen.
 client.loop();                      
}
