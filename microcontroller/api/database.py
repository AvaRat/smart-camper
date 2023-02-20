from typing import AsyncIterator
from aioredis import Redis


async def init_redis_pool() -> AsyncIterator[Redis]:
    session = Redis(host="192.168.0.186", port=6379, encoding="utf-8", decode_responses=True)
    try:
        yield session
    finally:
        await session.close()
