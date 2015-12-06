#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"

#define CLIENTID    ""
#define QOS         1
#define TIMEOUT     10000L

int main(int argc, char* argv[])
{
  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  MQTTClient_message pubmsg = MQTTClient_message_initializer;
  MQTTClient_deliveryToken token;
  int rc, opt;
  char *topic;
  char *address;
  
  /* Parse arguments */
  if(argc != 11) {
    fprintf(stderr, "Too few arguments supplied\n");
    exit(EXIT_FAILURE);
  }

  while((opt = getopt(argc, argv, "t:h:u:p:m:")) != -1) {
    switch(opt) {
    case 't':
      topic = optarg;
      break;
    case 'h':         
      address = optarg;
      break;
    case 'u':
      conn_opts.username = optarg;
      break;
    case 'p':
      conn_opts.password = optarg;
      break;
    case 'm':
      pubmsg.payload = optarg;
      pubmsg.payloadlen = strlen(optarg);
      pubmsg.qos = QOS;
      pubmsg.retained = 0;
      break;
    default:
      fprintf(stderr, "Usage %s -t TOPIC -h ADDRESS -u USER -p PASSWORD -m PAYLOAD\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  MQTTClient_create(&client, address, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
  conn_opts.keepAliveInterval = 20;
  conn_opts.cleansession = 1;

  if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
      printf("Failed to connect, return code %d\n", rc);
      exit(-1);
    }

  MQTTClient_publishMessage(client, topic, &pubmsg, &token);
  printf("Waiting for up to %d seconds for publication of %s\n"
	 "on topic %s for client with ClientID: %s\n",
	 (int)(TIMEOUT/1000), pubmsg.payload, topic, CLIENTID);
  rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
  printf("Message with delivery token %d delivered\n", token);
  MQTTClient_disconnect(client, 10000);
  MQTTClient_destroy(&client);
  return rc;
}


