#include "caesar_cipher.h"

caesar_cipher::caesar_cipher()
{

}
string caesar_cipher::ewCaesarCipher(string plainText, int key)
{
    clock_t time_start=clock();

    string result = "";

    for (int i = 0; i < plainText.length(); i++)
    {
        if(plainText[i] == ' ')
        {
            result += ' ';
        }
        else if(isalpha(plainText[i]))
        {
            if (isupper(plainText[i]))
                result += char(int(plainText[i]+key-65)%26 +65);
            else
                result += char(int(plainText[i]+key-97)%26 +97);
        }
    }
    _plainText = plainText;
    _key = key;
    _encryptedText = result;

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _encryptedText;
}

string caesar_cipher::dwCaesarCipher(string encryptedText, int key)
{
    clock_t time_start=clock();

    _encryptedText = encryptedText;
    _key = key;
    _plainText = ewCaesarCipher(encryptedText, 26-key);

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _plainText;
}

int caesar_cipher::get_key()
{
    return _key;
}

string caesar_cipher::get_plainText()
{
    return _plainText;
}

string caesar_cipher::get_encryptedText()
{
    return _encryptedText;
}
