#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
class JoinFile
{
public: void join(std::string inputUrl, unsigned char  aes_key_basic[], std::string outputUrl) {

	unsigned char iv[AES_BLOCK_SIZE];
	memset(iv, 0x00, AES_BLOCK_SIZE);
	std::ofstream ofs(outputUrl, std::ios::binary | std::ios::trunc);
	//std::ofstream output_file("decout.txt", std::ios::binary | std::ios::ate);
	//std::ostream_iterator<char> output_iterator(output_file);
	AES_KEY dec_key;
	int i = 0;
	while (1) {
		i++;
		std::string fileName = inputUrl + "chunk" + std::to_string(i) + ".txt";
		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		size_t sizeOfFile = file.tellg();
		if (sizeOfFile > 0) {
			std::streamsize size = file.tellg();
			file.seekg(0, std::ios::beg);
			unsigned char* dec_out = (unsigned char*)malloc(sizeOfFile + 1);

			std::vector<char> buffer(size);
			memset(dec_out, 0x00, sizeOfFile + 1);
			file.read(buffer.data(), size);
			file.close();
			unsigned char* aes_input = (unsigned char*)malloc(sizeOfFile + 1);
			std::copy(buffer.begin(), buffer.end(), aes_input);
			memset(iv, 0x00, AES_BLOCK_SIZE); // don't forget to set iv vector again, else you can't decrypt data properly
			AES_set_decrypt_key(aes_key_basic, 32 * 8, &dec_key); // Size of key is in bits
			AES_cbc_encrypt(aes_input, dec_out, sizeOfFile, &dec_key, iv, AES_DECRYPT);
			ofs.write((char *)dec_out, sizeOfFile);
		}
		else {
			return;
		}
	}
}

};

