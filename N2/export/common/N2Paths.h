// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Paths.h
///
///	\brief 		Пути
/// \details	Пути 
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		27.07.2015
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "isolator.h"
#include <vector>


class N2Paths
{
	std::vector<std_string> paths;
	unsigned int index;

public:

	N2Paths() :
		index(0){};
	N2Paths(const N2Paths& obj) :
		index(0)
	{
		if(this == &obj)
			return;
		std::vector<std_string>::const_iterator it = obj.paths.begin();
		while(it != obj.paths.end()) {
			paths.push_back(*it);
			it ++;
		}
	};

	void
	addPath(const std_string path) {
		// должна быть проверка на дублирование ???
		paths.push_back(path);
	}

	void
	resetPaths(void)
	{
		paths.clear();
	}

	std_string 
	getFirstPath(void)
	{
		if(paths.empty())
			return EMPTY_STR;
		index = 0;
		return paths[index];
	}

	std_string 
	getNextPath(void)
	{
		index ++;
		if(index >= paths.size())
			return EMPTY_STR;
		return paths[index];
	}

	bool
	empty(void)
	{
		return paths.empty();
	}

	size_t
	size(void) 
	{
		return paths.size();
	};


	/// operator =
	
};