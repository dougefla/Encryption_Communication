import requests
import json
import time
import os

url = 'http://code.douge.net.cn/upload'
while 1:
    print(time.time()) # 检测程序是否在运行
    if not os.path.exists('input.json'):
        with open("input.json",'w',encoding='utf-8') as f:
            i=1
    if not os.path.getsize('input.json') ==0:
        with open("input.json",'r+',encoding='utf-8') as f:
            content = json.load(f)
            print(content)
            req = requests.post(url,content)
            print("get_req:",req.text)
            f.seek(0)
            f.truncate()

    time.sleep(1)