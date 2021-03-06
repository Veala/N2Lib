// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Register.h
///
///	\brief 		Реестр библиотеки.
/// \details	Тут хранятся и создаются все необходимые объекты общего 
/// \details	использования.
/// \details	Реализован на основе паттерна Singleton.
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

#include "ITreeNode.h"
#include "N2Misc.h"
#include "N2Environment.h"
#include "N2Log.h"
#include "N2Modules.h"

enum PATH_FOR
{
//	TOTAL,
//	ROOT,
	DEVICE_LIBRARY,
	TASK_FIND
};

class N2Register   //: public N2Base
{
	//! Статический указатель на себя
	static N2Register* globalReg;
	//! 
	//N2MemoManager memManager;
	//!
	N2Register();
	N2Register(const N2Register& r);
	~N2Register();

	static void* pPrjTree_;

	N2Logbook* pLog_;
	N2ProjectSpecialInfo deviceInfo_;
	N2Environment* pEnv_; 
	N2Console* pConsole;
	OLS_Heap memoryAllocator;

public:

	//! Получение статического указателя на реестр
	static N2Register* self();

	//template <class T>
	//static
	//T* create(std_string name = std_string(), COUNT count = 1);
	//{
	//	return OLS_Heap::create<T>(name, dimension);
	//}
	//!
	//template <class T>
	//T* create(std_string name = std_string(), COUNT count = 1)
	//{
	//	T* ptr = NULL;
	//	if(count > 1)
	//		ptr = new T[count]();
	//	else
	//		ptr = new T();	
	//	if(N2Register::self()->getMemManager()->record) {
	//		N2Memo memo;
	//		memo.variableName = name;
	//		memo.operation = N2Memo::NEW_OP;
	//		memo.ptr = ptr;
	//		memo.sizeOfObject = sizeof(T);
	//		memo.number = count;
	//		// Нужно другое хранилище памяти для независимости
	//		N2Register::self()->getMemManager()->memory.push_back(memo);
	//	}
	//	return ptr;
	//}

	OLS_Heap* getMemoryAllocator(void);

//    static
//    void release(void* pObj);
//    {
//        OLS_Heap::release(pObj);
//    }

	//

	N2Environment*
	getEnvironment(void) 
	{
		return pEnv_;
	}

	static 
	bool 
	plantTree(void* root)
	{
		pPrjTree_ = root;
		return true;
	}

	static 
	//ITreeNode*
	void*
	getTree(void)
	{
		return pPrjTree_;
	}

	N2Logbook*
	log(void);

	N2ProjectSpecialInfo* 
		getDeviceInfo(void);
	
	void 
	addPath(std_string path, PATH_FOR pf);

	void 
	reset();
	
	//N2MemoManager* N2Register::getMemManager(void);

	//static
	//void setSerialize(N2BaseSerialize* pSerial)
	//{
	//	if(pSerial_)
	//		release<N2BaseSerialize>(pSerial);
	//	pSerial_ = pSerial;
	//}
};


