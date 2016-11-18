// -*- mode:c++; coding:utf-8; -*-
///
/// \file		 N2LiveObjectsPolicy.h
///
///	\brief 		Стратегия (политика) управлением жизни объектов
/// \details	Определяет как объекты создаются, размножаются и удаляются
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		28.05.2014
/// \version 	0.1
///  
///  История изменений:
///  

#pragma once

#include "isolator.h"
#include "N2Misc.h"
//#include "N2Register.h"

using namespace std;




struct OLS_Heap_New
{
	template <class T>
	T* create(std_string name = "", COUNT count = 1)
	{
		T* ptr = NULL;
		if(count > 1)
			ptr = new T[count]();
		else
			ptr = new T();		
		return ptr;
	}

	void release(void* ptr)
	{
		delete [] ptr;
	}

};


struct OLS_HeapWithGarbage
{
	N2MemoManager memManager;

	template <class T>
	T* create(std_string name = "")
	{
		T* ptr = new T();
		if (memManager.record) {
			N2Memo memo;
			memo.variableName = name;
			memo.operation = N2Memo::NEW_OP;
			memo.ptr = ptr;
			memo.sizeOfObject = sizeof(T);
			memo.number = 1;
			// Нужно другое хранилище памяти для независимости
			memManager.memory.push_back(memo);
		}
		return ptr;
	}

	template <class T>
	T* createVar(std_string name = "", COUNT count = 1)
	{
		T* ptr = NULL;
		if (count > 1)
			ptr = new T[count]();
		else
			ptr = new T();
		if (memManager.record && ptr) {
			N2Memo memo;
			memo.variableName = name;
			memo.operation = N2Memo::NEW_OP;
			memo.ptr = ptr;
			memo.sizeOfObject = sizeof(T);
			memo.number = count;
			// Нужно другое хранилище памяти для независимости
			try {
				memManager.memory.push_back(memo);
			}
			catch(const std::exception& e) {
				return NULL;
			}
			catch(...) {
				return NULL;
			}
		}
		return ptr;
	}

void release(void* ptr)
{
	if (memManager.record) {
		N2Memo memo;
		memo.operation = N2Memo::DELETE_OP;
		memo.ptr = (void*)ptr;
		memManager.memory.push_back(memo);
	}
	if (!ptr)
		return;
	delete ptr;
	ptr = NULL;
};

template <class T>
void releaseVar( T* ptr, int count)
{
	if (memManager.record) {
		N2Memo memo;
		memo.operation = N2Memo::DELETE_OP;
		memo.ptr = ptr;
		memManager.memory.push_back(memo);
	}
	if (!ptr)
		return;
	if (count == 1)
		delete ptr;
	else
	    delete[] ptr;
	ptr = NULL;
};

};


//typedef OLS_Heap_New OLS_Heap; 
typedef OLS_HeapWithGarbage OLS_Heap; 