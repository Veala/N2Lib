// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Order.cpp
///
///	\brief 		Очередь команд.
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

#include "include/N2Order.h"
//#include "include/N2Register.h"


N2Order::N2Order()
{
	ip = 0;
	init = false;
	jt_level = 0;
	size_programm = 0;
}


N2Order::~N2Order()
{

}


bool N2Order::AddCommandsInOrder(VectorCommand* vc)
{
	bool ret_val = true;

	if(init) 
			return false;
	on_execution.clear();
	
	// заголовок
	DataPack temp;
	temp.signature.value = N2_COMMAND_START;
	temp.nameTag = CT("_START_");
	temp.namePack = CT("Заголовок очереди команд");
	on_execution.push_back(temp);

	ResetJT();
	for(unsigned int i=0; i<vc->size(); i++) {
		DataPack tc;
		tc = (*vc)[i];
		AddToJT(tc, i + 1); // добавление в общую таблицу переходов
		AddMark(tc, i + 1); // добавление в таблицу меток
		on_execution.push_back(tc);
	}
	CalcJumpTable();
	
	temp.signature.value = N2_COMMAND_STOP; // команда остановки процессора
	temp.nameTag = CT("_END_");
	temp.namePack = CT("Конец очереди команд");
	on_execution.push_back(temp);
	
	CP = on_execution.begin();
	size_programm = on_execution.size();
	ip = 0;
	init = true;
	

	return ret_val;
}



/*
* функция на исполнение для Processor
* выдает команду в соответствии с указателем команд - cur_index
*/
DataPack* N2Order::GetExecuteCommand()
{
	if(ip >= size_programm)
			return &on_execution[size_programm - 1];
	
	return	&on_execution[ip];
}


void N2Order::IncCIP(void)
{
	if(!init)
			return;
	
	if((ip + 1) >= size_programm)
			return;
	ip++;
}

void N2Order::DecCIP()
{
	if(!init)
			return;
	
	if((ip - 1) >= size_programm)
			return;
	ip--;	
}

//! Получить "адрес" текущей инструкции
unsigned int N2Order::GetCIP()
{
	return ip;	
}

//! Исполнить инструкцию с данного "адреса"
bool N2Order::SetCIP(unsigned int cip)
{
	if(cip >= size_programm)
			return false;
	ip = cip;

	return true;
}


void N2Order::Reset()
{
	on_execution.clear();
	init = false;
}

//
void N2Order::AddToJT(DataPack& rtc, unsigned int ip)
{
	if(rtc.signature.img2.devClass != N2_PROCESSOR) return;
	switch(rtc.signature.img2.code)
		{
		case N2IC_FOR:   
		case N2IC_WHILE: 
		case N2IC_IF:
		case N2IC_ELSE:	
		case N2IC_BREAK: 
		case N2IC_END:	 break;
		default: return;
		}

	JmpTblElm te;
	te.cip = ip;
	te.id = (short)rtc.signature.img1.code;
	if(rtc.signature.img1.code == N2IC_END)
		{
		te.level = jt_level;
		jt_level --;
		}
	else if(rtc.signature.img1.code == N2IC_BREAK)
		{
		te.level = jt_level;
		}		
	else
		{
		jt_level ++;
		te.level = jt_level;
		}
	te.jmp = ip + 1;
		
	jumpTable.push_back(te);
}


void N2Order::AddMark(DataPack& rtc, unsigned int ip)
{
	if(rtc.signature.img1.code == N2IC_MARK) {
		tmpMark.name = rtc.namePack;
		tmpMark.jmpAddress = ip;
		marksTable.push_back(tmpMark);
	}
	else if(rtc.signature.img1.code == N2IC_GOTO) {
		vector<MARKS>::iterator it;
		for(it=marksTable.begin(); it!=marksTable.end(); it++) {
			if((*it).name == rtc.namePack) {
				rtc.ret_value = (*it).jmpAddress;
				return;
			}
		}
		throw CT("ERROR");
	}

}
void N2Order::ResetMarks(void)
{
	marksTable.clear();
}

//
bool N2Order::CalcJumpTable()
{
	unsigned int end = 0;
	for(size_t i=0; i<jumpTable.size(); i++)
		{
		switch(jumpTable[i].id)
			{
			case N2IC_FOR:  
			case N2IC_WHILE:
				{
				end = FindEnd(i+1, jumpTable[i].level);
				if(end == 0) return false;
				jumpTable[i].jmp = jumpTable[end].cip + 1;
				jumpTable[end].jmp = jumpTable[i].cip;
				jumpTable[end].circle = true;
				} break; 			
			case N2IC_IF:
				{
				int endelse = 0;
				end = FindEnd(i+1, jumpTable[i].level);
				if(end == 0) return false;
				if((end + 1) < jumpTable.size() && jumpTable[end + 1].id == N2IC_ELSE)
					{
					endelse = FindEnd(end+1, jumpTable[i].level);
					jumpTable[i].jmp = jumpTable[end + 1].cip;
					jumpTable[end].jmp = jumpTable[endelse].jmp;
					}
				else
					jumpTable[i].jmp = jumpTable[end].cip + 1;				
				} break;
			case N2IC_ELSE:	
				{
				end = FindEnd(i+1, jumpTable[i].level);
				if(end == 0) return false;
				jumpTable[i].jmp = jumpTable[end].cip + 1;			
				}
				break;
			case N2IC_BREAK: 
				{
				int level = jumpTable[i].level;
				while(1)
					{
					end = FindEnd(i+1, level);
					if(end == 0) return false;
					if(jumpTable[end].circle)
						{
						jumpTable[i].jmp = jumpTable[end].cip + 1;
						break;
						}
					if(level <= 1) return false;
					level --;
					}
				}
			case N2IC_END:	 break;
			default: return false;
			}
		}
	return true;
}

//
void N2Order::ResetJT(void)
{
	jumpTable.clear();
	jt_level = 0;
}

unsigned int N2Order::FindEnd(unsigned int begin, int level)
{
	for(size_t i=begin; i<jumpTable.size(); i++)
		if(jumpTable[i].id == N2IC_END &&
			jumpTable[i].level == level)
					return i;
	return 0;
}

void N2Order::JumpWithCurrent(void)
{
	for(size_t i=0; i<jumpTable.size(); i++)
		if(jumpTable[i].cip == ip)	
			{
			SetCIP(jumpTable[i].jmp);
			return;
			}
	IncCIP();
}

bool N2Order::CurrentIsActive(void)
{
	if(ip >= size_programm)
			return false;

	for(size_t i=0; i<jumpTable.size(); i++)
		if(jumpTable[i].cip == ip)	
			{
			if(jumpTable[i].active)
					return true;
			else
					return false;
			}
	
	return false;
}

void N2Order::ResetActivityOfCurrent(void)
{
	if(ip >= size_programm)
			return;

	for(size_t i=0; i<jumpTable.size(); i++)
		if(jumpTable[i].cip == ip)	
			jumpTable[i].active = false;

	return;
}

void N2Order::SetActivityOfCurrent(void)
{
	if(ip >= size_programm)
			return;

	for(size_t i=0; i<jumpTable.size(); i++)
		if(jumpTable[i].cip == ip)	
			jumpTable[i].active = true;

	return;
}