#ifndef RC4_CIPHER_H
#define RC4_CIPHER_H

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

class rc4_cipher
{
private:
    string _plainText, _encryptedText;//store plain texts and encrypted texts
    string _key;//store the encryption key
    double time_ms;//time used for executing in ms
public:
    rc4_cipher();
    string ewRC4(string msg, string key);//encrypt
    string dwRC4(string msg, string key);//decrypt
    string RC4Encryption(vector< bitset<8> > msg_bytes, vector< bitset<8> > keys);
    vector< bitset<8> > keysGenerator(int msg_length, vector<int> s);
    vector< bitset<8> > bytesOfMessage(string msg);
    string get_key();
    string get_plainText();
    string get_encryptedText();
    double get_time(){
        return time_ms;
    }
};

#endif // RC4_CIPHER_H
