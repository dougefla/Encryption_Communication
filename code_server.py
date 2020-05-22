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
    </body>
    </html>

    '''
app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def server():
    logging.debug('Server run!')
    now = time.strftime("%Y-%m-%d-%H_%M_%S", time.localtime())
    logging.debug(now)
    if request.method == 'POST':
        logging.debug('POST!')
        content = eval(request.data)
        try:
            ciphertext = content['ciphertext']
        except:
            logging.debug('Format Wrong!')
            logging.debug("Received:")
            logging.debug(request.data)
            s = ''
            return s
        with open('/var/www/code_server/ciphertext.json','w+',encoding='utf-8') as f:
            logging.debug('open ciphertext!!')
            json.dump(content,f,ensure_ascii=False)
        # 等待解密程序处理
        time.sleep(1)
        while 1:
            logging.debug("Waiting for Decode")
            if not os.path.exists('/var/www/code_server/plaintext.json'):
                logging.debug('plaintext not exist, create!')
                with open("/var/www/code_server/plaintext.json",'w',encoding='utf-8') as f:
                    i=1
            if not os.path.getsize('/var/www/code_server/plaintext.json') ==0:
                logging.debug('plaintext not empty, read!')
                with open('/var/www/code_server/plaintext.json','r+',encoding='utf-8') as f:
                    logging.debug('load plaintext!')
                    content = eval(json.load(f))
                    with open('/var/www/code_server/result.json','w+',encoding='utf-8') as f2:
                        logging.debug('write in result!:')
                        logging.debug(content.get('plaintext'))
                        f2.write(content['plaintext'])
                    f.seek(0)
                    f.truncate()
                    logging.debug("Done!")
                return html+content.get('plaintext')
            time.sleep(1)
    return html

@app.route('/', methods=['GET'])
def index():
    app.logger.info('index run!')
    if not os.path.exists('result.json'):
        with open("/var/www/code_server/result.json",'w',encoding='utf-8') as f:
            i=1
    with open('/var/www/code_server/result.json','a',encoding='utf-8') as f:
        f.seek(0,0)
        if os.path.getsize('/var/www/code_server/result.json') ==0:
            plaintext = ''
        else:
            plaintext = f.readline()
    return html+'<br>'+plaintext+'</br>'

if __name__ == '__main__':
    app.run()
