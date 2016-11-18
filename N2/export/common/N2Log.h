// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Log.h
///
///	\brief 		Файл журнала
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		11.07.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "N2Base.h"
#include "N2Defines.h"
//#include "N2Order.h"

/// Рабочий журнал 
class N2Logbook 
{	

public:
	N2Logbook();
	virtual ~N2Logbook();


	/// Запись в журнал
	void Write(std::string record);
	/// Запись в журнал обнаруженной ошибки
	bool WriteError(std::string module, int error, std::string description);
	/// Вывод журнала в файл
	void Print(std::string filename, bool add_over = false);
	/// Установить обработчик вывода	
	void SetResponse(void (*resp)(string));
	/// Сброс последней ошибки ????
	void ResetError();
	/// Получить значение и описание ошибки
	int GetLastError(std::string& description);
	/// Запрет или разрешение записи
	/// \param interd : true - запрет записи, false - отмена запрета записи
	void SetInterdiction(bool interd);
	
	/// Ф-ции профилирования кода
	/// Активировать профилировщик
	//void ProfilerInit(N2Order* porder, unsigned int length);
	/// Запись в файл профилировщика
	//void Profiler(DataPack* ptc, unsigned int ip, int time);
	/// Деактивировать профилировщик
	//void ProfilerStop(void);
	
private:
	void (*response)(string message);
	std::string descr_error;
	int current_error;
	FILE *profile;

	struct LOGED{
	std::string module;
	int error;
	std::string descr;
	} loged;

	std::vector<LOGED> log_error;
	bool write_interdiction;
	
	typedef struct PROFILER_S
		{
		PROFILER_S(): init(false), count(0), name(CT(" - - -")), sign(0), time(0) {}
		bool init;
		string name;
		int sign;
		int time;
		int count;
		} 
		PROFILER_STRUCT;
	unsigned int order_length;
	//N2Order* po;
	
	PROFILER_STRUCT* pProfStruct;
};