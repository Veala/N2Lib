// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Commands.h
///
///	\brief 		Файл определений сигнатуры и форматов команд
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

#include "isolator.h"
#include "N2Defines.h"

namespace N2_Defines {


#define SET_NUMDEV_SIGN(sign, numDev) ((sign & (~N2_MASK_NUMDEV))|((numDev&N2_LMASK_NUMDEV)<<N2_SHIFT_MASK_NUMDEV)) 


typedef union Sign_
{
	Sign_():value(0){}

	struct SignInternParts1_
	{
		SIGN
			type    : 4,
			subtype : 8,
			numDev  : 8,
			code    : 12;
	} img1;
	struct SignInternParts2_
	{
		SIGN
			devClass : 12,
			numDev   : 8,
			code     : 12;
	} img2;
	SIGN value;

} Signature;




/// Класс сигнатуры команды
//class Signature
//{
//	SIGN _signature;
//
//public:
//	
//	Signature()
//		{_signature = 0;}
//	Signature(const SIGN &s)
//		{_signature = s;}
//	Signature& operator = (SIGN s)
//		{_signature = s;
//		return *this;}
//	Signature& operator = (Signature s)
//		{_signature = s.value();
//		return *this;}		
//	bool operator == (const Signature &s)
//		{return (_signature == s.value());};
//	//! Geters
//	/// Получить полную числовую сигнатуру
//	inline SIGN value() const
//		{return _signature;}
//	/// Получить тип устройства
//	SIGN type() const
//		{return TYPE_SIGN(_signature);}
//	/// Получить подтип устройства
//	SIGN subType() const
//		{return SUBTYPE_SIGN(_signature);}
//	/// Получить порядковый номер устройства
//	SIGN numberDevice() const
//		{return NUMDEV_SIGN(_signature);}	
//	/// Получить команду для устройства
//	SIGN command() const
//		{return COMMAND_SIGN(_signature );}
//	/// Получить класс устройства
//	SIGN classDevice() const
//		{return (_signature & N2_MASK_CLASS);}	
//	/// Команда групповая?
//	/// \return true - групповая , false - нет.
//	bool isBroadcast()
//		{return (numberDevice() == N2_LMASK_NUMDEV);}
//	/// Получить сигнатуру с "вырезанными" битами номера устройства
//	SIGN maskNumDevice()
//		{return (_signature & (~N2_MASK_NUMDEV));}
//	/// Получить сигнатуру с "вырезанной" командой устройства
//	SIGN maskCommand()
//		{return (_signature & (~N2_MASK_COMMAND));}
//	/// Получить сигнатуру с "вырезанными" битами класса устройства
//	SIGN maskDeviceClass()
//		{return (_signature & (~N2_MASK_CLASS));}	
//	//! Seters		
//	/// Установить сигнатуру
//	/// \param value - значение новой сигнатуры
//	void setValue(SIGN value)
//		{_signature = value;}
//	/// Установить номер устройства
//	/// \param value_id - новое значение номера
//	void setNumDevice(WORD_N2 value_id)
//		{_signature = maskNumDevice() | ((value_id & N2_LMASK_NUMDEV) << N2_SHIFT_MASK_NUMDEV);}
//	/// Установить команду для устройства
//	/// \param comm - новая команда
//	void setCommand(WORD_N2 comm)
//		{_signature = maskCommand() | ((comm & N2_LMASK_COMMAND) << N2_SHIFT_MASK_COMMAND);}
//	/// Установить класс устройства
//	/// \param classDev - новый класс устройства
//	void setClassDevice(WORD_N2 classDev) 
//		{_signature = maskDeviceClass() | ((classDev & N2_LMASK_CLASS) << N2_SHIFT_MASK_CLASS);}
//};


struct N2BaseFormatCommand;

/// Класс пакета данных.
/// Набор пакетов формирует очередь задачи для исполнения процессором.
class DataPack
{

public:		
	DataPack(): 
		pCmd(NULL),
		numPack(0),
		buffer(NULL),
		ret_value(0)
	{}
	/// Сигнатура пакета
	Signature signature;
	/// Номер пакета данных (нумерация начинается с 0)
	int numPack; 
	/// Символьное наименование команды
	std_string nameTag;
	/// Наименование пакета данных/ Строковые данные
	std_string namePack;	
	/// Строка описания ошибки
	std_string errorDescription;	
	/// Блок команды
	N2BaseFormatCommand* pCmd; 
	/// Блок данных
	void* buffer; 	
	/// Возвращаемое значение
	int ret_value; 

	~DataPack(){};
};


	enum ERRORS_ 
	{
		OK,
		ERR,
		FATAL_ERR,
		THROW_EXCEPTION,
		WARNING,
		CMD_HANDLER_NOT_FOUND
	};


struct Response_
{
	ERRORS_ err_;

	Response_() :
		err_(OK)
	{}
	Response_(ERRORS_ er):
		err_(er)
	{}

};

typedef Response_ Response;

/// Очередь команд или исполняемый "байт-код" задания
typedef vector<DataPack> VectorCommand;


enum TYPE_COMMAND_LABEL {
	N2_BFC_DEFAULT = 0x0A00,
	N2_BFC1 = 0x0A01,
	N2_BFC2 = 0x0A02,
	N2_BFCHIERARCHY = 0x0A03,
	//N2_BFCERROR = 0x0A04,
	N2_BFCDECL = 0x0A05,
	N2_BFCOPER = 0x0A06,
	N2_BFC3 = 0x0A07,
	N2_BFC_SPECIAL = 0x0A08,
	N2_BFC_DEVICEINFO = 0x0A09,
	N2_BFCDECL2 = 0x0A0A,
	N2_BFC_ARRAY_INT = 0x0A0B,
	N2_BFC_ARRAY_STRING = 0x0A0C,
	N2_BFC_ARRAY_MIX = 0x0A0D,
	N2_BFC_ARRAY_DUX = 0x0A0E,
	//
	N2_BFC_USER = 0x0AAA
};

//const UINT_N2 N2_BFCSPEC = 0x0A07;

struct N2BaseFormatCommand
{
	N2BaseFormatCommand(int init = N2_BFC_DEFAULT):
		label(init)
	{}
	int label; 
};


struct N2DeclareBFC : public N2BaseFormatCommand
{
	N2DeclareBFC():
		N2BaseFormatCommand(N2_BFCDECL)
	{}
	//
	TYPE_VAR type;
	COUNT size;
	std_string initVariable;
	std_string sizeStr;
};

struct N2DeclareBFC2 : public N2BaseFormatCommand
{
	N2DeclareBFC2():
		N2BaseFormatCommand(N2_BFCDECL2),
		s_row(),
		s_column()
	{}
	//
	TYPE_VAR type;
	INDEX row;
	INDEX column;
	std_string s_value;
	std_string s_row;
	std_string s_column;
};


struct N2OperationBFC : public N2BaseFormatCommand
{
	N2OperationBFC():
		N2BaseFormatCommand(N2_BFCOPER)
	{}
	//
	std_string op1;
	std_string op2;
	N2_OPERATING_CODE code;
	std_string opResult;
	TYPE_VAR type2;
};


struct N2HierarchyBFC : public N2BaseFormatCommand
{
	N2HierarchyBFC():
		N2BaseFormatCommand(N2_BFCHIERARCHY)
	{}
	//
	USID usid;
};


struct N2BFC1 : public N2BaseFormatCommand
{
	N2BFC1():
		N2BaseFormatCommand(N2_BFC1),
		codeCompare(N2COMPARE_UNDEFINE)
	{}
	
	std_string nameVariable1;
	std_string nameVariable2;
	N2_COMPARE_CODES codeCompare;
	

};

struct N2BFC2 : public N2BaseFormatCommand
{
	N2BFC2():
		N2BaseFormatCommand(N2_BFC2),
		dec(false)
	{}
	std_string s_var[3];
	INT_N2 i_var[3];
	bool dec;
};

struct N2BFC_ARRAY_INT : public N2BaseFormatCommand
{
private:
	vector<int> vs;
	
public:
	N2BFC_ARRAY_INT():
		N2BaseFormatCommand(N2_BFC_ARRAY_INT)
	{}	
	~N2BFC_ARRAY_INT() 
	{ vs.clear(); }

	const DIMENSION size(void) {return vs.size();}

	void add(int s) {vs.push_back(s);}

	int get(size_t index) {
		if(index >= size())
			return 0;
		return vs[index];
	}

	void reset(void) {vs.clear();}
};


struct N2BFC_ARRAY_STRING : public N2BaseFormatCommand
{
private:
	vector<std_string> vs;
	
public:
	N2BFC_ARRAY_STRING():
		N2BaseFormatCommand(N2_BFC_ARRAY_STRING)
	{}
	~N2BFC_ARRAY_STRING() 
	{ vs.clear(); }

	const DIMENSION size(void) {return vs.size();}

	void add(std_string s) {vs.push_back(s);}

	std_string get(size_t index) {
		if(index >= size())
			return std_string();
		return vs[index];
	}
};


struct N2BFC_ARRAY_MIX : public N2BaseFormatCommand
{
private:
	vector<std_string> vs;
	vector<int> vi;
public:
	enum MY_TYPE{
		INT,
		STR
	};
	N2BFC_ARRAY_MIX():
		N2BaseFormatCommand(N2_BFC_ARRAY_MIX)
	{}
	~N2BFC_ARRAY_MIX() 
	{ vi.clear(); vs.clear(); }

	const DIMENSION size(MY_TYPE type) {return (type == INT) ? vi.size() : vs.size();}

	void add(std_string s) {
		vs.push_back(s);
	}

	void add(int i) {
		vi.push_back(i);
	}

	std_string getStr(size_t index) {
		if(index >= size(STR))
			return std_string();
		return vs[index];
	}

	int getInt(size_t index) {
		if(index >= size(INT))
			return 0;
		return vi[index];
	}

};


struct N2BFC_ARRAY_DUX : public N2BaseFormatCommand
{
public:

	struct VAL {
		std_string sval;
		int ival;
	} value;

private:
	vector<VAL> vals;

public:


	N2BFC_ARRAY_DUX():
		N2BaseFormatCommand(N2_BFC_ARRAY_DUX)
	{}
	~N2BFC_ARRAY_DUX() 
	{ vals.clear(); }

	const DIMENSION size() {return vals.size();}

	void add(std_string s, int i) {
		value.sval = s;
		value.ival = i;
		vals.push_back(value);
	}

	void add(VAL v) {
		vals.push_back(v);
	}

	VAL* get(size_t index) {
		if(index >= size())
			return NULL;
		return &vals[index];
	}

	int getInt(size_t index) {
		if(index >= size())
			return 0;
		return vals[index].ival;
	}
	std_string getStr(size_t index) {
		if(index >= size())
			return "";
		return vals[index].sval;
	}

};

struct N2BFC3 : public N2BaseFormatCommand
{
	N2BFC3():
		N2BaseFormatCommand(N2_BFC3),
		val(0),
		sw(false)
	{}
	std_string var;
	INT_N2 val;
	bool sw;
};

struct N2BFC_SPECIAL : public N2BaseFormatCommand
{
	N2BFC_SPECIAL():
		N2BaseFormatCommand(N2_BFC_SPECIAL),
		ok(false),
		sign_in_out(0),
		modeFind(FD_AUTO)
	{}
	bool ok;
	SIGN sign_in_out;
	FINDER_DEVICE modeFind;
};


struct N2BFC_DEVICE_INFO : public N2BaseFormatCommand
{
	N2BFC_DEVICE_INFO():
		N2BaseFormatCommand(N2_BFC_DEVICEINFO)
	{}
	
	N2DevicesInfo infoDev;
};



} //N2_Defines
