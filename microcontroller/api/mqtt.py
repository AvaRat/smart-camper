from yaml import load, dump, Loader
from pydantic import BaseSettings


class Settings(BaseSettings):
    gas_on: str
    lights_on: str
    water_on: str 


class TopicMapper():
    pass


topics = Settings(_env_file='topics.env', _env_file_encoding='utf-8')
tm = TopicMapper()
print(topics)
