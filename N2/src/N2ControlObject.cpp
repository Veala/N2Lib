// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ControlObject.cpp
///
///	\brief 		Управляющий объект 
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
#include "../export/common/N2ControlObject.h"
#include "include/N2Control.h"


N2Control* N2ControlObject::selfControl = NULL;


N2ControlObject::N2ControlObject()
{
};


N2ControlObject::~N2ControlObject()
{
};

IControl* 
N2ControlObject::getObj(void)
{
	if(!N2ControlObject::selfControl)
		N2ControlObject::selfControl = new N2Control();
	return N2ControlObject::selfControl;
}

IControl*
N2ControlObject::getControl(void)
{
	return getObj();
};

IControl*
N2ControlObject::createControl(void)
{
	if (N2ControlObject::selfControl)
		delete N2ControlObject::selfControl;
	N2ControlObject::selfControl = new N2Control();
	return N2ControlObject::selfControl;
};

//N2Control* 
//N2ControlObject::getLauncher(void)
//{
//	return getObj();
//}