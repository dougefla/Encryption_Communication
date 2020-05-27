#ifndef DES_TEXT_CIPHER_H
#define DES_TEXT_CIPHER_H

#include <string>
#include <cstring>
#include <cctype>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "des_cipher.h"
#include <ctime>
#include <vector>

using namespace std;
//DES Cipher with Text

class des_text_cipher : public des_cipher
{
private:
    string _plainText, _encryptedText;//store plain texts and encrypted texts
    string _key;//store the encryption key
    double time_ms;//time used for executing in ms
public:
    des_text_cipher();
    string ewIDES(string plainText, string key);//encrypt
    string dwIDES(string encryptedText, string key);//decrypt
    vector< string > textToBinaryAscii(string str);
    string binaryAsciiToText(string str);
    string charToBinaryAscii(char ch);
    char binaryAsciiToChar(string binaryAscii);
    string get_key();
    string get_plainText();
    string get_encryptedText();
    double get_time(){
        return time_ms;
    }
};

#endif // DES_TEXT_CIPHER_H
