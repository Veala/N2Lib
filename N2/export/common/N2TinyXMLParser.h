// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2TinyXMLParser.h
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
#include "isolator.h"
//#include "N2TreeNode.h"
//#include "configuration.h"
#include "N2RealParser.h"


//

class N2TinyXMLParser : public N2ConcreteXMLParser
{
	CFS* pCFS;
public:
	///!
	virtual CFS* parse( std_string filename, 
						std_string& errorDescription, 
						std_string firstMark = EMPTY_STR);
	///
	//CFS* parseMacro(std_string filename, std_string nameMacro);

private:
	void writeNode(void* node, CFS* curNode);

};

