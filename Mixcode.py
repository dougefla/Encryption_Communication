import math
import numpy
import random

class Mixcode(object):
    def __init__(self,password,plaintext='',ciphertext='',couple_range=3):
        self.plaintext = plaintext          # 原文
        self.ciphertext = ciphertext        # 密文
        self.password = password            # 密码
        self.couple_range = couple_range    # 耦合范围
    
    # 随机逐字符打乱原文，保存打乱顺序
    def shuffle(self,input_string):
        while not len(input_string)%self.couple_range==0:
            input_string+=' '
        index_list = [x for x in input_string]
        random.seed(hash(self.password))
        random.shuffle(index_list)  # 对内容进行打乱
        shuffled_text = ''.join(index_list)
        return shuffled_text

    # 根据打乱顺序和乱文获得原文
    def deshuffle(self,shuffled_text):
        index = [i for i in range(0,len(self.ciphertext))] 
        random.seed(hash(self.password))
        random.shuffle(index) # 与加密过程使用相同种子，获得打乱顺序
        deshuffle_text = [0 for i in range(len(self.ciphertext))]
        for i in range(len(self.ciphertext)):
            deshuffle_text[index[i]]=shuffled_text[i]
        deshuffle_text = ''.join(deshuffle_text)
        return deshuffle_text.strip()
    
    # 计算加密矩阵，用于字符替代    
    def get_matrix(self):
        numpy.random.seed(hash(self.password))
        while 1:
            matrix = numpy.random.randint(1,4,(self.couple_range,self.couple_range))
            if numpy.linalg.det(matrix) == 0:
                continue
            else:
                break
        return matrix
    # 切割字符串成等长字符串列表，如果不能整切，就在末尾补空格' '
    def cut_string(self, obj, sec):
        while not len(obj)%sec==0:
            obj+=' '
        return [obj[i:i+sec] for i in range(0,len(obj),sec)]
    
    # 替代字符
    def replace(self,input_string):
        matrix = self.get_matrix()
        content_list = self.cut_string(input_string,self.couple_range) # ['123','456','789']
        replaced_text = ''
        for content_unit in content_list:
            x_mat = numpy.mat(numpy.zeros((self.couple_range,1)),int)
            for i in range(self.couple_range):
                x = ord(content_unit[i])
                x_mat[i,0] = x
            new_mat = matrix*x_mat # B = A*a
            for x in new_mat[:,0]:
                replaced_text+=chr(x)
        return replaced_text # ['abc','def','ghi']

    # 把替代字符还原为原字符
    def deplace(self,input_string):
        matrix = self.get_matrix()
        content_list = self.cut_string(input_string,self.couple_range) # ['abc','def','ghi']
        deplace_text = ''
        for content_unit in content_list: # 'abc'
            x_mat = numpy.mat(numpy.zeros((self.couple_range,1)),int) # [[0];[0];[0]]
            for i in range(self.couple_range):
                x = ord(content_unit[i]) # x=ord('a')
                x_mat[i,0] = x # x_mat = [[ord('a')];[ord('b')];[ord('c')]]
            new_mat = numpy.linalg.inv(matrix)*x_mat # a = A^-1*B
            for x in new_mat[:,0]:
                deplace_text+=chr(x)
        return deplace_text

    def encrypt(self):
        shuffled_text = self.shuffle(self.plaintext)
        replaced_text = self.replace(shuffled_text)
        self.ciphertext = replaced_text
        return replaced_text
    
    def decrypt(self):
        # 先把字符转回来
        deplace_text = self.deplace(self.ciphertext)
        self.plaintext = self.deshuffle(deplace_text)
        return self.plaintext