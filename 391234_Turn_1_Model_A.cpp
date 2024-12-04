#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your_ssid";
const char* password = "your_password";
const char* mqtt_server = "your_mqtt_broker.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "temperature";
const char* client_id = "ESP32_Client";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  float temp = analogRead(A0) * 0.06; // Example temperature reading
  String message = String(temp);
  Serial.print("Publishing message: ");
  Serial.println(message);

  client.publish(mqtt_topic, message.c_str());

  delay(10000); // Delay for 10 seconds
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(client_id)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");
      delay(5000);
    }
  }
}
