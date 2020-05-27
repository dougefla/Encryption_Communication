#include "rsa_cipher.h"

rsa_cipher::rsa_cipher()
{

}

double rsa_cipher::ewRSA(double msg, double p, double q)
{
    clock_t time_start=clock();

    // generate public as first, private as second key
    pair<double,double> keys = RSAKeys(p, q);

    double n = p*q;
    double e = keys.first;
    _p = p;
    _q = q;
    _plainText = msg;
    _encryptedText = RSAEncryption(msg, n, e);

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _encryptedText;
}

double rsa_cipher::dwRSA(double msg, double p, double q)
{
    clock_t time_start=clock();

    // generate public as first, private as second key
    pair<double,double> keys = RSAKeys(p, q);

    int n = p*q;
    int d = keys.second;
    _p = p;
    _q = q;
    _encryptedText = msg;
    _plainText = RSADecryption(msg, n, d);

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _plainText;
}

double rsa_cipher::RSAEncryption(double msg, double n, double e)
{
    // Encryption c = (msg ^ e) % n
    double c = pow(msg, e);
    c = fmod(c, n);
    return c;
}

double rsa_cipher::RSADecryption(double msg, double n, double d)
{
    // Decryption m = (c ^ d) % n
    double m = pow(msg, d);
    m = fmod(m, n);
    return m;
}

pair<double, double> rsa_cipher::RSAKeys(double p, double q)
{
    // Finding public key; e stands for encrypt.
    double e = 2;
    double phi = (p-1)*(q-1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }

    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient

    int d = e;
    while((int)(d*e)%((int)phi) != 1)
    {
        d++;
    }

    return make_pair(e, d);
}

int rsa_cipher::gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}

double rsa_cipher::get_plainText()
{
    return get_plainText();
}

double rsa_cipher::get_encryptedText()
{
    return _encryptedText;
}

double rsa_cipher::get_p()
{
    return _p;
}

double rsa_cipher::get_q()
{
    return _q;
}
