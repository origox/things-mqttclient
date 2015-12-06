# things-mqttclient

A publish only mqtt client

## Prerequisite

The Paho MQTT C Client need to be build and installed.

**Build**
- git clone http://git.eclipse.org/gitroot/paho/org.eclipse.paho.mqtt.c.git
- cd org.eclipse.paho.mqtt.c.git
- make

**Install**
- sudo make install


## Getting Started
- git clone https://github.com/origox/things-mqttclient.git
- cd things-mqttclient; make clean; make all
- ./mqttpub -t TOPIC -h tcp://localhost:1883 -u USER -p PASSWORD -m PAYLOAD
