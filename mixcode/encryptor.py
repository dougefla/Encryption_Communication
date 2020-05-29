import json
import time
from Mixcode import Mixcode
# 输入信息
codetype = 'des_text_cipher'

plaintext = input('Input Message Only Support English:')
curtime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())

# 对明文加密
mixcode = Mixcode(plaintext=plaintext,password=123456,couple_range=3)
ciphertext = mixcode.encrypt()
# 获得json格式的密文报
encrptor_output = json.dumps({'code-type':codetype,'ciphertext':ciphertext,'time':curtime})
print("encrptor_output:\n",encrptor_output)
# 把密文报输入客户端-加密软件之间的中转文件
with open('input2.json','w+',encoding='utf-8') as f:
    json.dump(encrptor_output,f,ensure_ascii=False)
