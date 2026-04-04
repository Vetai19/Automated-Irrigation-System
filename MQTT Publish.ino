//ESP8266: MQTT Gateway 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Honor 8X_160C";
const char* password = "123456";
const char* mqttServer = "m10.cloudmqtt.com";
const int mqttPort = 12038; 
const char* mqttUser = "uthzmxvn"; 
const char* mqttPassword = "nDjWmfSZ-aUD";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600); // Listen to Arduino
  WiFi.begin(ssid, password);
  client.setServer(mqttServer, mqttPort);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    client.publish("GG", data.c_str());
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266_Gate", mqttUser, mqttPassword)) {
      client.subscribe("GG");
    } else { delay(2000); }
  }
}
