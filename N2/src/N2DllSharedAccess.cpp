// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2DllSharedAccess.cpp
///
///	\brief 		Загрузчик DLL
/// \details	Загрузчик и экспортер функций из DLL
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		06.06.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#include "include/N2DllSharedAccess.h"
#include "../export/common/N2Register.h"
#include <iostream>
#include <fstream>

using namespace std;

N2DllSharedAccess::N2DllSharedAccess():
	hin(NULL)
{
	
}

bool N2DllSharedAccess::findLib(std_string path)
{
	bool retVal = false;
	FILE* pFile = std_fopen(path.c_str(), CT("r"));
	if(pFile) {
		path_ = path;
		fclose(pFile);
		retVal = true;
	}
	return retVal;
}

bool N2DllSharedAccess::attach(std_string path)
{
	if(path == EMPTY_STR)
		path = path_;
    hin = ::LoadLibrary((LPCWSTR)path.c_str());
	if(!hin) {
		//int k = ::GetLastError();
		return false;
	}
	return true;
}

bool N2DllSharedAccess::checkSignature(SIGN sign)
{
	return false;
}

PEXPROCEDURE N2DllSharedAccess::getProcedure(std_string nameProc)
{
	if(!hin)
		return NULL;
	return GetProcAddress(hin, nameProc.c_str());
}
