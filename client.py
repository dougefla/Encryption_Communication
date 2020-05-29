import requests
import json
import time
import os
cipher_list = ['caesar_cipher','des_cipher','des_text_cipher','play_fair','rc4_cipher','rsa_cipher','mix_cipher']
url = 'http://code.douge.net.cn/upload'
while 1:
    curtime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    print(curtime) # 用于检测程序是否在运行
    # 校验输入文件是否存在，若不存在就新建一个空白的
    if not os.path.exists('input.json'):
        with open("input.json",'w',encoding='utf-8') as f:
            print("Create New File: input.json")
    # 校验输入文件是否有内容，若有，则准备发送
    if not os.path.getsize('input.json') ==0:
        with open("input.json",'r+',encoding='utf-8') as f:
            content = json.load(f)
            # 校验密文输入报合法性
            try:
                codetype = content['code-type']
                ciphertext = content['ciphertext']
                if not codetype in cipher_list:
                    print("Invalid code-type:",code_type)
                    continue
            except:
                print('Invalid format!')
            # 准备发送密文上行报
            post_data = json.dumps({'code-type':codetype,'ciphertext':ciphertext,'time':curtime})
            print(post_data)
            req = requests.post(url,post_data)
            print("get_req:",req.text)
            f.seek(0)
            f.truncate()

    time.sleep(1)