#ifndef CAESA_CIPHER_H
#define CAESA_CIPHER_H

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

//Caesar Cipher

class caesar_cipher
{
private:
    string _plainText, _encryptedText;//store plain texts and encrypted texts
    int _key;//store the encryption key
    double time_ms;//time used for executing in ms
public:
    caesar_cipher();
    string ewCaesarCipher(string plainText, int key);//encrypt
    string dwCaesarCipher(string encryptedText, int key);//decrypt
    int get_key();
    string get_plainText();
    string get_encryptedText();
    double get_time(){
        return time_ms;
    }
};

#endif // CAESA_CIPHER_H
