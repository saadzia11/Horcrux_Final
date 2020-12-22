#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
const static unsigned char  aes_key_basic[] = { 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF };
class CreateSplitFile
{
public: std::string originalFilePath = "";

	  const int size1MB = 1024;
	  int remBytes = 0;

public: void Split(int nMegaBytesPerChunk, std::string path, std::string outputPath) {
	originalFilePath = path;

	std::ifstream file;
	file.open(originalFilePath, std::ios::in);
	//std::ifstream inputFileStream(originalFilePath, std::ios::binary);
	std::vector<std::string> fileNamesVector;
	SplitFile(file, nMegaBytesPerChunk, fileNamesVector, outputPath);
}

	  unsigned char* SplitFile(std::istream& inStream, int nMegaBytesPerChunk, std::vector<std::string>& vecFilenames, std::string outputPath) {

		  unsigned char key[32];
		  GenerateKey(key);
		  std::ifstream file(originalFilePath, std::ios::binary | std::ios::ate);
		  size_t sizeOfFile = file.tellg();
		  int chunkSize = nMegaBytesPerChunk * size1MB;
		  int  iter = ceil(sizeOfFile / chunkSize);
		  if (remBytes == 0) {
			  remBytes = sizeOfFile;
		  }

		  std::unique_ptr<char[]> buffer(new char[chunkSize]);
		  unsigned char* buffer2 = (unsigned char*)malloc(chunkSize);
		  int nCurrentMegaBytes = 0;
		  int i = 0;
		  unsigned char* aes_input = (unsigned char*)malloc(chunkSize);
		  std::unique_ptr<std::ostream> pOutStream = createChunkFile(vecFilenames, outputPath);

		  while (!inStream.eof())
		  {
			  if (remBytes == 0)
			  {
				  return 0;
			  }
			  if (remBytes < chunkSize) {
				  chunkSize = remBytes;
				  remBytes = 0;
			  }
			  else {
				  remBytes = remBytes - chunkSize;
			  }
			  inStream.read(buffer.get(), chunkSize);

			  /* Init vector */
			  unsigned char iv[AES_BLOCK_SIZE];
			  memset(iv, 0x00, AES_BLOCK_SIZE);
			  /* Buffers for Encryption and Decryption */
			  unsigned char* enc_out = (unsigned char*)malloc(chunkSize);


			  /* AES-128 bit CBC Encryption */
			  AES_KEY enc_key;
			  memcpy(buffer2, buffer.get(), chunkSize);
			  AES_set_encrypt_key(key, sizeof(key) * 8, &enc_key);
			  AES_cbc_encrypt((unsigned char*)buffer2, enc_out, chunkSize, &enc_key, iv, AES_ENCRYPT);
			  pOutStream->write((char*)enc_out, chunkSize);
			  pOutStream = createChunkFile(vecFilenames, outputPath);
		  }
		  
		  printf("Encryption Key: \n");
		  for (int i = 0; i < 32; i++)
		  {
			  if (key[i] == '\0')
			  {
				  std::cout << "00";
			  }
			  else
			  {
				  std::cout << std::hex << (int)key[i];
			  }
		  }
		  std::cout << "\n";
		  //std::cout << std::hex << key;
		  return key;
	  }

	  std::unique_ptr<std::ofstream> createChunkFile(std::vector<std::string>& vecFilenames, std::string outputPath) {
		  std::stringstream filename;
		  filename << outputPath << "chunk" << (vecFilenames.size() + 1) << ".txt";
		  vecFilenames.push_back(filename.str());
		  return std::make_unique<std::ofstream>(filename.str(), std::ios::trunc | std::ios::binary);
	  }


	  void GenerateKey(unsigned char Key[]) {
		  int length = 32;
		  int i = 0;
		  for (i; i < length; i++)
		  {
			  Key[i] = aes_key_basic[rand() % 16];
		  }
		  return;
	  }
};

