#define _CRT_SECURE_NO_WARNINGS
#include "head.h"

using json = nlohmann::json;

#define ciphertext_file "./ciphertext.json"
#define result_file "./result.json"

int main(int argc, char **argv) {
	while (true)
	{
		ifstream in(ciphertext_file);
		if (!in.is_open())
		{
			cout << "Error opening file";
			exit(1);
		}
		else {
			cout << "Open!\n";
		}
		if (GetFileSize(ciphertext_file) == 0)
		{
			cout << "nothing in file!\n";
			in.close();
		} else {
			json j;
			in >> j;
			in.close();
			string ciphertext, code_type, plaintext;
			ciphertext = j["ciphertext"].get<string>();
			code_type = j["code-type"].get<string>();
			ofstream fileout(ciphertext_file, ios::trunc);
			if (!fileout) {
				cout << "Create file failure...\n";
				exit(0);
			}
			fileout.close();
			// cout << ciphertext << endl;
			// cout << code_type << endl;
			// break;
			if (code_type == "caesar_cipher") { 
				caesar_cipher cae;
				plaintext = cae.dwCaesarCipher(ciphertext, 5);
			}
			if (code_type == "des_cipher") { 
				des_cipher des;
				plaintext = des.dwDES(ciphertext, "0001001100110100010101110111100110011011101111001101111111110001");
			}
			if (code_type == "des_text_cipher") { 
				des_text_cipher des_text;
				plaintext = des_text.dwDES(ciphertext, "0001001100110100010101110111100110011011101111001101111111110001");
			}
			if (code_type == "play_fair") { 
				play_fair pf;
				plaintext = pf.dwPlayfair(ciphertext, "harpsichord");
			}
			if (code_type == "rc4_cipher") { 
				rc4_cipher rc4;
				plaintext = rc4.dwRC4(ciphertext, "securitycomputersystem");
			}
			if (code_type == "rsa_cipher") { 
				rsa_cipher rsa;
				istringstream is(ciphertext);
				double pt, ct;
				is >> ct;
				pt = rsa.dwRSA(ct, 3, 11);
				ostringstream os;
				os << pt;
				plaintext = os.str();
			}
			json jo;
			jo["code-type"] = code_type;
			jo["plaintext"] = plaintext;
			auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
			stringstream ss;
			ss << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S");
			string str_time = ss.str();
			jo["time"] = str_time;
			ofstream o(result_file);
			o << jo << endl;
		}
	}
}