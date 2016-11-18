// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Base.h
///
///	\brief 		Общий шаблонный класс
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

#include "isolator.h"

/// Общий класс, от которого наследуют практически все классы библиотеки N2
class N2Base
{
	std_string nameModule;
protected:
//	ExC exc;
public:
	N2Base() 
	{
		// определение наименования модуля, запихиваем его в исключение
	}
	virtual ~N2Base() {}

};
