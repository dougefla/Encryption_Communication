	# -*- coding: utf-8 -*-
import os
from flask import Flask, request, url_for, send_from_directory,send_file
from werkzeug.utils import secure_filename
import json
import time
import logging
from logging.handlers import RotatingFileHandler

#日至等级的设置
logging.basicConfig(level=logging.DEBUG)
#创建日志记录器，指明日志保存路径,每个日志的大小，保存日志的上限
file_log_handler = RotatingFileHandler('/var/www/code_server/flasklog.txt',maxBytes=1024*1024,backupCount=10)
#设置日志的格式           日志等级     日志信息文件名   行数        日志信息
formatter=logging.Formatter('%(levelname)s %(filename)s %(lineno)d %(message)s')
#将日志记录器指定日志的格式
file_log_handler.setFormatter(formatter)
#为全局的日志工具对象添加日志记录器
logging.getLogger().addHandler(file_log_handler)

html = '''
    <!DOCTYPE html>
    <html>
    <head> 
        <style> 
        body{text-align:center} 
        </style> 
        </head> 
<meta HTTP-EQUIV="pragma" CONTENT="no-cache"> 
<meta HTTP-EQUIV="Cache-Control" CONTENT="no-store, must-revalidate"> 
<meta HTTP-EQUIV="expires" CONTENT="Wed, 26 Feb 1997 08:21:57 GMT"> 
<meta HTTP-EQUIV="expires" CONTENT="0">
<Meta http-equiv="Set-Cookie" Content="cookievalue=xxx; expires=Wednesday,21-Oct-98 16:14:21 GMT; path=/">

    <body>
    <title>Encryption Communication</title>
    <h1>Encryption Communication</h1>
    <h2>Plaintext</h2>
    <br>
        <h3>By @Douge, ZJU</h3>
    </br>

    '''
app = Flask(__name__)
result_json = '/var/www/code_server/decryption/result.json'
ciphertext_json = '/var/www/code_server/decryption/ciphertext.json'
show_file = '/var/www/code_server/show'

@app.route('/upload', methods=['POST'])
def server():

    logging.debug('Server run!')
    now = time.strftime("%Y-%m-%d-%H_%M_%S", time.localtime())
    logging.debug(now)
    # 只接受POST类型的请求
    if request.method == 'POST':
        logging.debug('POST!')
        logging.debug(request.data)

        content = eval(request.data)
        logging.debug(content)
        logging.debug(type(content))
        # 校验密文上行报合法性
        try:
            ciphertext = content['ciphertext']
        except:
            logging.debug('Format Wrong!')
            logging.debug("Received:")
            logging.debug(request.data)
            s = ''
            return s
        # 写入密文存储报
        with open(ciphertext_json,'w+',encoding='utf-8') as f:
            logging.debug('Open ciphertext.json')
            json.dump(content,f,ensure_ascii=False)
        # 等待解密程序处理
        time.sleep(1)
        while 1:

            logging.debug("Waiting for Decode")
            # 检验result文件是否存在，不存在就新建一个
            if not os.path.exists(result_json):
                logging.debug('result not exist, create!')
                with open(result_json,'w',encoding='utf-8') as f:
                    print("Create File: result_json")
            # 检验是否非空，如果非空就读入
            if not os.path.getsize(result_json) ==0:
                logging.debug('result not empty, read!')
                with open(result_json,'r+',encoding='utf-8') as f:
                    logging.debug('load plaintext!')
                    content = json.load(f)
                    with open(show_file,'w+',encoding='utf-8') as f2:
                        logging.debug('write in show!:')
                        logging.debug(content.get('plaintext'))
                        f2.write(content['plaintext'])
                    f.seek(0)
                    f.truncate()
                    logging.debug("Done!")
                return html+content['plaintext']
            time.sleep(1)
    return html + '</body></html>'

@app.route('/', methods=['GET'])
def index():
    app.logger.info('index run!')
    if not os.path.exists(show_file):
        with open(show_file,'w',encoding='utf-8') as f:
            i=1
    with open(show_file,'r',encoding='utf-8') as f:
        if os.path.getsize(show_file) ==0:
            plaintext = ''
        else:
            plaintext = f.readline()
    return html+'<br>'+plaintext+'</br>' + '</body></html>'

if __name__ == '__main__':
    app.run()
