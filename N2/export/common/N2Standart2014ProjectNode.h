// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Standart2014ProjectNode.h
///
///	\brief 		Интерфейс стандартного узла дерева проекта
/// \details	Данные полностью описывающие узел дерева загруженного стандартного проекта
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		03.07.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "N2ProjectNode.h"
#include <vector>

using namespace std;

struct N2Standart2014SpecialInfo
{
	// список парсеров 
	// список байткодеров
};



struct N2Standart2014ProjectNode : public N2ProjectNode
{
	static std_string mark;
	std_string name;
	std_string scriptName;
	std_string description;
	//
	//COLORING color;
	bool enable;
	bool execute;

	static N2Standart2014SpecialInfo info_;

public:
	N2Standart2014ProjectNode();
	virtual ~N2Standart2014ProjectNode();
	//
	virtual 
	bool interpretation(CFS *parsedTree);

	virtual
	std_string 	getMark(void) 
	{
		return mark;
	}


	///! разбор дерева с полным анализом 
	virtual bool
		parseTree(std_string filename, std_string& errorDescription);


};

