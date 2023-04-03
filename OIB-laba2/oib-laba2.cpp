#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <random>
#include <string>

using namespace std;

int RandomNumber()
{
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(-99999, 99999); // distribute results between -99999 and 99999 inclusive.

	return dist(gen);
}

string Generation()
{
	string seq = "";
	for (int i = 0; i < 128; i++)
	{
		if (RandomNumber() < 0) seq += '0';
		else seq += '1';
	}
	return seq;
}

bool FileIsExist(string filePath)
{
	bool isExist = false;
	ifstream fin(filePath.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}

int main()
{
	if (FileIsExist("random_sequence.txt")) remove("random_sequence.txt");
	string seq = "";
	for (int q = 0; q < 3; q++)
	{
		seq = Generation();
		seq += '\n';
		FILE* file = fopen("random_sequence.txt", "a");
		const char* str = seq.c_str();
		fprintf(file, "%s", str);
		fclose(file);
	}
	return 0;
}