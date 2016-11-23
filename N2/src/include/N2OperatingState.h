// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2OperatingState.h
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

#include "../../export/common/IControl.h"
#include "N2Processor.h"
#include "N2Order.h"
#include "N2ModulesManager.h"
//#include "../../export/common/N2ProjectNode.h"



/// Класс отвечающий за запуск и состояние текущей задачи
class N2OperatingState :	public ILauncher 					
{
protected:

	N2Processor* pProc_;
	N2Order* pOrder_;
	N2ModulesManager* pMM_;

public:
	N2OperatingState():
		pProc_(NULL),
		pOrder_(NULL),
		pMM_(NULL)
	{
		pProc_ = N2Register::self()->getMemoryAllocator()->create<N2Processor>("Processor");
	}

	~N2OperatingState()
	{
		if(pProc_)
			N2Register::self()->getMemoryAllocator()->release(pProc_);
	}

	/// Получить текущий режим работы ядра
	virtual OPERATING_MODE mode(void)
		{
			return MODE_UNDEFINE;
		}

	/// Привязать очередь команд (байт-код) загруженной задачи к процессору
	/// \param pOrder - указатель на очередь команд (байт-код)
	virtual void setOrder(N2Order* pOrder)
	{
		pOrder_ = pOrder;
	}
	
	/// Подключить менеджер модулей
	/// \param pMM - указатель на менеджер модулей
	virtual void setModulesManager(N2ModulesManager* pMM)
	{
		pMM_ = pMM;
	}




};

