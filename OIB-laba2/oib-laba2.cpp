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

void TheLargestSequence(const string seq)
{
	double pi[] = {0.2148, 0.3672, 0.2305, 0.1875};
	int v[] = { 0, 0, 0, 0 };
	int k = 0;
	double x = 0;

	for (int i = 0; i < 128; i += 8)
	{
		for (int j = i; j < i + 8; j += 1)
		{
			if (seq[j] == '1') k += 1;
			else k = 0;
		}
		cout << i << '\t' << k << endl;
		if (k <= 1) v[0] += 1;
		if (k == 2) v[1] += 1;
		if (k == 3) v[2] += 1;
		if (k >= 4) v[3] += 1;
	}

	for (int i = 0; i <= 3; i++)
	{
		x += pow((v[i] - 16 * pi[i]), 2) / (16 * pi[i]);
		cout << 'x' << x << endl;
	}
	FILE* file = fopen("random_sequence.txt", "a");
	fprintf(file, "%lf", x);
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
		TheLargestSequence(seq);
	}
	return 0;
}