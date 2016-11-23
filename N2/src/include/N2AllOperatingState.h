// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2AllOperatingState.h
///
///	\brief 		Общий класс рабочего состояния управляемого объекта
/// \details	
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		21.03.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "N2OperatingState.h"
#include "N2Processor.h"
#include "../../export/common/N2TreeNode.h"


/// Класс реализации "ручного" режима работы ядра
class N2OperatingStateManual:	public N2OperatingState 					
{
	STATE_TASK stateTask;

public:
	N2OperatingStateManual(){};

	/// Запуск загруженной задачи
	virtual STATE_TASK run(void);

	/// Аварийный останов загруженной задачи
	virtual STATE_TASK stop(void);

	/// Получить состояние выполняемой задачи
	virtual STATE_TASK getTaskState(void) const;	

	virtual bool clock(void);
	
	virtual STATE_TASK pause(void);

	OPERATING_MODE mode(void)
		{
			return MODE_MANUAL;
		}

};

/// Класс реализации автоматического режима работы ядра
class N2OperatingStateAuto:	public N2OperatingState 					
{
	/// Запуск загруженной задачи
	virtual STATE_TASK run(void);

	/// Аварийный останов загруженной задачи
	virtual STATE_TASK stop(void);

	/// Получить состояние выполняемой задачи
	virtual STATE_TASK getTaskState(void) const;	

	virtual bool clock(void);
	
	virtual STATE_TASK pause(void);

	OPERATING_MODE mode(void)
		{
			return MODE_AUTO;
		}
};

/// Класс реализации отладочного режима работы ядра
class N2OperatingStateDebug:	public N2OperatingState 					
{
	STATE_TASK stateTask;
public:
	/// Запуск загруженной задачи
	virtual STATE_TASK run(void);

	/// Аварийный останов загруженной задачи
	virtual STATE_TASK stop(void);

	/// Получить состояние выполняемой задачи
	virtual STATE_TASK getTaskState(void) const;	

	virtual bool clock(void);
	
	virtual STATE_TASK pause(void);

	OPERATING_MODE mode(void)
		{
			return MODE_DEBUG;
		}

	N2Processor* getProcessor(void)
	{
		return pProc_;
	}
};

/// Класс реализации режима холостого хода ядра
class N2OperatingStateIdle:	public N2OperatingState 					
{
	/// Запуск загруженной задачи
	virtual STATE_TASK run(void);

	/// Аварийный останов загруженной задачи
	virtual STATE_TASK stop(void);

	/// Получить состояние выполняемой задачи
	virtual STATE_TASK getTaskState(void) const;	

	virtual bool clock(void);
	
	virtual STATE_TASK pause(void);	
	
	OPERATING_MODE mode(void)
		{
			return MODE_IDLE;
		}
};
