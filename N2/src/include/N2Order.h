// -*- mode:c++; coding:utf-8; -*-
///
/// \file		ITreeNode.h
///
///	\brief 		Интерфейс узла дерева
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

#include "../common/N2Base.h"
#include "../common/N2Commands.h"
#include <vector>
//#include "..\..\common\total.h"
//#include "..\..\common\DataPack.h"

using namespace std;
using namespace N2_Defines;

/// Очередь команд.
/// Задача переведенная в набор инструкций байт-кода с соответствующей таблицей переходов.
/// Класс активно взаимодействует с классом N2Processor по заранее определенному алгоритму.
class N2Order: public N2Base
{
		bool init;
	unsigned int ip;
	unsigned int size_programm;
	unsigned int jt_level;
	//

	/*** JUMP-таблица ***/
	// Элемент таблицы переходов
	typedef struct JMP_TABLE_ELEMENT
	{
	JMP_TABLE_ELEMENT():	cip(0), 
							id(N2IC_UNRECO), 
							level(0), 
							jmp(0), 
							circle(false), 
							active(true)
							{}
	unsigned int	cip;
	short			id;
	unsigned int	level;
	unsigned int	jmp;
	bool			circle; // закрывающая скобка принадлежит циклу?
	bool			active;
	} JmpTblElm;
	
	// Таблица переходов
	vector<JmpTblElm> jumpTable;
	/*** ***/

	/*** MARKS - таблица ***/
	// Элемент таблицы меток
	struct MARKS{
		std_string name;
		unsigned int jmpAddress;
	} tmpMark;

	// Таблица меток
	vector<MARKS> marksTable;
	/*** ***/

	// Добавить элемент в таблицу
	void AddToJT(DataPack& rtc, unsigned int ip);
	// Добавить метку
	void AddMark(DataPack& rtc, unsigned int ip);
	// Вычислить переходы
	bool CalcJumpTable(void);
	// Сбросить таблицу
	void ResetJT(void);
	// Сбросить метки
	void ResetMarks(void);
	//
	unsigned int FindEnd(unsigned int begin, int level);
	vector <DataPack> on_execution;
	vector <DataPack>::iterator CP; // указатель команд	

public:
	N2Order();
	virtual ~N2Order();


public:
	/// Сброс очереди
	void Reset();
	/// Добавить вектор команд (набор разобранных инструкций) в очередь
	bool AddCommandsInOrder(VectorCommand* vc);
	/// Взять текущую команду
	DataPack*  GetExecuteCommand();
	/// Инкремент указателя команд
	void IncCIP();
	/// Декремент указателя команд
	void DecCIP();
	/// Получить "адрес" текущей инструкции
	unsigned int GetCIP();
	/// Установить указатель на инструкцию данного "адреса"
	bool SetCIP(unsigned int cip);
	/// Переход на команду поля jmp в JUMP-таблице
	void JumpWithCurrent(void);
	/// Установлен ли флаг активности для текущей команды
	/// (действителен для команд циклических операторов)
	bool CurrentIsActive(void);
	/// Погасить флаг активности
	void ResetActivityOfCurrent(void);
	/// Установить флаг активности
	void SetActivityOfCurrent(void);	
	/// Получить длину очереди команд
	unsigned int GetSizeOrder(void) 
		{return size_programm;}
	/// Получить произвольную команду 
	const DataPack* GetAnyCommand(unsigned int cp) 
		{if(cp >= on_execution.size())
			return NULL;
		return &on_execution[cp];}
	
private:
	//int current_channel;
};
