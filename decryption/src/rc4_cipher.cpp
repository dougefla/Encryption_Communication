#include "rc4_cipher.h"

rc4_cipher::rc4_cipher()
{

}

string rc4_cipher::ewRC4(string msg, string key)
{
    clock_t time_start=clock();

    vector<int> k;

    // initialize key
    string stdCppKey = key;
    for(int i=0; i<stdCppKey.length(); ++i)
        k.push_back(int(stdCppKey[i] - '0'));

    vector<int> s(256);
    vector<int> t(256);

    // initialize vector S to [0:255]
    for(int i=0; i<256; ++i)
        s[i] = i;

    // initialize vector T from key K
    for(int i=0; i<256; ++i)
        t[i] = k[i%k.size()];

    // initial Permutation Of S
    int j = 0;
    for(int i=0; i<256; ++i)
    {
        j = (j + s[i] + t[i])%256;
        swap(s[i], s[j]);
    }

    // prepare msg
    vector< bitset<8> > msg_bytes = bytesOfMessage(msg);


    // generate a key for each byte of input
    // e.g input: 5 bytes, generates output: 5 bytes
    vector< bitset<8> > keys = keysGenerator((int)msg_bytes.size(), s);
    _key = key;
    _plainText = msg;
    _encryptedText = RC4Encryption(msg_bytes, keys);

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _encryptedText;

}

string rc4_cipher::dwRC4(string msg, string key)
{
    clock_t time_start=clock();

    _key = key;
    _encryptedText = msg;
    _plainText = ewRC4(msg, key);

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _plainText;
}

string rc4_cipher::RC4Encryption(vector< bitset<8> > msg_bytes, vector< bitset<8> > keys)
{
    string result = "";
    for (int i = 0; i < msg_bytes.size(); ++i)
    {
        bitset<8> temp = bitset<8>(msg_bytes[i] ^ keys[i]);
        result += temp.to_string();
    }

    // Debugging output
    cout << "> Debugging Statements" << endl;

    cout << "I/P: " ;
    for(int t=0; t<msg_bytes.size(); ++t)
        cout << msg_bytes[t];
    cout << endl;

    cout << "Key: ";
    for(int t=0; t<keys.size(); ++t)
        cout << keys[t].to_string();
    cout << endl;
    cout << "O/P: " << result << endl;

    return result;
}

vector< bitset<8> > rc4_cipher::keysGenerator(int msg_length, vector<int> s)
{
    vector< bitset<8> > keys(msg_length);

    int i=0, j=0, k=0;
    for (int lc = 0; lc < msg_length; ++lc)
    {
        i = (i+1)%256;
        j = (j+s[i])%256;
        swap(s[i], s[j]);
        k = s[(s[i]+s[j])%256];
        keys[lc] = bitset<8>(k);
    }

    return keys;
}

vector< bitset<8> > rc4_cipher::bytesOfMessage(string msg)
{
    vector< bitset<8> > msg_bytes;

    for(int i=0; i<(msg.length()/8); ++i)
    {
        string msg_byte = "";
        for(int j=0; j<8; ++j)
        {
            int idx = j + i*8;
            msg_byte += msg[idx];
        }
        msg_bytes.push_back(bitset<8>(msg_byte));
    }

    return msg_bytes;
}

string rc4_cipher::get_key()
{
    return _key;
}

string rc4_cipher::get_plainText()
{
    return _plainText;
}

string rc4_cipher::get_encryptedText()
{
    return _encryptedText;
}
