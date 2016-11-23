// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Defines.h
///
///	\brief 		Файл общих определений
/// \details	
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

#include <vector>
#include "isolator.h"

using namespace std;

namespace N2_Defines {

// Version
#define MainVersion 0
#define LowVersion  10

/// Active ID
const WORD_N2 N2_ACTIVE_DEVICE = 0xFE;
/// Команда для автоматического выбора первого свободного устройства как активного
const WORD_N2 N2_AUTO_ACTIVATE = 0xFF;

/// Типы устройств
const WORD_N2 N2_TYPE_PROGRAMM = 1;
const WORD_N2 N2_TYPE_MEASURER = 2;
const WORD_N2 N2_TYPE_GENERATOR = 3;
const WORD_N2 N2_TYPE_SWITCH = 4;
const WORD_N2 N2_TYPE_ZERO = 5;
const WORD_N2 N2_TYPE_CLIMAT_STATION = 6;
const WORD_N2 N2_TYPE_TESTERS = 7;
const WORD_N2 N2_TYPE_RECORDERS = 8;

/// Подтипы устройств
/// для типа N2_TYPE_PROGRAMM
const WORD_N2 N2_SUBTYPE_PROCESSOR = 1;
const WORD_N2 N2_SUBTYPE_CONSOLE = 2;
const WORD_N2 N2_SUBTYPE_DEBUGER = 3;
const WORD_N2 N2_SUBTYPE_SYSTEM = 4;
const WORD_N2 N2_SUBTYPE_ENVIRONMENT = 5;
const WORD_N2 N2_SUBTYPE_LOGGER_PRC = 6;
const WORD_N2 N2_SUBTYPE_INTERNAL_MODULE = 7;
/// для типа N2_TYPE_MEASURER
const WORD_N2 N2_SUBTYPE_MESUARE_SPECIAL = 7;
/// для типа N2_TYPE_TESTERS
const WORD_N2 N2_SUBTYPE_TESTERS_STANDART = 1;
const WORD_N2 N2_SUBTYPE_TESTERS_SPECIALIZE = 2;
/// для типа N2_TYPE_RECORDERS
const WORD_N2 N2_SUBTYPE_RECORDER_SOFT = 1;
const WORD_N2 N2_SUBTYPE_RECORDER_HARD = 2;
const WORD_N2 N2_SUBTYPE_RECORDER_SOFT_STANDART = 3;
const WORD_N2 N2_SUBTYPE_RECORDER_HARD_STANDART = 4;
// для типа N2_TYPE_ZERO
const WORD_N2 N2_SUBTYPE_IMITATOR = 1;

/// Маски
const SIGN N2_LMASK_TYPE = 0xF;
const SIGN N2_LMASK_SUBTYPE = 0xFF;
const SIGN N2_LMASK_CLASS = 0xFFF;
const SIGN N2_LMASK_NUMDEV = 0xFF;
const SIGN N2_LMASK_COMMAND = 0xFFF;
//
const BYTE_N2 N2_SHIFT_MASK_TYPE = 0;
const BYTE_N2 N2_SHIFT_MASK_SUBTYPE = 4;
const BYTE_N2 N2_SHIFT_MASK_CLASS = N2_SHIFT_MASK_TYPE;
const BYTE_N2 N2_SHIFT_MASK_NUMDEV = 12;
const BYTE_N2 N2_SHIFT_MASK_COMMAND = 20;
//
const SIGN N2_MASK_TYPE    = (N2_LMASK_TYPE << N2_SHIFT_MASK_TYPE);
const SIGN N2_MASK_SUBTYPE = (N2_LMASK_SUBTYPE << N2_SHIFT_MASK_SUBTYPE);
const SIGN N2_MASK_CLASS   = (N2_LMASK_CLASS << N2_SHIFT_MASK_CLASS);
const SIGN N2_MASK_NUMDEV  = (N2_LMASK_NUMDEV << N2_SHIFT_MASK_NUMDEV);
const SIGN N2_MASK_COMMAND = (N2_LMASK_COMMAND << N2_SHIFT_MASK_COMMAND);

/// Сигнатуры (и классы) программных устройств
const SIGN N2_PROCESSOR = (N2_TYPE_PROGRAMM | (N2_SUBTYPE_PROCESSOR << N2_SHIFT_MASK_SUBTYPE));
const SIGN N2_CONSOLE = (N2_TYPE_PROGRAMM | (N2_SUBTYPE_CONSOLE << N2_SHIFT_MASK_SUBTYPE));
const SIGN N2_DEBUGER = (N2_TYPE_PROGRAMM | (N2_SUBTYPE_DEBUGER << N2_SHIFT_MASK_SUBTYPE));
const SIGN N2_SYSTEM = (N2_TYPE_PROGRAMM | (N2_SUBTYPE_SYSTEM << N2_SHIFT_MASK_SUBTYPE));
const SIGN N2_ENVIRONMENT = (N2_TYPE_PROGRAMM | (N2_SUBTYPE_ENVIRONMENT << N2_SHIFT_MASK_SUBTYPE));
const SIGN N2_EXT_DEVICE_SPECIAL = 0;
const SIGN N2_PRC_LOG = (N2_TYPE_PROGRAMM | (N2_SUBTYPE_LOGGER_PRC << N2_SHIFT_MASK_SUBTYPE));
const SIGN N2_INTERNAL = (N2_TYPE_PROGRAMM | (N2_SUBTYPE_INTERNAL_MODULE << N2_SHIFT_MASK_SUBTYPE));


/************** КОДЫ КОМАНД ****************/
/// Коды собственных команд процессора
const UINT_N2 CMD_TASK = 1;
const UINT_N2 CMD_TASK_END = 2;
const UINT_N2 CMD_STEP = 3;
const UINT_N2 CMD_STEP_END = 4;
const UINT_N2 CMD_IF = 16;
const UINT_N2 CMD_ELSE = 17;
const UINT_N2 END_CMD = 19;
const UINT_N2 CMD_WHILE = 21;
const UINT_N2 CMD_VARIABLE = 24;
const UINT_N2 CMD_OPERATION = 25;
const UINT_N2 CMD_TABLE = 26;
const UINT_N2 CMD_TABULAR = 27;
const UINT_N2 CMD_FOR = 32;
const UINT_N2 CMD_COMPARE = 35;
const UINT_N2 CMD_BREAK = 38;
const UINT_N2 CMD_MARK = 39;
const UINT_N2 CMD_GOTO = 40;
const UINT_N2 CMD_EXECUTE = 54;
const UINT_N2 CMD_EXIT = 55;
const UINT_N2 CMD_TIMER = 56;
const UINT_N2 CMD_FORMAT_CONST = 58;
const UINT_N2 CMD_PRAGMA = 62;
const UINT_N2 CMD_CAST = 63;
const UINT_N2 CMD_OPEN_DEVICE = 66;
const UINT_N2 CMD_CLOSE_DEVICE = 67;
const UINT_N2 CMD_DEVICE = 68;
const UINT_N2 CMD_DEVICE_END = 69;
const UINT_N2 CMD_USE_GLOBAL = 70;
const UINT_N2 CMD_MACRO = 71;
const UINT_N2 END_MACRO = 72;
const UINT_N2 CMD_LOADED_MACRO = 73;
const UINT_N2 CMD_EMPTY = 74;
const UINT_N2 CMD_GFA = 75;
const UINT_N2 CMD_SET_GLOBAL = 76;
const UINT_N2 CMD_SET_GLOBAL_TABLE = 77;
const UINT_N2 CMD_STA = 78;
const UINT_N2 CMD_RIBBON_TO_ARRAY = 79;

/// Коды команд консоли
const UINT_N2 CMD_CON_WRITE = 3;
const UINT_N2 CMD_CON_SYNTAX_ERROR = 4;
const UINT_N2 CMD_CON_LOG = 5;
const UINT_N2 CMD_PROCESSOR_EVENT = 6;
const UINT_N2 CMD_CON_PROCESSOR_ERROR_FATAL = 7;
const UINT_N2 CMD_CON_PROCESSOR_WARNING = 8;
const UINT_N2 CMD_CON_DEBUG = 9;
const UINT_N2 CMD_CON_PROCESSOR_MODULE_ERROR = 10;

/// Тип вывода для CMD_CON_WRITE
enum TYPE_CON_WRITE
{
	TCW_GEN,
	TCW_TXT,
	TCW_VAR,
	TCW_VAL
};

// ...
const UINT_N2 CMD_CON_UP_BORDER = 0x100;
const UINT_N2 CMD_CON_USER = 0x101;

/// Буфер специальных обязательных команд модуля управления устройствами
/// Входящие команды
const UINT_N2 CMD_SPECIAL_BORDER = 4000;
const UINT_N2 CMD_SP_SELFTEST = 4001;
const UINT_N2 CMD_SP_SET_ACTIVE_SLOT = 4002;
const UINT_N2 CMD_SP_IS_FREE = 4003;
const UINT_N2 CMD_SP_OPEN = 4004;
const UINT_N2 CMD_SP_CLOSE = 4005;
const UINT_N2 CMD_SP_DEVICE_INFO = 4006;
const UINT_N2 CMD_SP_RESET = 4008;
//const UINT_N2 CMD_SP_BUILTINSTRUCTION = 4010;
const UINT_N2 CMD_SP_ENUMERATION = 4020;
/// Исходящие команды
const UINT_N2 CMD_SP_ROUTE = 4007;
//const UINT_N2 CMD_SP_GET_ACTIVE_SLOT = 4008;
const UINT_N2 CMD_SP_CALLBACK_FUNCTION = 4011;
//const UINT_N2 CMD_SP_GET_ENVIRONMENT_VAR = 4012;
const UINT_N2 CMD_SP_GET_VARIABLE = 4013;
const UINT_N2 CMD_SP_SET_VARIABLE = 4014;
//


///. Коды ошибок
const INT_N2 ERR_NOTHING = 0; /// без ошибок
const INT_N2 ERR_VARIABLE_DSNT_EXIST = 1; /// Переменная не существует


/// Специальные сигнатуры команд
const SIGN N2_COMMAND_START = ( (7 << N2_SHIFT_MASK_COMMAND) | N2_PROCESSOR);
const SIGN N2_COMMAND_STOP = ( (33 << N2_SHIFT_MASK_COMMAND) | N2_PROCESSOR);




#define MAKE_CODE(Command, deviceClass) ((Command << N2_SHIFT_MASK_COMMAND) | (deviceClass & N2_LMASK_CLASS))
#define MAKE_CLASS(Type, SubType) (Type | (Subtype << N2_SHIFT_MASK_SUBTYPE))
#define MAKE_SIGNATURE (Command, NumDevice, SubType, Type) ( Type | (Subtype << N2_SHIFT_MASK_SUBTYPE) | (NumDevice << N2_SHIFT_MASK_NUMDEV) | (Command << N2_SHIFT_MASK_COMMAND) )
#define TYPE_SIGN(Sign) (Sign & 0xF)
#define SUBTYPE_SIGN(Sign) ((Sign >> N2_SHIFT_MASK_SUBTYPE) & N2_LMASK_SUBTYPE)
#define NUMDEV_SIGN(Sign) ((Sign >> N2_SHIFT_MASK_NUMDEV) & N2_LMASK_NUMDEV)
#define COMMAND_SIGN(Sign) ((Sign >> N2_SHIFT_MASK_COMMAND) & N2_LMASK_COMMAND)
#define CLASS_SIGN(Sign) ((Sign >> N2_SHIFT_MASK_CLASS) & N2_LMASK_CLASS)


/// Безкодовые сигнатуры базовых устройств
#define SIGN_PROCC(code) MAKE_CODE(code, N2_PROCESSOR)
#define SIGN_CONSOLE(code) MAKE_CODE(code, N2_CONSOLE)

// Проверка соответствия
#define CHECK_CLASS(sign1, sign2)  (CLASS_SIGN(sign1) == CLASS_SIGN(sign2))

// 
#define YES	 1
#define NO	 0


enum ButtonSet 
	{
	BUTTONS_OK = 0x0000,
	BUTTONS_OKCANCEL = 0x0001,
	BUTTONS_ABORTRETRYIGNORE = 0x0002,
	BUTTONS_YESNOCANCEL = 0x0003,
	BUTTONS_YESNO = 0x0004,
	BUTTONS_RETRYCANCEL = 0x0005
	};


#define PRAGMA_ERROR_REDECLARE	1
#define PRAGMA_AUTOCASTING		2

enum N2Error 
	{
	ERR_NOERROR = 0,
	ERR_FILE_NOT_FOUND,
	ERR_FILE_PARSING
	};

enum KIND_TYPE
	{
	KT_UNDEFINE,
	KT_SIMPLEX,
	KT_TABLE,
	KT_COMPLEX
	};

enum TYPE_VAR
	{
	VAR_UNDEFINED,
	VAR_INT = 1,
	VAR_FLOAT = 2,
	VAR_LONG = 3,
	VAR_STRING = 4,
	VAR_BOOL = 5,
	VAR_COMPOSITE = 6,
	VAR_TABLE = 7,
	VAR_TERNAR = 8
	};

/// Тернарный тип (расширение булевского)
enum TERNAR {
	TERNAR_YES = 1,
	TERNAR_NO = 0,
	TERNAR_DISABLE = 2
};

enum RETURN_ON_LOAD_TASK
	{
	ROLP_OK,					// ������ ������� ��������
	ROLP_ERR_FILE_LOAD,
	ROLP_ERR_PARSE,
	ROLP_ERR_BYTECODER,
	ROLP_ERR_EXCEPTION,			// ����������� ����������
    ROLP_ERR_INTERNAL           // ���������� ������
	};


enum STATE_TASK
	{
    RST_UNDEFINED,
	RST_READY,				   	// ������ ������ � �������
	RST_PAUSE,
	RST_RUN,
	RST_ERR_CONDITION,
    RST_ERR_CRITICAL,		   	// ������ �����������
	RST_ERR_WARNING,			// ��������������
    RST_ERR_INTERNAL            // ���������� ������
	};

/// Рабочие режимы управляющего объекта
enum OPERATING_MODE
	{
	MODE_UNDEFINE,
    MODE_IDLE,
	MODE_MANUAL,
	MODE_AUTO,
	MODE_DEBUG
};


enum N2_INSTRUCTION_CODES 
{
	N2IC_UNRECO = 0,
	N2IC_FOR   = CMD_FOR,
	N2IC_WHILE = CMD_WHILE,
	N2IC_IF	= CMD_IF,
	N2IC_ELSE	= CMD_ELSE,
	N2IC_BREAK = CMD_BREAK,
	N2IC_END	= END_CMD,
	N2IC_MARK = CMD_MARK,
	N2IC_GOTO = CMD_GOTO
};

enum N2_OPERATING_CODE
{
	N2OC_DEC			= 1,	//	Декремент
	N2OC_INC			= 2,	//	Инкремент
	N2OC_INIT			= 3,	//	Инициализация (присвоение значения)
	N2OC_PLUS			= 4,	//	Прибавить
	N2OC_MINUS			= 5,	//	Отнять
	N2OC_DIV			= 6,	//	Деление
	N2OC_AND			= 7,	//	Логическое И
	N2OC_OR				= 8,	//	Логическое ИЛИ
	N2OC_XOR			= 9,	//	Исключающее ИЛИ
	N2OC_LOG_10			= 10,	
	N2OC_LOG			= 11,	
	N2OC_MULT			= 12,	 //	Умножение
	N2OC_SHIFT_LEFT		= 13,	 //	Двоичный сдвиг влево
	N2OC_SHIFT_RIGTH	= 14,	 //	Двоичный сдвиг вправо
	N2OC_MIN			= 15,	 //	Минимум двух значений
	N2OC_MAX			= 16,	 //	Максимум двух значений
	N2OC_MOD			= 17,	 //	Деление по модулю
	N2OC_NOT			= 18,	 //	Логическое НЕ
	N2OC_LN				= N2OC_LOG	 // Натуральный логарифм
};

enum N2_TABLE_OPERATING_CODE
{
	N2TOC_SET_CELL			= 1,	//	Установить значение в ячейку
	N2TOC_GET_CELL			= 2,	//	Взять значение из ячейки
};


enum N2_COMPARE_CODES 
{
	N2COMPARE_UNDEFINE = 0,
	N2COMPARE_EQU  = 20,
	N2COMPARE_GR   = 21,
	N2COMPARE_LS   = 22,
	N2COMPARE_GREQ = 23,
	N2COMPARE_LSEQ = 24,
	N2COMPARE_NEQ  = 25
};

// ����� ������������ ������
#define SIGN_PASSWORD				0x88DB0406


enum STATE_LAUNCHER {
	SL_NOT_INITIAL,
	SL_FREE,
	SL_BUZY,
	SL_CRASH
};

enum FINDER_DEVICE {
	FD_AUTO = 0,
	FD_MANUAL = 1
};

enum INTEGER_FORMAT_VIEW {
	IFV_DEC = 0,
	IFV_HEX = 1,	
	IFV_BIN = 2
};


/// Информация о реальном устройстве
struct N2DevicesInfo 
{
	struct DEV_INFO {
		std_string deviceClass;
		//INDEX real_index;
		INDEX libModule_index;
		std_string name;
		std_string model;
		std_string special;
		bool active;
		bool busy;
	} devInfo;

	std::vector<DEV_INFO> infos;

	void clear() {
		infos.clear();
		devInfo.deviceClass = EMPTY_STR;
	}
};


// ���������� ��������
//template <class T, int _size = 1 > 
//class ResourceAllocator {
//	T *pT;
//	class RARangeError {};
//	ResourceAllocator() {
//		pT = new T[_size];
//	};
//	~ResourceAllocator() {
//		delete [] pT;
//	};
//	T& operator[] (int i) throw(RARangeError) {
//		if(i >= 0 && i < _size)
//			return pT[i];
//		throw RARangeError;
//	}
//	T* operator -> () {
//		return pT;
//	};
//	int size() {
//		return _size;
//	};
//};


} // namespace N2_Defines
