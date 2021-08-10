import requests
url = 'http://192.168.0.14:1880/snapshot'
#payload = open("request.json")
headers = {'content-type': 'application/json', 'Accept-Charset': 'UTF-8'}
data = '{"text":"Took Photo, move Slider!"}'
r = requests.post(url, data=data, headers=headers)
print(r)