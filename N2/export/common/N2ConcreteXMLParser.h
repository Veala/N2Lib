// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ConcreteXMLParser.h
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

#include <N2Parser.h>



/// Обобщенный класс для конкретного парсера фомата XML
// Интерфейс класса вырожден, но позволяет менять его не затрагивая
// общие ф-ции разбора проекта
class N2ConcreteXMLParser : public N2Parser
{
protected:

	//vector<std_string>* pPaths_;
	//COUNT index_;

	//std_string getFirstPath(void) {
	//	if(pPaths_ && !pPaths_->empty()) {
	//		index_ = 0;
	//		return (*pPaths_)[0];
	//	}
	//	return std_string();
	//}
	//
	//std_string getNextPath(void) {
	//	index_ ++;
	//	if(pPaths_ && pPaths_->size() < index_) 
	//		return (*pPaths_)[index_];		
	//	return std_string();
	//}


public:
	N2ConcreteXMLParser() {}
	//	pPaths_(NULL),
	//	index_(0)
	//{};

	/// Производит разбор файла XML фомата и преобразование его спец. структуру данных.
	/// \param filename - имя разбираемого файла
	/// \param firstMark - метка в файле с которой начинается разбор
	/// \return указатель на дерево разбора с узлами в формате XMLF.
	//virtual CFS* parse(const std_string filename, std_string& errorDescription, const std_string firstMark = EMPTY_STR) = 0;

	/// Установка путей поиска
	//virtual void setPaths(vector<std_string>* paths)
	//{
	//	pPaths_ = paths;
	//}

};



