import argparse
import paho.mqtt.client as mqtt
import time
############
def on_message(client, userdata, message):
    print("message received " ,str(message.payload.decode("utf-8")))
    print("message topic=",message.topic)
    print("message qos=",message.qos)
    print("message retain flag=",message.retain)


parser = argparse.ArgumentParser()
   
#parser.add_argument('topic')
parser.add_argument('--duration')

args = parser.parse_args()

topic = 'ducato/state'

client =mqtt.Client("terminal-listener")
client.on_message=on_message
client.connect("192.168.1.1", port=1883)
client.loop_start() #start the loop
print("Subscribing to topic", topic)
client.subscribe(topic)
time.sleep(int(args.duration))
client.loop_stop()