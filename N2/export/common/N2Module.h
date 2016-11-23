// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Module.h
///
///	\brief 		Универсальный класс модуля
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

#pragma once

#include "N2Base.h"
#include "N2Commands.h"
#include "N2Paths.h"

using namespace N2_Defines;

/// Структура определяющая соответствие сигнатуры её исполняемому модулю
struct N2RouteLine 
{
	N2RouteLine():
		signOut(0),
		resolveSwitch(false)
	{}
	/// сигнатура устройств
	SIGN signIn;
	/// обязательные ли устройства?
	bool obligative;
	/// имя файла библиотеки управления 
	std_string fileExtLibrary;
	/// общее наименование устройств
	std_string name;
	/// пути поиска библшиотек управления
	N2Paths paths; // путь
	/// разрешено ли перенаправление команд
	bool resolveSwitch;
	/// сигнатура перенаправления
	SIGN signOut;
	/// политика использования модуля (разрешение автопоиска и подключения)
	FINDER_DEVICE autoChange;

	bool operator == (const N2RouteLine& op) const;
};



/// Класс устройства (исполняемого модуля).
/// Данный класс исполняет адресованные ему команды.
/// Неверно адресованная команда игнорируется.
class N2Module : public N2Base
{
protected:
	//SIGN signature_;
	N2RouteLine selfInfo;

public:
	N2Module() {};
	/// Исполнить команду
	virtual Response command(DataPack* pPacket) = 0;
	/// Сброс устройства
	virtual bool reset(bool hard = true) = 0;
	/// Проверка подключения устройства
	virtual bool alive(INDEX devNum = N2_ACTIVE_DEVICE) = 0;
	/// Открыть устройство 
	/// (без параметра открывается устройство назначенное активным)
	virtual bool open(INDEX devNum = N2_ACTIVE_DEVICE);
	/// Освободить устройство
	virtual bool close(INDEX devNum = N2_ACTIVE_DEVICE);
	/// Получить сигнатуру устройства 
	virtual SIGN getSignature(void)
	{ return selfInfo.signIn;}
	/// Инициировать модуль поддержки устройств
	virtual bool initial(const N2RouteLine* pInfo) = 0;
	/// Установить в модуле ф-цию обратного вызова
	virtual void setCallBackFunc(void*, int(*)(void*, DataPack&)) 
		{};
	///
	virtual const N2RouteLine getRouteLine(void) const;
	///
	virtual COUNT getListOfDevices(N2DevicesInfo& info);

	/// Обновление состояния всех устройств
	virtual void update(void);

	/// Перенаправление потока команд на устройство с
	/// сигнатурой signOut
	/// \param  signOut - сигнатура устройства , на которое перенаправляется поток команд
	/// \return true - при удачном переключении, false - в противном случае (значение переключателя ).
	virtual bool redirection(SIGN signOut);

	/// Отключение перенаправления потока команд
	virtual bool stopRedirection(void);
};


/// Список устройств (исполняемых модулей)
class N2ListModules 
{
	size_t curIndex;
	std::vector<N2Module*> vecMods;

public:
	N2ListModules();
	~N2ListModules();
	bool add(N2Module* pModule);
	bool del(N2Module* pModule);
	N2Module* find(const N2RouteLine* pRl);
	N2Module* find(SIGN signature);
	N2Module* first(void);
	N2Module* next(void);
	UINT_N2 size(void);
	void clear();

	/// Перенаправление потока команд с устройства с сигнатурой sign_src
	/// на устройство с сигнатурой sign_dst
	/// \return true - при удачном переключении, false - в противном случае.
	bool redirection(SIGN sign_src, SIGN sign_dst);

	/// Отключение перенаправления потока команд
	bool stopRedirection(SIGN signature);

};