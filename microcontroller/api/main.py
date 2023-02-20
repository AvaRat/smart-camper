from fastapi import FastAPI, Depends, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi_mqtt import FastMQTT, MQTTConfig
from database import init_redis_pool
from models import CamperState
from mock_state import MockState
import os

app = FastAPI()

mqtt_config = MQTTConfig(host="192.168.1.1", port=1883, keepalive=5)

mqtt = FastMQTT(
    config=mqtt_config
)

if(os.getenv('BROKER_OFF') == "false"):
    mqtt.init_app(app)


state = MockState()

origins = [
    "http://localhost.tiangolo.com",
    "https://localhost.tiangolo.com",
    "http://localhost",
    "http://localhost:8080",
    "http://127.0.0.1:8000"
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"]
)

#s = camper_state.json()
#with open('file.json', 'w') as f:
#    f.write(s)

@app.get("/")
async def root():
    return {"message": "Hello World"}


@app.get("/camper/state", response_model=CamperState)
async def get_state():
    return state.camper_state

@app.post("/camper/state")
async def set_state(_camper_state: CamperState):
    state.camper_state = _camper_state
    return {"message": "success"}



@mqtt.on_connect()
def connect(client, flags, rc, properties):
    mqtt.client.subscribe("ducato/clean_water_tank/temperature")
    #mqtt.client.subscribe("ducato/clean_water_tank/level")
    print("Connected: ", client, flags, rc, properties)


@mqtt.subscribe("ducato/clean_water_tank/temperature")
async def message_to_topic(client, topic, payload, qos, properties):
    state.camper_state.water_tank.temperature = payload.decode()
    #print("Received message to topic: ", topic, payload.decode(), qos, properties)


@mqtt.subscribe("ducato/clean_water_tank/level")
async def message_to_topic(client, topic, payload, qos, properties):
    state.camper_state.water_tank.level = payload.decode()
    #print("Received message to topic: ", topic, payload.decode(), qos, properties)


@mqtt.on_disconnect()
def disconnect(client, packet, exc=None):
    print("Disconnected")
