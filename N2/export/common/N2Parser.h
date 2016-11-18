// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Parser.h
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

#include "N2Base.h"
#include "N2XMLF.h"




class N2Parser : public N2Base
{
protected:
	//std::vector<std_string> paths;
	//unsigned int index;

public:
	
	N2Parser()/*:
		index(0)*/
	{}

	virtual CFS* parse( std_string filename, 
						std_string& errorDescription, 
						std_string firstMark = EMPTY_STR) = 0;

	//virtual void reset(void) = 0;

	//virtual void
	//addSearchPath(std_string path) {
	//	paths.push_back(path);
	//}

	//virtual void
	//	resetPaths(void)
	//{
	//	paths.clear();
	//}

	//std_string getFirstPath(void)
	//{
	//	if(paths.empty())
	//		return EMPTY_STR;
	//	index = 0;
	//	return paths[index];
	//}

	//std_string getNextPath(void)
	//{
	//	index ++;
	//	if(index >= paths.size())
	//		return EMPTY_STR;
	//	return paths[index];
	//}
};
