// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2DllSharedAccess.h
///
///	\brief 		
/// \details	
///
/// \copyright  
/// \author 	
///
/// \date 		28.04.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#pragma once

#include "N2SharedAccessWorker.h"
#include "windows.h"
// или "minwindef.h"

class N2DllSharedAccess: public N2SharedAccessWorker
{
	std_string path_;
	HINSTANCE hin;

public:
	N2DllSharedAccess();

	virtual bool findLib(std_string path);
	
	virtual bool attach(std_string path);
	
	virtual bool checkSignature(SIGN sign);
	
	virtual PEXPROCEDURE getProcedure(std_string nameProc);

};