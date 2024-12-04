#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "SensorNodeClient"
#define TOPIC       "agriculture/field1/sensors"
#define PAYLOAD     "24.5"  // Example payload representing temperature
#define QOS         1
#define TIMEOUT     10000L

void publishMessage(MQTTClient client, char* payload)
{
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;
    
    pubmsg.payload = payload;
    pubmsg.payloadlen =strlen(payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    
    if ((rc = MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to publish message, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for up to %d seconds for publication of %s\n"
           "on topic %s for client with ClientID: %s\n",
           (int)(TIMEOUT/1000), payload, TOPIC, CLIENTID);
    
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
}

int main(int argc, char* argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);

    opts.keepAliveInterval = 20;
    opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    // Simulate collecting sensor data
    char *sensor_data = "24.5";  // Example: Temperature data
    publishMessage(client, sensor_data);

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
