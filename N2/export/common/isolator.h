///////////////////////////////////////////////////////////
//
//  isolator.h
//
//	Наименование: Изоляция определений  	
//  Описание:	
//
//  Дата создания:  27.02.2014
//  Автор:			Чихичин Д.А.
//  
///////////////////////////////////////////////////////////
//  История изменений:
//  
//
///////////////////////////////////////////////////////////
#pragma once

#include <tuner.h>


// TOTAL DEFINES
#ifdef WIN32
	#define WINDOWS_BUILD
	#ifdef _MSC_VER
		#pragma warning( disable : 4635 ) 
		#pragma warning( disable : 4996 ) 
	#endif
#else
	#undef	WINDOWS_BUILD
#endif

// INCLUDErs
#ifdef WINDOWS_BUILD 
	#include <tchar.h>
#else
	//
#endif
#include <string>

typedef void*				PVOID_N2;
typedef unsigned	long	ULONG_N2;
typedef				long	LONG_N2;
typedef unsigned	int		UINT_N2;
typedef				int		INT_N2;
typedef unsigned	short	USHORT_N2;
typedef unsigned	short	WORD_N2;
typedef ULONG_N2			DWORD_N2;
typedef unsigned	char	BYTE_N2;
typedef				float	FLOAT_N2;
typedef	unsigned	long long UBIG_N2;
//
#if defined(LONG_MAX) && (LONG_MAX > 0x7FFFFFFFL)
typedef unsigned int        SIGN;
#else
typedef unsigned long       SIGN;
#endif

typedef DWORD_N2			BINT;
typedef UINT_N2				COUNT;
typedef size_t				INDEX;
typedef size_t				DIMENSION;
typedef INDEX				SIZE_N2;
typedef USHORT_N2			OPERATION_CODE;
typedef UINT_N2				FLAGS;


#ifdef WINDOWS_BUILD
	typedef int (__stdcall *PEXPROCEDURE)();
#else
	typedef int (__stdcall *PEXPROCEDURE)();
#endif;

#ifdef SET_UNICODE
	typedef std::wstring		std_string;
	typedef wchar_t				CHAR_N2;
	typedef const wchar_t		CCHAR_N2;
	typedef CHAR_N2				UCHAR_N2;	
	typedef wchar_t*			PCHAR_N2;
	typedef PCHAR_N2			PUCHAR_N2;
#else
	typedef std::string			std_string;
	typedef char				CHAR_N2;
	typedef const char			CCHAR_N2;
	typedef unsigned char		UCHAR_N2;
	typedef char*				PCHAR_N2;
	typedef unsigned char*		PUCHAR_N2;
#endif;

typedef std_string				USID; // Unique string ID

#ifdef WINDOWS_BUILD 
	#ifdef SET_UNICODE
		#define CT(x)	L##x
	#else
		#define CT(x)	x
	#endif
#else
	#define CT(x)	x
#endif

#define EMPTY_STR CT("")

#ifdef WINDOWS_BUILD 
	#define SLASH_STR CT("\\")
	#define ENDL_STR CT("\n")
#else
	#define SLASH_STR CT("/")
	#define ENDL_STR CT("\n")
#endif


// STDLIB definition
/// Определения функций стандартной библиотеки ф-ций С/С++ имеющие 
/// специфические наименования на разных платформах
#ifdef WINDOWS_BUILD
	#define std_fopen	_tfopen
	#define std_atoi	_ttoi
	#define std_snprintf	_snprintf
#else
	#define std_fopen	fopen
	#define std_atoi	atoi
#endif

