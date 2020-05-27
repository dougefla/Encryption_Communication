#ifndef RSA_CIPHER_H
#define RSA_CIPHER_H

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

class rsa_cipher
{
private:
    double _plainText, _encryptedText;//store plain texts and encrypted texts
    double _p, _q;//store the keys
    double time_ms;//time used for executing in ms
public:
    rsa_cipher();
    double ewRSA(double msg, double p, double q);//encrypt
    double dwRSA(double msg, double p, double q);//decrypt
    double RSAEncryption(double msg, double n, double e);
    double RSADecryption(double msg, double n, double d);
    pair<double, double> RSAKeys(double p, double q);
    int gcd(int a, int h);
    double get_plainText();
    double get_encryptedText();
    double get_p();
    double get_q();
    double get_time(){
        return time_ms;
    }
};

#endif // RSA_CIPHER_H
