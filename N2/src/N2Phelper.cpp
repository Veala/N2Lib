#include "include\N2Phelper.h"


PHelper::~PHelper(void)
{
}


void
PHelper::Add(string token, int value)
{
	Psh b;
	b.token = token;
	b.value = value;
	buff.push_back(b);
}

void 
PHelper::Reset()
{
	buff.clear();
	delimiter = "| ";
}

void 
PHelper::ClearTokens()
{
	buff.clear();
}

//->
AHE 
PHelper::WhatIs(std::string attribute)
{
	AHE ahe = AHE_ERROR;
	char *pch, *tc;
	return_flags.clear();
	
	if(attribute == "")
		return AHE_EMPTY;
	
	// выжать пробелы
	//attribute.replace(
	int szIn = attribute.size();

	if(isdigit(attribute[0] & 0xFF))					
				{
				if (attribute[0] == '0' && szIn > 1 && (attribute[1] == 'x' || attribute[1] == 'X'))
					sscanf(attribute.c_str(), "%x", &return_int);
				else
					{
					sscanf(attribute.c_str(), "%d", &return_int);
					sscanf(attribute.c_str(), "%f", &return_float);
					}
				return AHE_DIGIT;
				}
				
	int valInt = 0;
	float valFl = 0.0;
	int szOut;
	sscanf(attribute.c_str(), "%d%n", &valInt, &szOut);
	if (szIn == szOut)
	{
		return_int = valInt;
		return_float = (float)valInt;
		return AHE_DIGIT;
	}
	return_int = 0;
	sscanf(attribute.c_str(), "%f%n", &valFl, &szOut);
	if (szIn == szOut)
	{
		return_float = valFl;
		return AHE_DIGIT;
	}

	pch = strtok_s(const_cast<char*>(attribute.c_str()), delimiter.c_str(), &tc);
	if(!pch)
		return AHE_ERROR;
	if(Find(pch))
		{
		ahe = AHE_TOKEN;
		do
			{
				pch = strtok_s(NULL, delimiter.c_str(), &tc);
				if(pch)	
						{
						string str = pch;
						if(Find(str))
								{
								ahe = AHE_TOKEN_FLAGS;
								}
						else
							return AHE_ERROR;
						}
			}while(pch);		
		}
	else
		{
		ahe = AHE_VARIABLE;
		return_flags.push_back(string(pch));
		}
		
	return ahe;
}

std::string 
PHelper::GetName()
{
	if(return_flags.size() <= 0)
			return string();
	return 
			return_flags[0];
}

int 
PHelper::GetValue()
{
	return return_int;
}


long 
PHelper::GetLongValue()
{
	return (long)return_int;
}

std::string 
PHelper::GetFirstFlag()
{
	if(return_flags.size() <= 0)
			return string();
	count = 1;
	return 
			return_flags[0];
}

std::string
PHelper::GetNextFlag()
{
	if(return_flags.size() <= count)
			return string();
	count ++;
	return
			return_flags[count - 1];
}


bool
PHelper::Find(std::string fnd)
{
	for(size_t i=0; i<buff.size(); i++)
		{
		if(buff[i].token == fnd)
			{
			return_flags.push_back(fnd);
			return_int = buff[i].value;
			return true;
			}
		}
	return false;
}
bool PHelper::HashString(std::string str)
{
	//buff.clear(); - сбрасывать буфер нельзя!
	char *pch, *tc;
	return_flags.clear();
	
	pch = strtok_s(const_cast<char*>(str.c_str()), delimiter.c_str(), &tc);
	if(pch)
			return_flags.push_back(pch);
	else
			return false;
	do
	{
	pch = strtok_s(NULL, delimiter.c_str(), &tc);
		if(pch)	
			return_flags.push_back(pch);
	}while(pch);

	return true;
}

std::string PHelper::SetDelimiter(std::string dlm_new)
{
	string ret = delimiter;
	delimiter = dlm_new;
	return ret;
}

int PHelper::StoI(string str, RADIX_CALC ncalc)
{
	int ret_val = 0;
	char* t;
	string tmp = str.substr(0,2);	
	if(tmp == "0x") {
		ncalc = RC_HEX;
		str.erase(str.begin());
		str.erase(str.begin());
	}
	if(ncalc == RC_DEC)
		ret_val = atoi(str.c_str());
	else if(ncalc == RC_HEX)
		{
		ret_val = strtol(str.c_str(), &t, 16);
		}
	else if(ncalc == RC_BIN)
		{
		ret_val = strtol(str.c_str(), &t, 2);
		}
		
	return ret_val;
}

int PHelper::GetFlagSet(void)
{
	int ret_val = 0;
	
	for(size_t i=0; i<return_flags.size(); i++)
	{
		for(size_t y=0; y<buff.size(); y++) {
			if(return_flags[i] == buff[y].token) {
					ret_val |= buff[y].value;
					break;
				}
		}
	}
	
	return ret_val;
}

float PHelper::GetValueFloat(void)
{
	return return_float;
}
