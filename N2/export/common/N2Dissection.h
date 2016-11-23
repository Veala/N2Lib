// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Dissection.h
///
///	\brief 		Преобразователь XMLF-формата в байт-код (пакет команд)
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

#include "N2XMLF.h"
#include "N2Commands.h"
#include "N2Parser.h"

using namespace N2_Defines;



/// Обобщенный класс - преобразователь
class N2Dissection
{
protected:
	// данные секции protected нужны для разбора макросов
	static N2Parser* pParser_;
	static VectorCommand* pVecComm_;
	// 
	//
	virtual bool 
		unpack(CFS* pCFS);
public:

	enum RESULT_DECODE {
		SUCCESSFUL,
		ERROR,
		NOT_FOUND
	};

	N2Dissection() {};

	static void setParser(N2Parser* pParser) {
		pParser_ = pParser;
	}
	
	static void setOrder(VectorCommand* pOrder) {
		pVecComm_ = pOrder;
	}

	static N2Parser* getParser() {
		return pParser_;
	}

	static VectorCommand* getOrder() {
		return pVecComm_;
	}



	
	virtual RESULT_DECODE
		decode(XMLF* px, vector<DataPack>& pack) = 0;
};

/// Класс внутреннего (постоянно определенного) преобразования
/// В основном это команды модулю процессора
class N2DissInternal : public N2Dissection
{
	bool checkType(std_string type, TYPE_VAR& tv);

public:
		
	virtual RESULT_DECODE
		decode(XMLF* px, vector<DataPack>& pack);
};


/// Рабочий класс преобразования
/// Используется только в N2
class N2DissTotal  : public N2Dissection
{
	N2DissInternal inter_;
	std::vector<N2Dissection*> vecExpand_;

	RESULT_DECODE
		decode(XMLF* px, vector<DataPack>& pack);

public:
	N2DissTotal();
	~N2DissTotal();

	void passParser(N2Parser* pParser) {
		N2Dissection::setParser(pParser);
	}

	virtual bool 
		unpackWhole(CFS* pCFS, VectorCommand* vecComm);

	bool 
		addDissector(N2Dissection* pDiss);

	void
		resetExternalDissectors(void);

};
