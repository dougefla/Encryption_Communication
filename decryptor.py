import requests
import json
import time
import os
from Mixcode import Mixcode

while 1:
    curtime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    if not os.path.exists('ciphertext.json'):
        with open("ciphertext.json",'w',encoding='utf-8') as f:
            i=1
    with open("ciphertext.json",'r+',encoding='utf-8') as f:
        print("Open!")
        if not os.path.getsize('ciphertext.json') ==0:
            print("ciphertext not empty!")
            content = json.load(f)
            mixcode = Mixcode(ciphertext = content.get('ciphertext'),password =123456,couple_range = 3)
            plaintext = mixcode.decrypt()
            decrptor_output = json.dumps({'code-type':content.get('code-type'),'plaintext':plaintext,'time':curtime})
            with open("plaintext.json",'w+',encoding='utf-8') as f2:
                json.dump(content,f2,ensure_ascii=False)
                print("Write Into plaintext:",plaintext)
            f.seek(0)
            f.truncate()
    time.sleep(1)
    print(time.time())