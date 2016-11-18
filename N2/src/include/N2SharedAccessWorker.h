// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2SharedAccessWorker.h
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

#include "../../export/common/N2Base.h"
#include "../../export/common/isolator.h"


using namespace std;

class N2SharedAccessWorker : public N2Base
{
public:

	virtual bool findLib(std_string path) = 0;
	
	virtual bool attach(std_string path = EMPTY_STR) = 0;
	
	virtual bool checkSignature(SIGN sign) = 0;
	
	virtual PEXPROCEDURE getProcedure(std_string nameProc) = 0;
};