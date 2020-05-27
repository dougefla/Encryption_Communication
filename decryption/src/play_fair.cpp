#include "play_fair.h"

play_fair::play_fair()
{

}

string play_fair::ewPlayfair(string plainText, string secret)
{
    clock_t time_start=clock();

    string plainStdText = plainText;
    string secretStdText = secret;

    normalizePFSecret(secretStdText);
    populatePFMatrix(secretStdText);
    normalizePFString(plainStdText);

    string encryptedText = encryptPFString(plainStdText);
    _plainText = plainText;
    _secret = secret;
    _encryptedText = encryptedText;

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _encryptedText;
}

string play_fair::dwPlayfair(string encryptedText, string secret)
{
    clock_t time_start=clock();

    string encryptedStdText = encryptedText;
    string secretStdText = secret;

    normalizePFSecret(secretStdText);
    populatePFMatrix(secretStdText);
    _encryptedText = encryptedText;
    _secret = secret;
    string plainText = decryptPFString(encryptedStdText);
    _plainText = plainText;

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _plainText;
}

bool play_fair::inSameRow(Position p1, Position p2)
{
    if(p1.x == p2.x)
        return true;
    return false;
}

bool play_fair::inSameColumn(Position p1, Position p2)
{
    if(p1.y == p2.y)
        return true;
    return false;
}

void play_fair::normalizePFString(string &str)
{
    string pure_str= "";
    // remove any non-alphabetical characters
    // convert string to lower case
    for(int i=0; i < str.size(); ++i)
    {
        if(isalpha(str[i]))
        {
            if(isupper(str[i]))
                str[i] = tolower(str[i]);
            pure_str += str[i];
        }
    }

    // separate duplicate characters
    for(int i=0; i < pure_str.size()-1; i+=2)
    {
        if(pure_str[i] == pure_str[i+1])
            pure_str.insert(pure_str.begin()+i+1, 'x');
    }

    // make string even
    if(pure_str.size()%2 !=0)
        pure_str += 'x';

    str = pure_str;
}

string play_fair::encryptPFString(string plainStdText)
{
    string result = "";

    for(int i=0; i < plainStdText.size(); i+=2)
    {
        Position p1 = findPositionByChar(plainStdText[i]);
        Position p2 = findPositionByChar(plainStdText[i+1]);

        if(inSameRow(p1, p2))
        {
            if(p1.y == 4)
                p1.y = 0;
            else
                p1.y +=1;

            if(p2.y == 4)
                p2.y = 0;
            else
                p2.y +=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else if(inSameColumn(p1, p2))
        {
            if(p1.x == 4)
                p1.x = 0;
            else
                p1.x +=1;

            if(p2.x == 4)
                p2.x = 0;
            else
                p2.x +=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else
        {
            Position t1, t2;

            t1.x = p1.x;
            t1.y = p2.y;

            t2.x = p2.x;
            t2.y = p1.y;

            result += findCharByPosition(t1);
            result += findCharByPosition(t2);
        }
    }

    return result;
}

string play_fair::decryptPFString(string encryptedStdText)
{
    string result = "";

    for(int i=0; i < encryptedStdText.size(); i+=2)
    {
        Position p1 = findPositionByChar(encryptedStdText[i]);
        Position p2 = findPositionByChar(encryptedStdText[i+1]);

        if(inSameRow(p1, p2))
        {
            if(p1.y == 0)
                p1.y = 4;
            else
                p1.y -=1;

            if(p2.y == 0)
                p2.y = 4;
            else
                p2.y -=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else if(inSameColumn(p1, p2))
        {
            if(p1.x == 0)
                p1.x = 4;
            else
                p1.x -=1;

            if(p2.x == 0)
                p2.x = 4;
            else
                p2.x -=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else
        {
            Position t1, t2;

            t1.x = p1.x;
            t1.y = p2.y;

            t2.x = p2.x;
            t2.y = p1.y;

            result += findCharByPosition(t1);
            result += findCharByPosition(t2);
        }
    }

    return result;
}

void play_fair::normalizePFSecret(string &secret)
{
    string result = "";
    secret += "abcdefghiklmnopqrstuvwxyz";
    for(int i=0; i < secret.size(); ++i)
    {
        if(result.find(secret[i]) == string::npos)
            result += secret[i];
    }
    secret = result;
}

void play_fair::populatePFMatrix(string secret)
{
    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5 ; ++j)
        {
            pfMatrix[i][j] = secret[j+5*i];
        }
    }
}

Position play_fair::findPositionByChar(char ch)
{
    Position p;

    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5; ++j)
        {
            if(pfMatrix[i][j] == ch)
            {
                p.x = i;
                p.y = j;
            }
        }
    }

    return p;
}

char play_fair::findCharByPosition(Position p)
{
    return pfMatrix[p.x][p.y];
}

string play_fair::get_secret()
{
    return _secret;
}

string play_fair::get_plainText()
{
    return _plainText;
}

string play_fair::get_encryptedText()
{
    return _encryptedText;
}
