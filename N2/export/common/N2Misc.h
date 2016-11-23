// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Misc.h
///
///	\brief 		Набор утилитарных классов
/// \details	- структура менеджера памяти, определения,
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		21.03.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "isolator.h"
#include <vector>
using namespace std;



struct N2Memo 
{
	enum {
		NEW_OP,
		DELETE_OP
	} operation;

	N2Memo() : 
		sizeOfObject(0),
		number(0)
		{}
	void* ptr;
	std_string variableName;
	//std_string operation;
	COUNT sizeOfObject;
	COUNT number;
};


struct N2MemoManager
{
	vector<N2Memo> memory;	
	bool record;
	N2MemoManager():
		record(false) 
	{}

	void memReset(){memory.clear();}
};


