#include <EspMQTTClient.h>
#include <ArduinoJson.h>

int enA = 16;
int in1 = 14;
int in2 = 12;

int vel = 250;

EspMQTTClient client(
  //"Greppi-2G",
  "WIFI-SSID",
  //"withProxy",
  "WIFI-PASSWORD",
  //"172.17.3.46",
  "BROKER ID",
  "",
  "",
  "ESP8266_Motore",
  1883
);

void ricevi(String payload){
  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, payload);
  const char* dir = doc["direzione"];
  vel = doc["velocità"]; 
  Serial.println(dir);
  if(strcmp(dir, "destra") == 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, vel);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, vel);
  }
}

void onConnectionEstablished(){
 client.subscribe("tps/motore", ricevi);
}


void setup() {
  Serial.begin(9600);
  client.enableDebuggingMessages();
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  client.loop();
}
