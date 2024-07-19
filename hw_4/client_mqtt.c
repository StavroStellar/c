#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"
#include <time.h>
#include <unistd.h>

//~ #define ADDRESS     "tcp://localhost:1883"
//#define ADDRESS     "mqtt.eclipseprojects.io:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "/node-red/temp"
//#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L
#define PAYLOAD_SIZE 10

int main(int argc, char* argv[])
{
	
	if (argc != 4) {
        printf("Usage: %s <IP:port> <login> <password>\n", argv[0]);
        return 1;
    }
	char *ip = argv[1];
    char *login = argv[2];
    char *password = argv[3];

	
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ip, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = login;
    conn_opts.password = password;
	char PAYLOAD[PAYLOAD_SIZE];
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    while(1) {
        int random_value = rand() % 36 + 10;
        sprintf(PAYLOAD, "%d", random_value);

        pubmsg.payload = PAYLOAD;
        pubmsg.payloadlen = strlen(PAYLOAD);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;

        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("Waiting for up to %d seconds for publication of %s\n"
                "on topic %s for client with ClientID: %s\n",
                (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
        rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        printf("Message with delivery token %d delivered\n", token);

        sleep(7); 
    }

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return rc;
}
