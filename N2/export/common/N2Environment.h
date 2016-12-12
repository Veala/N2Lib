// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Environment.h
///
///	\brief 		Переменные окружения
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

#pragma once

#include <list>
#include "N2Variable.h"
//#include "N2Types.h"


class N2Environment
{
	std::list <N2BaseVariable*> listEnvmt;		
	std::list <N2BaseVariable*>::const_iterator curIterator;

public:
	/// Получить глобальную переменную по имени.
	const N2BaseVariable* get(std_string nameVar);
	/// Получить глобальную переменную по имени для изменения.
	N2BaseVariable* change(std_string nameVar);
	/// Очистить список глобальных переменных.
	void clear(void);
	/// Добавить глобальную переменную в список.
	bool add(N2BaseVariable* pVar);
	/// Перебирать переменные по очереди.
	N2BaseVariable* first() { curIterator = listEnvmt.begin(); return *curIterator; }
	N2BaseVariable* next() { return ++curIterator == listEnvmt.end() ? NULL : *curIterator; }
};
