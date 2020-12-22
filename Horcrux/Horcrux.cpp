// Horcrux.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CreateFile.h"
#include "CreateSplitFile.h"
#include "JoinFile.h"

void convertCharToHex(unsigned char key1[], unsigned char key2[])
{
	int i = 0, j = 0;
	for (i; i < 64; i = i + 2)
	{
		if (key1[i] == '0')
		{
			key2[j] = 0x00;
			j++;
		}
		if (key1[i] == '1')
		{
			key2[j] = 0x11;
			j++;
		}
		else if (key1[i] == '2')
		{
			key2[j] = 0x22;
			j++;
		}
		else if (key1[i] == '3')
		{
			key2[j] = 0x33;
			j++;
		}
		else if (key1[i] == '4')
		{
			key2[j] = 0x44;
			j++;
		}
		else if (key1[i] == '5')
		{
			key2[j] = 0x55;
			j++;
		}
		else if (key1[i] == '6')
		{
			key2[j] = 0x66;
			j++;
		}
		else if (key1[i] == '7')
		{
			key2[j] = 0x77;
			j++;
		}
		else if (key1[i] == '8')
		{
			key2[j] = 0x88;
			j++;
		}
		else if (key1[i] == '9')
		{
			key2[j] = 0x99;
			j++;
		}
		else if (key1[i] == 'a')
		{
			key2[j] = 0xaa;
			j++;
		}
		else if (key1[i] == 'b')
		{
			key2[j] = 0xbb;
			j++;
		}
		else if (key1[i] == 'c')
		{
			key2[j] = 0xcc;
			j++;
		}
		else if (key1[i] == 'd')
		{
			key2[j] = 0xdd;
			j++;
		}
		else if (key1[i] == 'e')
		{
			key2[j] = 0xee;
			j++;
		}
		else if (key1[i] == 'f')
		{
			key2[j] = 0xff;
			j++;
		}
	}
}
int main()
{
	std::string inputString = "";
	std::string inputFilePath = "";
	std::string outputFilePath = "";
	std::string consoleResponse = "";
	int outputFileSize = 0; 
	while (1)
	{
		std::cout << "Enter the action you want to perform.\n(Create/Load) \n";
		std::cin >> inputString;
	
		if (inputString == "Create") {
			std::cout << "Enter the input file Path \n";
			std::cin >> inputFilePath;

			std::cout << "Enter the output file path \n";
			std::cin >> outputFilePath;

			std::cout << "Enter number of chunks \n";
			std::cin >> outputFileSize;
			CreateSplitFile* createFileObj = new CreateSplitFile();
			createFileObj->Split(outputFileSize, inputFilePath, outputFilePath);
		}
		else if (inputString == "Load") {
			std::cout << "Enter the input file Path \n";
			std::cin >> inputFilePath;

			std::cout << "Enter the output file path \n";
			std::cin >> outputFilePath;
			std::cout << "Enter Key\n";
			unsigned char inputKey[64];
			
			unsigned char inputKey2[32];
			int i = 0;
			std::cin >> inputKey;
			convertCharToHex(inputKey, inputKey2);
			/*for (int i = 0; i < 32; i++)
			{
				if (inputKey2[i] == '\0')
				{
					std::cout << "00";
				}
				else
				{
					std::cout << std::hex << (int)inputKey2[i];
				}
			}
			std::cout << "\n";*/
			JoinFile* joinFile = new JoinFile();
			joinFile->join(inputFilePath, inputKey2, outputFilePath);
		}
		else {
			std::cout << "Please enter one of the values mentioned above \n";
		}
		std::cout << "To clean the screen press c, to close press z \n";
		std::cin >> consoleResponse;
		if (consoleResponse == "c")
		{
			//system("CLS");
		}
		else if (consoleResponse == "z")
		{
			break;
		}
	}
}
