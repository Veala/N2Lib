// -*- mode:c++; coding:utf-8; -*-
///
/// \file		configuration.h
///
///	\brief 		Общие определения конфигурации ядра
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		06.06.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once


#include "N2RealParser.h"
#include "N2TinyXMLParser.h"
#include "N2RapidXMLParser.h"
#include "N2Standart2014ProjectNode.h"
#include "N2Serializer.h"


/// Тип N2DefaultXMLParserT задает библиотеку XML разборщика
#ifdef SET_UNICODE
	typedef  N2RealParser<N2RapidXMLParser> N2DefaultXMLParserT;
#else
	typedef  N2RealParser<N2TinyXMLParser>  N2DefaultXMLParserT;
#endif

typedef N2Serializer<N2Standart2014ProjectNode, N2DefaultXMLParserT > N2DefaultSerializerT;

