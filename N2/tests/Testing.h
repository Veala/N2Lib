// -*- mode:c++; coding:utf-8; -*-
///
/// \file		 Testing.h
///
///	\brief 		
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		28.04.2014
/// \version 	0.1
///  
///  История изменений:
///  

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace GloTest
{
	string nameTesting;
	typedef unsigned int NUM;
	enum TYPE
	{
		TYPE_ERROR,
		TYPE_EXCEPTION
	};

	struct PAER
	{
		NUM line;
		TYPE type;
	}; 
	
	NUM ok;
	NUM fail;
	NUM except;
	vector<PAER> results;


	bool test(bool inv, int line)
	{
		try {
			if(inv)
				ok ++;
			else {
				fail ++;
				PAER r;
				r.line = line;
				r.type = TYPE_ERROR;
				results.push_back(r);
			}
		} // try
		catch(...)
		{
			except ++;
			PAER r;
			r.line = line;
			r.type = TYPE_EXCEPTION;
			results.push_back(r);
		}
		return inv;
	}

	
#define TEST_CHK(x) test(x, __LINE__)
#define TEST_INIT(x) nameTesting = x
//#define TEST_AND_SOE(x)  (if(!test(x, __LINE__))return 1)

	unsigned int errors(void)
	{
		return fail + except;
	}

	void printResult(void)
	{
		cout << "=============================================" << endl;
		cout << "   TEST :   " << nameTesting.c_str() << endl; 
		cout << "=============================================" << endl;		
		cout << "OKs:           " << ok << endl;
		cout << "FAILs:         " << fail << endl;
		cout << "EXCEPTIONs:    " << except << endl;
		cout << "--------------------------------------------" << endl;
		cout << "All checks:    " << ok + fail + except << endl;
		cout << "=============================================" << endl;
		cout << endl << "Details:" << endl;
		for(NUM i=0; i<results.size(); i++) {
			cout << " Line # " << results[i].line << "  -  " ;
			cout << ((results[i].type == TYPE_ERROR)?"error":"exception") << endl; 
		}
		cout << endl << " * RESULT - " << ((fail+except == 0)?"Ok!":"Fail!") << endl;
		cout << endl << endl;
	};

};
 
