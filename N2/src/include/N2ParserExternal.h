// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ParserExternal.h
///
///	\brief 		
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		29.04.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "N2Parser.h"

class N2ParserExternal : public N2Parser
{
	virtual CFS* parse( std_string filename);
};