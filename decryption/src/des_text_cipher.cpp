#include "des_text_cipher.h"

des_text_cipher::des_text_cipher()
{

}

string des_text_cipher::ewIDES(string plainText, string key)
{
    clock_t time_start=clock();

    vector< string > keys = keyPreparation(key);
    vector< string > blocks = textToBinaryAscii(plainText);

    string encryptedText;

    for(int i=0; i < blocks.size(); ++i)
        encryptedText += DESEncryption(blocks[i], keys);

//    encryptedText = string::fromStdString(binaryAsciiToText(encryptedText.toStdString()));
    _encryptedText = encryptedText;
    _key = key;
    _plainText = plainText;

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _encryptedText;
}

string des_text_cipher::dwIDES(string encryptedText, string key)
{
    clock_t time_start=clock();

    vector< string > keys = keyPreparation(key);
    reverse(keys.begin(), keys.end());

    string stdPlainText = encryptedText;
    string allPlainText = "";

    for(int i=0; i<encryptedText.size()/64; ++i)
    {
        allPlainText += DESEncryption(stdPlainText.substr(i*64, 64), keys);
    }
    _encryptedText = encryptedText;
    _key = key;
    _plainText = binaryAsciiToText(allPlainText);

    clock_t time_end=clock();
    time_ms = 1000*(time_end-time_start)/(double)CLOCKS_PER_SEC;

    return _plainText;
}

vector< string > des_text_cipher::textToBinaryAscii(string str)
{
    vector< string > blocksOfData;

    for(int i=0; i<str.size()/8; ++i)
    {
        string blockStr = str.substr(i*8, 8);
        string block = "";

        for(int i=0; i<8; ++i)
            block += charToBinaryAscii(blockStr[i]);

        blocksOfData.push_back(block);
    }

    if(str.size()%8 != 0)
    {
        int start = ((int)str.size()/8)*8;
        int length = (int)str.size()- start;

        string blockStr = str.substr(start, length);
        for(int i=0; i<(8-length); ++i)
            blockStr += " ";

        string block = "";
        for(int i=0; i<8; ++i)
            block += charToBinaryAscii(blockStr[i]);
        blocksOfData.push_back(block);
    }

    return blocksOfData;
}

string des_text_cipher::binaryAsciiToText(string str)
{
    string blocksOfData = "";

    for(int i=0; i<str.size()/64; ++i)
    {
        string blockStr = str.substr(i*64, 64);
        string block = "";

        for(int i=0; i<8; ++i)
        {
           string ascii = blockStr.substr(i*8, 8);
           block += binaryAsciiToChar(ascii);
        }
        blocksOfData += block;
    }

    return blocksOfData;
}

string des_text_cipher::charToBinaryAscii(char ch)
{
    return bitset<8>(int(ch)).to_string();
}

char des_text_cipher::binaryAsciiToChar(string binaryAscii)
{
    return char(bitset<8>(binaryAscii).to_ulong());
}

string des_text_cipher::get_key()
{
    return _key;
}

string des_text_cipher::get_plainText()
{
    return _plainText;
}

string des_text_cipher::get_encryptedText()
{
    return _encryptedText;
}
