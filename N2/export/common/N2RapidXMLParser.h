// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2RapidXMLParser.h
///
///	\brief 		
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		14.05.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "N2RealParser.h"
//
//class N2ConcreteXMLParser;

class N2RapidXMLParser : public N2ConcreteXMLParser
{
	
public:
	///!
	virtual CFS* parse(const std_string filename, 
						const std_string firstMark);
};

