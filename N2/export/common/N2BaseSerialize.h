// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2BaseSerialize.h
///
///	\brief 		Абстактный класс сериализации проекта
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		06.06.2014
/// \version 	0.1
///  
///  История изменений:
///  03.03.15 - добавлена ф-ция addSearchPath
///

#pragma once

#include "isolator.h"
#include "ITreeNode.h"


/// Базовый класс загрузки/сохранения проектов
class N2BaseSerialize
{
public:
	/// Загрузить проект
	/// \param filename - имя файла загружаемого проекта
	//virtual ITreeNode*
	virtual bool
	loadProject(std_string filename, std_string& errorDescription) = 0;

	/// Добавляет пути для поиска для файлов загружаемого проекта.
	/// Можно добавить множество путей.
	//virtual bool
	//	addSearchPath(std_string filename) = 0;


	virtual bool
	saveProject(std_string filename) = 0;	

};

