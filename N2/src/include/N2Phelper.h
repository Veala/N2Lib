#pragma once
#include <string>
#include <vector>
#include <isolator.h>

using namespace std;

enum AHE 
		{
 		 AHE_ERROR,
		 AHE_TOKEN,			// токен, константное строковое значение
		 AHE_TOKEN_FLAGS,	// набор токенов (разделённых разделителями )
		 AHE_DIGIT,			// число
		 AHE_VARIABLE,		// переменная
		 AHE_EMPTY			// пусто
		 };

enum RADIX_CALC
		{
		RC_DEC,
		RC_HEX,
		RC_BIN
		};

class PHelper
{
	struct Psh
		{string token;
		int value;} ;
	std::vector<Psh> buff;
	int return_int;
	float return_float;
	//long return_long;
	std::vector<string> return_flags;
	size_t count;
	bool Find(string fnd);
	string delimiter;
public:
	PHelper():return_int(-1), count(0), delimiter("| ") {};
	void AddFirst(string token, int value = 0)
		{Reset(); Add(token, value);}
	void Add(string token, int value = 0);
	void Reset();
	AHE WhatIs(string attribute);
	string GetName();
	int GetValue();
	float GetValueFloat(void);
	long GetLongValue();
	// переименовать в GetFirstToken и GetNextToken
	string GetFirstFlag();
	string GetNextFlag();
	size_t Count() { return return_flags.size(); }

	~PHelper(void);
	bool HashString(std::string str);
	std::string SetDelimiter(std::string dlm_new);
	int StoI(std::string str, RADIX_CALC ncalc = RC_DEC);
	int GetFlagSet(void);
	void ClearTokens(void);
};
