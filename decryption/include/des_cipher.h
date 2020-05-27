#ifndef DES_CIPHER_H
#define DES_CIPHER_H

#include <string>
#include <cstring>
#include <cctype>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

//Des Cipher
// data 0000000100100011010001010110011110001001101010111100110111101111
// key  0001001100110100010101110111100110011011101111001101111111110001

class des_cipher
{
private:
    string _plainText, _encryptedText;//store plain texts and encrypted texts
    string _key;//store the encryption key
    double time_ms;//time used for executing in ms
public:
    des_cipher();
    string ewDES(string plainText, string key);//encrypt
    string dwDES(string encryptedText, string key);//decrypt
    vector<string> keyPreparation(string key);
    string DESEncryption(string dataBlock, vector< string > keys);
    string apply_xor(string str1, string str2);
    string apply_func_F(string str1, string str2);
    string apply_func_E(string str);
    string get_key();
    string get_plainText();
    string get_encryptedText();
    double get_time(){
        return time_ms;
    }
};

#endif // DES_CIPHER_H
