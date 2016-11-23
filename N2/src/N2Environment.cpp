// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Environment.cpp
///
///	\brief 		Блок глобальных переменных
/// \details	
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

#include <N2Environment.h>


const N2BaseVariable* N2Environment::get(std_string nameVar)
{
	std::list <N2BaseVariable*>::iterator it = listEnvmt.begin();
	while(it != listEnvmt.end()) {
		if((*it)->name() == nameVar)
			return *it;
		it ++;
	}
	return NULL;
}

N2BaseVariable* N2Environment::change(std_string nameVar)
{
	std::list <N2BaseVariable*>::iterator it = listEnvmt.begin();
	while(it != listEnvmt.end()) {
		if((*it)->name() == nameVar)
			return *it;
		it ++;
	}
	return NULL;
}

void N2Environment::clear(void)
{
	std::list <N2BaseVariable*>::iterator it = listEnvmt.begin();
	while(it != listEnvmt.end()) {
		if(*it)
			delete *it;
		it ++;
	}
	listEnvmt.clear();
}


bool N2Environment::add(N2BaseVariable* pVar)
{
	bool retVal = false;
	
	if(pVar == NULL)
		return retVal;
	listEnvmt.push_back(pVar->clone());
	
	return true;
}