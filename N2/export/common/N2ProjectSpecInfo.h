// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ProjectSpecInfo.h
///
///	\brief 		
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		11.07.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once
#include "isolator.h"
#include <vector>
#include "N2Paths.h"

using namespace std;

struct N2ModulesSpecification
{
	std_string name;
	bool obligative;
	SIGN signature;
	std_string libName;
};

struct N2ProjectSpecialInfo
{
	std_string nameProject;
	N2Paths pathsTasks;
	N2Paths pathsDevices;
	vector<N2ModulesSpecification> modules;
};


