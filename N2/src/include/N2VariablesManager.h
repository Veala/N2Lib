// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2VariablesManager.h
///
///	\brief 		Управитель переменными :)
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		15.07.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "../common/N2Base.h"
//#include "N2Variable.h"
#include "N2Types.h"
#include <vector>

using namespace std;

//typedef enum VARMANTYPE{
//	VMT_CACHE,
//	VMT_GLOBAL
//}	N2_VMT;

class N2VariablesManager
{
    vector<N2BaseVariable*> cache;
	//vector<N2BaseVariable*> globalVariable;

public:

	N2VariableCreator creator;
    
    bool declare(N2BaseVariable* pVar/*, N2_VMT type = VMT_CACHE*/);
    bool release(std_string name/*, N2_VMT type = VMT_CACHE*/);
	void clear(/*N2_VMT type = VMT_CACHE*/);

	N2BaseVariable* getVar(std_string name);
	//N2BaseVariable* getGlobal(std_string name);

	vector<N2BaseVariable*>* getCache(void) {return &cache;} ;

	//template<class T>
	//T* getAs(std_string name);

	/*
    bool setValue(TYPE type, std_string name, void* val, INDEX index = 0);

    void* get(TYPE type, std_string name, INDEX index)
	{
		return NULL;	    
	}
	*/
};
