// -*- mode:c++; coding:utf-8; -*-
///
/// \file		Processor.h
///
///	\brief 		Исполняющий виртуальный процессор
/// \details	Исполнение потока команд
///
/// \copyright  
/// \author 	
///
/// \date 		21.03.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "N2Order.h"
#include "N2ModulesManager.h"
#include "../../export/common/N2TreeNode.h"
#include "../../export/common/N2Base.h"
#include "../../export/common/N2Register.h"
#include "../include/N2VariablesManager.h"
#include <time.h>
#include <stack>


class N2Processor : public N2Base
{
	N2Order* pOrder_;
	///! Менеджер устройств
	N2ModulesManager *pModsMan_;

	bool initial;
	/// Менеджер стека переменных
	N2VariablesManager manVars;
	// флаг конца очереди команд (окончание работы)
	bool queue_empty;
	// флаг ошибки, в результате которой работа должна закончиться
	bool fatal_error;
	///! Включение/отключение журналирования шагов
	bool step_log;
	///! Имя текущего шага
	std_string nameStep;
	///! Флаги управления интерпретацией
	FLAGS pragma;
	///! Генератор переменных :)
	N2VariableCreator maker;

	struct HANDLE_NAME {
		HANDLE_NAME():
			pModule(NULL)
		{}
		std_string nameHandle;
		WORD_N2 numberDevice;
		N2Module* pModule;
	};
	std::vector<HANDLE_NAME> vecHands;
	std::stack<HANDLE_NAME> stackHands;
	//HANDLE_NAME currentHandle;
	
	struct INTERNAL_TIMERS
		{
		INTERNAL_TIMERS():resol(0), use(false){}
		clock_t time_begin;
		int resol;
		bool use;
		} 
	Timers[11]; // // Таймеры
	
	/// Ф-ция обратного вызова
	int callBack(DataPack& data);

	/// Обработчик ошибки возвращённой из модуля устройств
	void onErrorHappened(DataPack* pPack, Response& resp);

public:	
	N2Processor();
	virtual ~N2Processor();

	//! Основная процедура обработки команды
	bool tick(/*Order* order*/);
	// Получить строку описания текущей команды
	//std_string GetStrCurrentCommand();
	//! Начальная инициализация процессора
	bool Initial(N2ModulesManager *pMM, N2Order *pOrder);
	//! Сброс процессора
	void ResetProcessor();
	//! Запрос - пуста ли очередь команд?
	bool EmptyQueue();
	//! Запрос - случилась ли фатальная ошибка?
	bool FatalError();
	//! Обёртка для ф-ции обратного вызова
	static int WrapperCallBack(void* pFmc, DataPack& data);
	//! Получить менеджер переменных
	N2VariablesManager* getManVar(void) {return &manVars;}
	//! Исполнение команды вне очереди
	bool inject(DataPack* pack);
	
protected:
	//! текущий узел
	//NodeTree* current_node;
	DataPack* current_command_in_proccess;
	USID cur_USID;
	//! 
	unsigned short regA;
	int regC;
		
	// Ф-ции обработки поступающих команд
	// Возврат: 
	//		true - требуется инкремент указателя стека команд
	//		false - команда не изменяет положение указателя команд
	bool SelfExec(DataPack* tc);

private:

	void OnProcedureProcessError(std_string message, SIGN sign, bool fatal);
	void consoleMessage(std_string msg, UINT_N2 typeMsg);
};


