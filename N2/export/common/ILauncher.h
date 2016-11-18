// -*- mode:c++; coding:utf-8; -*-
///
/// \file		IControl.h
///
///	\brief 		Интерфейс управления задачей.
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		21.03.2014
/// \version 	0.1
///  
//  История изменений :
//  
//

#pragma once

#include "isolator.h"

using namespace N2_Defines;

/// Интерфейс управления состоянием задачи
class ILauncher
{

public:

	/// Запуск загруженной задачи
	/// \return Возвращает текущее состояние задачи
	virtual STATE_TASK run(void) = 0;

	/// Аварийный останов загруженной задачи
	/// \return Возвращает текущее состояние задачи
	virtual STATE_TASK stop(void) = 0;

	/// Получить состояние выполняемой задачи
	/// \return Возвращает текущее состояние задачи
	virtual STATE_TASK getTaskState(void) const = 0;
	
	/// Пауза исполнения задачи
	/// \return Возвращает текущее состояние задачи
	virtual STATE_TASK pause(void) = 0;

	/// Запуск исполнения команд ("задающий генератор")
	/// \return true - в очереди процессора есть команды, false - задача выполнена.
	virtual bool clock(void) = 0;

};
