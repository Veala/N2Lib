// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ControlObject.h
///
///	\brief 		Объект для получения доступа к библиотеке N2
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

#include "IControl.h"

class N2Control;

/// Класс получения интерфейса доступа к управлению библиотекой N2.
/// Пример:
/// IControl* pIControl = N2ControlObject::getControl();
class N2ControlObject 
{

	static N2Control* selfControl;
	
	N2ControlObject() ;
	~N2ControlObject();
	
public:
	/// Статическая ф-ция получения интерфейса управления библиотекой N2
	static IControl* getControl(void);
	static IControl* createControl(void);

private:
	static IControl* getObj(void);
};
