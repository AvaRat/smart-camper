import redis
r = redis.Redis(host='192.168.0.186', port=6379, db=0)

r.set('vdfrsv', 'bar')
