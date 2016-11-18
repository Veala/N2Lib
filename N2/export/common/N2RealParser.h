// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2RealParser.h
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
class N2RealParser : public N2ConcreteXMLParser
{
	ConcreteXMLParser* pConcPar_;

public:
	N2RealParser():
		pConcPar_(NULL)
	{
		pConcPar_ = new ConcreteXMLParser();
	}
	virtual ~N2RealParser()
	{
		if(pConcPar_)
			delete pConcPar_;
	}

	virtual CFS* parse(std_string filename, std_string& errorDescription, std_string firstMark)
	{
		return pConcPar_->parse(filename, errorDescription, firstMark);
	}



private:
	///! 
	//virtual CFS* analysis(const std_string filename, std_string& errorDescription, const std_string firstMark)
	//{
	//	return pConcPar_->analysis(filename, errorDescription, firstMark);
	//}

};