#ifndef HEAD_H
#define HEAD_H

#include "caesar_cipher.h"
#include "des_cipher.h"
#include "des_text_cipher.h"
#include "play_fair.h"
#include "rc4_cipher.h"
#include "rsa_cipher.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <sstream>
#include <chrono>

using namespace std;

size_t GetFileSize(const std::string& file_name) {
	std::ifstream in(file_name.c_str());
	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	in.close();
	return size; //µ¥Î»ÊÇ£ºbyte
}

#endif // HEAD_H
#pragma once
