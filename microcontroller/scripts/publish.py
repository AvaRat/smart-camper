import argparse

import paho.mqtt.client as mqtt

parser = argparse.ArgumentParser()
   
parser.add_argument('topic')

parser.add_argument('message')

args = parser.parse_args()

client =mqtt.Client("jupyter-client")
client.connect("192.168.1.1", port=1883)

res = client.publish(args.topic, args.message)
