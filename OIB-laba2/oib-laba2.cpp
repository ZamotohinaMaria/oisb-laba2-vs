#include <stdio.h>
#include <fstream>
#include <iostream>>
#include <random>
#include <string>
#include <math.h>

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

void FrequencyBitwiseTest(const string seq)
{
	double s, p;
	s = 0;
	for (int i = 0; i < 128; i++)
	{
		if (seq[i] == '1') s += 1;
		if (seq[i] == '0') s += (-1);
	}
	s = s / sqrt(128);
	p = erfc(s / sqrt(2));

	FILE* file = fopen("random_sequence.txt", "a");
	fprintf(file, "%lf", p);
	fprintf(file, "%c", '\n');
	fclose(file);
}

void IdenticalBits(const string seq)
{
	double ones, p, v;
	ones = 0;
	v = 0;
	for (int i = 0; i < 128; i++)
	{
		if (seq[i] == '1') ones += 1;
	}
	ones /= 128;
	if (abs(ones - 0.5) < 2 / sqrt(2) == false) 
		p = 0;
	else
	{
		for (int i = 0; i < 127; i++)
		{
			if (seq[i] == seq[i + 1]) v += 0;
			if (seq[i] != seq[i + 1]) v += 1;
		}

		p = erfc((abs(v - 2 * 128 * ones * (1 - ones))) / (2 * sqrt(2 * 128) * ones * (1 - ones)));
	}
	FILE* file = fopen("random_sequence.txt", "a");
	fprintf(file, "%lf", p);
	fprintf(file, "%c", '\n');
	fclose(file);
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

		FrequencyBitwiseTest(seq);
		IdenticalBits(seq);
	}
	return 0;
}