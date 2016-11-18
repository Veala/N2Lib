// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2System.cpp
///
///	\brief 		Модуль операционной системы
/// \details	
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

#include "include\N2Modules.h"

///! Исполнить команду
Response N2System::command(DataPack* pPacket)
{
	return Response(ERR);
}

///! Сброс устройства
bool N2System::reset(bool hard)
{
	return false;
}

///! Проверка подключения устройства
bool N2System::alive(INDEX devNum)
{
	return false;
}

bool N2System::initial(const N2RouteLine* pInfo)
{
	return false;
}