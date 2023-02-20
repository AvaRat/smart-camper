import asyncio
from pydantic import BaseModel
import aioredis

host='192.168.0.186'
port=6379
db=0

class Sensor(BaseModel):
    temp: float
    level: float


class Car(BaseModel):
    front: Sensor
    back: Sensor

async def main():
    redis = aioredis.from_url(f"redis://{host}")
    s1 = Sensor(temp=19, level=0.2)
    s2 = Sensor(temp=45, level=0.87)
    car = Car(front=s1, back=s2)

    await redis.set("camper/water_tank", car.json())

    str_value = await redis.get("camper/water_tank")
    rec_obj = Car.parse_raw(str_value)
    print(rec_obj.json())


if __name__ == "__main__":
    asyncio.run(main())