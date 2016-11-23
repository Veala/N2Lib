// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ModulesManager.h
///
///	\brief 		Управитель модулей
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

#include "N2Base.h"
#include "N2Module.h"



/// Менеджер устройств (исполняемых модулей)
class N2ModulesManager : public N2Base
{
	//N2RoutingTable table_;
	N2ListModules modules_;

public:
	N2ModulesManager();
	/// Автоматическое заполнение списка модулей управления устройствами
	/// При вызове этой ф-ции модули загруженные вручную сбрасываются, их надо 
	/// добавлять сызнова
	bool updateModulesList(void);
	/// Обновить состояние устройств
	bool updateDevices(void);
	/// Получить список модулей
	N2ListModules* getListTable(void);
	/// Создать логический модуль.
	/// На каждое реальное или виртуальное устройство создается свой отдельный модуль.
	N2Module* createModule(const N2RouteLine* pInfo);
	///  Добавить созданный модуль
	bool addModuleManual(N2Module* pModule);
	/// Удалить созданный модуль 
	bool deleteModule(N2Module* pModule);
	/// Маршрутизация команды
	bool AutoExecuteCommand(DataPack* pPack, Response& resp);
};