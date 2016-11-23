// -*- mode:c++; coding:utf-8; -*-
///
/// \file		 N2VariableSimplex.h
///
///	\brief 		Модуль унифицированных переменныx
/// \details	Определяет "шаблонный" тип динамической переменной,
///				описывает класс управления переменными.
///				Так же специализирует основные типы данных.
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А., Лызлов В.Е.
///
/// \date 		28.04.2014
/// \version 	0.1
///  
///  История изменений:
///  28.08.14	изменен интерфейс динамической переменной

#pragma once

#include "N2Defines.h"
#include <vector>
#include "N2Base.h"
#include "N2LiveObjectsPolicy.h"

using namespace std;
using namespace N2_Defines;

//class N2VariableCreator;

enum N2_ERRORS_OPCODES {
	N2EC_SUCCESS = 0,
	N2EC_INAPPLICABLE_CODE = 1, // неприменимый код
	N2EC_BAD_OPERAND_TYPE = 2, 
	N2EC_NULL_OPERAND = 3,
	N2EC_EMPTY = 4 // ф-ция не выполнила действие
};

struct N2_ERRORS_OPCODES_DESCRIPTION {
	N2_ERRORS_OPCODES code;
	std_string description;
};

static N2_ERRORS_OPCODES_DESCRIPTION N2ERR_Definitions [] = 
{
	{N2EC_SUCCESS, CT("без ошибок")}, 
	{N2EC_INAPPLICABLE_CODE, CT("неприменимый к операнду код")}
};

/// Базовый класс динамической переменной
class N2BaseVariable : public N2Base
{
protected:
	/// тип переменной
	const TYPE_VAR type_;
	/// имя переменной
	std_string name_;
	/// вид типа переменной
	const KIND_TYPE kind_;

	explicit N2BaseVariable(const TYPE_VAR type, const KIND_TYPE kind):
		type_(type),
		kind_(kind)
	{}
	explicit N2BaseVariable(const TYPE_VAR type, const KIND_TYPE kind, std_string name):
		type_(type),
		kind_(kind),
		name_(name)
	{}
public:
	///! Получить имя переменной
	/// \return имя переменной
	virtual std_string name(void);
	///! Получить тип переменной
	/// \return тип переменной 
	virtual TYPE_VAR type(void);
	///! Переименовать переменную
	/// \param newName новое имя переменной
	/// \return старое имя
	virtual std_string rename(std_string newName);
	///! ??? для комплексного типа
	virtual bool add(N2BaseVariable* addVar);
	///!
	virtual bool set(N2BaseVariable* , INDEX index = 0) = 0;
	///! Размер массива данных
	/// \return число элементов данных заданного типа в переменной
	virtual const COUNT dimension(void);
	/// Создать копию объекта в динамической памяти
	virtual N2BaseVariable* clone(void) = 0;
	/// 
	virtual N2_ERRORS_OPCODES 
		operation(N2_OPERATING_CODE code, N2BaseVariable* op2 = NULL, N2BaseVariable* res = NULL);
	///
	//virtual N2BaseVariable* toType(TYPE_VAR ) = 0;
	///
	/// Установить значение переменной из другой переменной.
	virtual bool setVoid(void* pVal, INDEX index = 0) = 0;
	///
	virtual bool compare(N2_COMPARE_CODES code, N2BaseVariable* pVar) = 0;
	///
	KIND_TYPE kind(void);
	///
	virtual void* getVoid(INDEX index = 0);
};


class N2VariableCreator
{

public:

    N2BaseVariable*
        createSimplex(TYPE_VAR type, std_string name = EMPTY_STR, int cnt = 1);


    N2BaseVariable*
        createComplex(std_string name)
    {
        return NULL; // new N2VariableComplex(name);
    }

    //

    N2BaseVariable*
        createTable(TYPE_VAR el_type, std_string name, int rows, int columns);

    int
        getIntFromSimplexVar(N2BaseVariable* pVar);
};



/// @class Шаблонный класс динамической переменной, 
/// для создания простых переменных произвольного типа.
template <class T >
class N2VariableSimplex : public N2BaseVariable
{
	friend N2VariableCreator;

protected:
	T* value_;
	COUNT count_;
	/// Выделить в динамической памяти место под значение переменной
	virtual void create(std_string name, COUNT count = 1);
	/// Конструктор копирования ????	
	N2VariableSimplex(const N2VariableSimplex<T> & copy);
	/// Конструктор с созданием элемента переменной
	N2VariableSimplex(const TYPE_VAR typeName, std_string name, COUNT numElements = 1);

public :

	/// Деструктор
	virtual ~N2VariableSimplex();

	/// Установить значение переменной
	/// \param value устанавливаемое значение
	/// \param index индекс элемента (если массив)
	/// \return true - установлено, false - нет
	virtual bool set(T& value, INDEX index = 0);

	/// Установить значение переменной из другой переменной.
	/// Если необходимо производится преобразование к требуемому типу переменной.
	/// (Не применимо к массивам).
	/// \param pVar переменная из которой копируется значение
	/// \param index - идекс значения в который записывается значение
	/// \return true - установлено, false - нет
	virtual bool set(N2BaseVariable* pVar, INDEX index = 0);

	/// Установить значение переменной из другой переменной.
	virtual bool setVoid(void* pVal, INDEX index = 0);

	/// Получить указатель на значение переменной
	/// (начало счёта с 0).
	/// \param index индекс элемента (если массив)
	/// \return указатель на значение переменной
	virtual T* get(INDEX index = 0);

	/// Получить значение переменной
	/// (начало счёта с 0).
	/// \param index индекс элемента (если массив)
	/// \return значение переменной
	virtual T getValue(INDEX index = 0);

	/// Получить размерность массива переменной
	/// \return размер массива
	virtual const COUNT dimension(void);

	/// Оператор получения значения массива
	/// \param index индекс элемента (если массив)
	/// \return ссылка на значение переменной
	virtual  T& operator [] (int index);
	
	/// Привести тип внешней переменной к типу данной переменной
	/// \param pVar приводимая переменная
	/// \return значение данного типа
	virtual T custom(N2BaseVariable* pVar) = 0;

	/// Сравнить две переменные, текущую и передаваемую в параметре pVar.
	/// \param code код сравнения одно из значений типа N2_COMPARE_CODES
	/// \param Var сравниваемая переменная
	/// \return true - выражение истинно, false - нет
	virtual bool compare(N2_COMPARE_CODES code, N2BaseVariable* pVar);

	//virtual N2BaseVariable* toType(TYPE_VAR type);
	
	virtual void* getVoid(INDEX index = 0);
};


/// Класс переменной типа int.
class N2VariableINT : public N2VariableSimplex <int>
{
	friend N2VariableCreator;
protected:
	N2VariableINT():N2VariableSimplex<int>(VAR_INT, EMPTY_STR, 1){}
	N2VariableINT(std_string name, COUNT numElements = 1):N2VariableSimplex(VAR_INT, name, numElements){}
public:	
	virtual N2BaseVariable* clone(void) ;
	virtual N2_ERRORS_OPCODES 
		operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res);
	virtual int custom(N2BaseVariable* pVar);
	//virtual bool compare(N2_COMPARE_CODES code,N2BaseVariable* pVar);
};

/// Класс переменной типа long
class N2VariableLONG : public N2VariableSimplex <long>
{
	friend N2VariableCreator;
protected:
	N2VariableLONG():N2VariableSimplex(VAR_LONG, EMPTY_STR, 1){}
	N2VariableLONG(std_string name, COUNT numElements = 1):N2VariableSimplex(VAR_LONG, name, numElements){}
public:	
	virtual N2BaseVariable* clone();
	virtual N2_ERRORS_OPCODES 
		operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res);
	virtual long custom(N2BaseVariable* pVar);
};

/// Класс переменной типа bool
class N2VariableBOOL : public N2VariableSimplex <bool>
{
	friend N2VariableCreator;
protected:
	N2VariableBOOL():N2VariableSimplex(VAR_BOOL, EMPTY_STR, 1){}
	N2VariableBOOL(std_string name, COUNT numElements = 1):N2VariableSimplex(VAR_BOOL, name, numElements){}
public:	
	virtual N2BaseVariable* clone();
	virtual N2_ERRORS_OPCODES 
		operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res);
	virtual bool custom(N2BaseVariable* pVar);
};

/// Класс переменной типа
class N2VariableSTR : public N2VariableSimplex <std_string>
{
	friend N2VariableCreator;
protected:
	N2VariableSTR():N2VariableSimplex(VAR_STRING, EMPTY_STR, 1){}
	N2VariableSTR(std_string name, COUNT numElements = 1):
		N2VariableSimplex(VAR_STRING, name, numElements)
	{}
public:	
	virtual N2BaseVariable* clone();
	virtual N2_ERRORS_OPCODES 
		operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res);
	virtual std_string custom(N2BaseVariable* pVar);
};

/// Класс переменной типа float
class N2VariableFLOAT : public N2VariableSimplex <float>
{
	friend N2VariableCreator;
protected:
	N2VariableFLOAT():N2VariableSimplex(VAR_FLOAT, EMPTY_STR, 1){}
	N2VariableFLOAT(std_string name, COUNT numElements = 1):N2VariableSimplex(VAR_FLOAT, name, numElements){}
public:	
	virtual N2BaseVariable* clone();
	virtual N2_ERRORS_OPCODES 
		operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res);
	virtual float custom(N2BaseVariable* pVar);
};

/// Класс переменной типа TernOp
class N2VariableTO : public N2VariableSimplex <TERNAR>
{
	friend N2VariableCreator;
protected:
	N2VariableTO():N2VariableSimplex(VAR_TERNAR, EMPTY_STR, 1){}
	N2VariableTO(std_string name, COUNT numElements = 1):N2VariableSimplex(VAR_TERNAR, name, numElements){}
public:	
	virtual N2BaseVariable* clone();
	virtual N2_ERRORS_OPCODES 
		operation(N2_OPERATING_CODE code, N2BaseVariable* op2, N2BaseVariable* res);
	virtual TERNAR custom(N2BaseVariable* pVar);
};

/// Шаблонный класс табличных данных 
template <class T>
class N2Table
{
protected:
	/// количество строк таблицы
	INDEX rows_; 
	/// количество столбцов таблицы
	INDEX columns_;
	/// указатель на таблицу
	T* tbl_;

public:
	/// Конструктор
	explicit N2Table(int rows, int columns);

	/// Деструктор
	~N2Table();

	/// Установить значение ячейки таблицы
	/// \param row строка таблицы
	/// \param column колонка таблицы
	/// \param value устанавливаемое значение
	/// \return true - установлено, false - нет
	bool set(INDEX row, INDEX column, T value);

	/// Получить значение ячейки таблицы
	/// \param row строка таблицы
	/// \param column колонка таблицы
	/// \return значение ячейки
	T get(INDEX row, INDEX column);

	/// Число строк в таблице
	/// \return число строк
	SIZE_N2 rows(void);

	/// Число столбцов в таблице
	/// \return число столбцов
	SIZE_N2 columns(void);


	bool fill(T value);
};

typedef N2Table<int> N2TaInt;

/// Базовый абстрактный класс переменной типа Таблица
class N2BaseVariableTable : public  N2BaseVariable
{
protected:
	TYPE_VAR typeElement_;
	N2BaseVariableTable(std_string name, int rows, int columns, const TYPE_VAR typeElements):
		N2BaseVariable(VAR_TABLE, KT_TABLE, name),
		typeElement_(typeElements)
		{}
public:
	virtual N2BaseVariable* clone() = 0;
	TYPE_VAR getTypeElement() {return typeElement_;}
	virtual int rowCount() = 0;
	virtual int columnCount() = 0;
	/// Установить значение переменной из другой переменной.
	virtual bool setVoid(void* pVal, INDEX index = 0) {return false;}
	///
	virtual bool compare(N2_COMPARE_CODES code, N2BaseVariable* pVar) 
	{return false;}
	///
	virtual bool moveVariableToCell(int row, int column, N2BaseVariable* pVar) = 0;

	virtual bool moveCellToVariable(int row, int column, N2BaseVariable* pVar) = 0;

	virtual bool fill(N2BaseVariable* val) = 0;
};

class N2VariableCreator;

/// "Рабочий" шаблонный класс таблицы
template <class T>
class N2VariableTABLE : public  N2BaseVariableTable
{
protected:
	N2VariableTABLE(std_string name, int rows, int columns, const TYPE_VAR typeElements):
		N2BaseVariableTable(name, rows, columns, typeElements),
		tbl(rows, columns)
		{}
public:
	N2Table<T> tbl;
    virtual bool set(N2BaseVariable*, INDEX index = 0 ) {return false;}
	virtual N2BaseVariable* clone(); // {return new N2VariableTABLE<T>(name(), tbl.rows(), tbl.columns(), typeElement_);}

	virtual int rowCount() { return tbl.rows(); }
	virtual int columnCount() { return tbl.columns(); }

	virtual bool moveVariableToCell(int row, int column, N2BaseVariable* pVar){
		if(pVar->kind() != KT_SIMPLEX)
			return false;
		N2VariableCreator maker;
		N2BaseVariable* pTemp = maker.createSimplex(getTypeElement());
		pTemp->set(pVar);
		return tbl.set(row, column, ((N2VariableSimplex<T>*)(pTemp))->getValue());
	}

	virtual bool moveCellToVariable(int row, int column, N2BaseVariable* pVar) {
		if(pVar->kind() != KT_SIMPLEX)
			return false;
		T val = tbl.get(row, column);
		N2VariableCreator maker;
		N2BaseVariable* pTemp = maker.createSimplex(getTypeElement());
		pTemp->setVoid(&val);
		return pVar->set(pTemp);
	}

	virtual bool fill(N2BaseVariable* val) {
		if(!val)
			return false;
		N2VariableCreator maker;
		N2BaseVariable* pTemp = maker.createSimplex(getTypeElement());
		pTemp->set(val);
		tbl.fill(((N2VariableSimplex<T>*)(pTemp))->getValue());
		return true;
	}
};


/// Таблица с элементом ячейки типа int
class N2VariableIntTABLE : public N2VariableTABLE<int>
{
	friend N2VariableCreator;
protected:
	N2VariableIntTABLE(std_string name, int rows, int columns):
		N2VariableTABLE(name, rows, columns, VAR_INT)
	{}
};

/// Таблица с элементом ячейки типа float
class N2VariableFloatTABLE : public N2VariableTABLE<float>
{
	friend N2VariableCreator;
protected:
	N2VariableFloatTABLE(std_string name, int rows, int columns):
		N2VariableTABLE(name, rows, columns, VAR_FLOAT)
	{}
};

/// Таблица с элементом ячейки типа float
class N2VariableLongTABLE : public N2VariableTABLE<long>
{
	friend N2VariableCreator;
protected:
	N2VariableLongTABLE(std_string name, int rows, int columns):
		N2VariableTABLE(name, rows, columns, VAR_LONG)
	{}
};

/// Таблица с элементом ячейки типа std_string
class N2VariableStringTABLE : public N2VariableTABLE<std_string>
{
	friend N2VariableCreator;
protected:
	N2VariableStringTABLE(std_string name, int rows, int columns):
		N2VariableTABLE(name, rows, columns, VAR_STRING)
	{}
};

/// Таблица с элементом ячейки типа bool
class N2VariableBoolTABLE : public N2VariableTABLE<bool>
{
	friend N2VariableCreator;
protected:
	N2VariableBoolTABLE(std_string name, int rows, int columns):
		N2VariableTABLE(name, rows, columns, VAR_BOOL)
	{}
};

/// Таблица с элементом ячейки типа TERNAR
class N2VariableTernarTABLE : public N2VariableTABLE<TERNAR>
{
	friend N2VariableCreator;
protected:
	N2VariableTernarTABLE(std_string name, int rows, int columns):
		N2VariableTABLE(name, rows, columns, VAR_TERNAR)
	{}
};




/// Класс сложной переменной (В РАЗРАБОТКЕ)
class N2VariableComplex : public N2BaseVariable
{	
	vector<N2BaseVariable*> vecSimples;
	vector<N2VariableComplex*> vecComplex;

//	std_string cutPartName(std_string& name);
//	std_string clearName(std_string name);
//	INDEX parseIndex(std_string name);
//	N2BaseVariable* find(std_string name);

public:
	N2VariableComplex(std_string name):
		N2BaseVariable(VAR_COMPOSITE, KT_COMPLEX, name)
	{}
	virtual N2BaseVariable* clone(){return NULL;}//new N2VariableComplex(name());}

	/// Добавить в текущий контейнер переменную.
	/// \param pVar - указатель на добавляемую переменную
	/// \param index - индекс элемента данного объекта к которому добавляется переменная pVar
	/// \return возвращает true - при успешной операции, false - 
	bool add(N2BaseVariable* pVar); //, INDEX index = 0);
	bool add(N2VariableComplex* pVar);

	/// \param index - индекс элемента данного объекта, если он сложного типа, иначе игнорируется
	N2BaseVariable* findChild(std_string pureName);

	/// Получить переменную по её имени
	/// \param name - имя переменной, формируется по правилам языков C/C++
	/// (вложенность определяется точкой, элемент массива квадратными скобками с непосредственным значением)
	/// \return возвращает указатель на найденную переменную или NULL, если переменная
	/// не была найдена.
	N2BaseVariable* getNamed(std_string name);
};




/// Класс для создания объектов переменных разных типов
//class N2VariableCreator
//{
	
//public:
	
//	N2BaseVariable*
//		createSimplex(TYPE_VAR type, std_string name = EMPTY_STR, int cnt = 1);

	
//	N2BaseVariable*
//		createComplex(std_string name)
//	{
//		return NULL; // new N2VariableComplex(name);
//	}
	
//	//

//	N2BaseVariable*
//		createTable(TYPE_VAR el_type, std_string name, int rows, int columns);

//	int
//		getIntFromSimplexVar(N2BaseVariable* pVar);
//};
