// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ParserXML.h
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
#include "N2ConcreteXMLParser.h"


template<class ConcreteXMLParser>
class N2ParserXML : public N2Parser,
					public N2ConcreteXMLParser
{
	ConcreteXMLParser* pParser_;

public:
	N2ParserXML():
		pParser_(NULL)
	{
		pParser_ = new ConcreteXMLParser();
	}
	virtual ~N2ParserXML()
	{
		if(pParser_)
			delete pParser_;
	}

	virtual CFS* parse(std_string filename, std_string& errorDescription, std_string firstMark)
	{
		return analysis(filename, errorDescription, firstMark);
	}

	void reset(void)
	{
		//pParser_->reset();
	}
private:
	///! 
	virtual CFS* analysis(const std_string filename, std_string& errorDescription, const std_string firstMark)
	{
		return pParser_->analysis(filename, errorDescription, firstMark);
	}

};