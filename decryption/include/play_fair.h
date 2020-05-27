#ifndef PLAY_FAIR_H
#define PLAY_FAIR_H


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

struct Position {
    int x;
    int y;
};

class play_fair
{
private:
    string _plainText, _encryptedText;//store plain texts and encrypted texts
    string _secret;//store the encryption secret
    double time_ms;//time used for executing in ms
public:
    play_fair();
    string ewPlayfair(string plainText, string secret);//encrypt
    string dwPlayfair(string encryptedText, string secret);//decrypt
    char pfMatrix[5][5];
    bool inSameRow(Position p1, Position p2);
    bool inSameColumn(Position p1, Position p2);
    void normalizePFString(string &str);
    void normalizePFSecret(string &secret);
    void populatePFMatrix(string secret);
    string encryptPFString(string plainStdText);
    string decryptPFString(string encryptedStdText);
    Position findPositionByChar(char ch);
    char findCharByPosition(Position p);
    string get_secret();
    string get_plainText();
    string get_encryptedText();
    double get_time(){
        return time_ms;
    }
};

#endif // PLAY_FAIR_H
