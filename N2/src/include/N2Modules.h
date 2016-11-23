// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Module.h
///
///	\brief 		Базовые классы модулей
/// \details	Модули для работы с физическими и логическими 
/// \details	устройствами 
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

#pragma once

#include "../../export/common/N2Module.h"
#include "N2SharedAccessWorker.h"

class N2Console;

class BaseConsoleHandler
{
	N2Console* pConsole_;
public:
	BaseConsoleHandler(N2Console* ptc):
		pConsole_(ptc)
	{}

	virtual Response command(DataPack* pPacket) = 0;
	virtual COUNT getListOfDevices(N2DevicesInfo& info) = 0;	
	virtual bool open(INDEX devNum) = 0;
	virtual bool close(INDEX devNum) = 0;

	Response reverse(DataPack& dp);
};


/// Специализированный модуль - консоль.
class N2Console : public N2Module
{
protected:

	bool alive_;
	BaseConsoleHandler* pHdlr;
	void* pObjCall;
	int(*pObjFuncCall)(void*, DataPack&);

public:
	N2Console():
		pHdlr(NULL),
		pObjCall(NULL),
		pObjFuncCall(NULL),
		alive_(false)
	{}
	/// Исполнить команду
	Response command(DataPack* pPacket);
	/// Сброс устройства
	bool reset(bool hard = true);
	/// открыть устройство
	virtual bool open(INDEX devNum = N2_ACTIVE_DEVICE);
	/// Освободить устройство
	virtual bool close(INDEX devNum = N2_ACTIVE_DEVICE);
	/// Проверка подключения устройства
	virtual bool alive(INDEX devNum = N2_ACTIVE_DEVICE);
	/// Set
	bool setBCH(BaseConsoleHandler* pBCH) 
	{ 
		if(pBCH) {
			pHdlr = pBCH;
			alive_ = true;
			return true;
		}
		return false;
	}
	///
	virtual bool initial(const N2RouteLine* pInfo);
	//
	virtual COUNT getListOfDevices(N2DevicesInfo& info);
	//
	virtual void setCallBackFunc(void*, int(*)(void*, DataPack&));
	/// Посылка запроса в процессор
	virtual Response reverse(DataPack& dp);
};


/// Внешний подключаемый модуль
class N2ModuleExternal : public N2Module
{
	N2SharedAccessWorker* connector_;
	typedef bool (*alive_)(INDEX devNum);
	typedef Response (*command_)(DataPack* );
	typedef void (*setCallBackPtr)(void* pMPC, int(*pSF)(void*, DataPack&));
	alive_ f_alive;
	command_ f_command;
	setCallBackPtr f_callBack;
	std_string pathName;

	void enumerationDevices(void);

	Response commander(DataPack* pPack);

public:
	N2ModuleExternal():
		connector_(NULL),
		f_alive(NULL),
		f_command(NULL),
		f_callBack(NULL)
	{}
	~N2ModuleExternal();
	///
	virtual Response command(DataPack* pPacket);
	///
	virtual bool alive(INDEX devNum)
	{ 
		if(!f_alive)
			return false;
		return f_alive(devNum);
	}
	virtual bool open(INDEX devNum = N2_ACTIVE_DEVICE);
	/// Освободить устройство
	virtual bool close(INDEX devNum = N2_ACTIVE_DEVICE);
	///!
	virtual void setCallBackFunc(void* pMPC, int(*pSF)(void*, DataPack&));
	///! Сброс устройства
	bool reset(bool hard = true);
	///! 
	virtual bool initial(const N2RouteLine* pInfo);
	///!
	//bool activate(void);
	///!
	//bool deactivate(void);
	///
	virtual COUNT getListOfDevices(N2DevicesInfo& info);
};

/// Внутренний модуль библиотеки N2
class N2ModuleInternal : public N2Module
{
	
public:
	///! Исполнить команду
	Response command(DataPack* pPacket);
	///! Сброс устройства
	bool reset(bool hard = true);
	///! Проверка подключения устройства
	bool alive(INDEX devNum = N2_ACTIVE_DEVICE);
	///!
	virtual bool initial(const N2RouteLine* pInfo);

};

class N2Debuger : public N2Console
{
public:
	virtual bool open(INDEX devNum) { return true; }
};

/// Модуль взаимодействия с операционной системой
class N2System : public N2Module
{
	
public:
	///! Исполнить команду
	Response command(DataPack* pPacket);
	///! Сброс устройства
	bool reset(bool hard = true);
	///! Проверка подключения устройства
	bool alive(INDEX devNum);
	///!
	virtual bool initial(const N2RouteLine* pInfo);
	///!

};