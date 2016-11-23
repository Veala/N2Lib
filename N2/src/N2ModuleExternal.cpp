// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ModuleExternal.cpp
///
///	\brief 		Внешний модуль
/// \details	
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		14.05.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#include "include\N2Modules.h"
#include "..\export\common\N2Defines.h"
#include "N2Register.h"

#ifdef WINDOWS_BUILD
	#include "include\N2DllSharedAccess.h"
#elif LINUX_BUILD
	#include "include\N2LinuxSharedAccess.h"
#endif

#ifdef _DEBUG
	#include <fstream>
	#include <iostream>
	using namespace std;
#endif

N2ModuleExternal::~N2ModuleExternal()
{
	//deactivate();
}

///! Сброс устройства
bool N2ModuleExternal::reset(bool hard)
{
	return false;
}


bool N2ModuleExternal::initial(const N2RouteLine* pInfo)
{
	selfInfo = *pInfo;
	bool retVal = false;
#ifdef WINDOWS_BUILD
	connector_ = new N2DllSharedAccess();
#elif LINUX_BUILD
	connector_ = new N2LinuxSharedAccess();
#endif
	if(!connector_)
		return retVal;
	
#ifdef _DEBUG
	ofstream out("Log_err.txt");	
	out << pInfo->name.c_str() << " : " << endl;
#endif

	// поиск по путям в N2RouteLine
	std_string pt = const_cast<N2RouteLine*>(pInfo)->paths.getFirstPath();
	bool finded = false;
	while(pt != EMPTY_STR) {
		pathName = pt + SLASH_STR + pInfo->fileExtLibrary;
#ifdef _DEBUG		
		out << pathName.c_str() << endl;
#endif
		if(connector_->findLib(pathName)) {
			finded = true;
			break;
		}
		pt = const_cast<N2RouteLine*>(pInfo)->paths.getNextPath();
	}
	// поиск по путям в N2ProjectSpecialInfo
	pt = N2Register::self()->getDeviceInfo()->pathsDevices.getFirstPath();	
	while(pt != EMPTY_STR) {
		pathName = pt + SLASH_STR + pInfo->fileExtLibrary;
#ifdef _DEBUG		
		out << pathName.c_str() << endl;
#endif
		if(connector_->findLib(pathName)) {
			finded = true;
			break;
		}
		pt = N2Register::self()->getDeviceInfo()->pathsDevices.getNextPath();
	}

	if(!finded) {
		// запись в журнал
		return retVal;
	}
	if(!connector_->attach()) {
		// запись в журнал
		return retVal;
	}

	// позже раскрыть
	//connector_->checkSignature(signature_);

	f_alive = (alive_)connector_->getProcedure(CT("alive"));
	f_command = (command_)connector_->getProcedure(CT("commandExecute"));

	if(!f_alive || !f_command)
		return retVal;

	// команда перечисления устройств управляющего модуля
	enumerationDevices();

	return true;
}


Response 
N2ModuleExternal::command(DataPack* pPacket)
{	
	return commander(pPacket);
}

void 
N2ModuleExternal::enumerationDevices(void)
{
	if(!f_command)
		return;
	DataPack dp;
	dp.signature.value = MAKE_CODE(CMD_SP_ENUMERATION, N2_EXT_DEVICE_SPECIAL);
	//
	Response ret;
	ret = commander(&dp);
	//
	if(selfInfo.autoChange == FD_AUTO) {
		dp.signature.value = MAKE_CODE(CMD_SP_SET_ACTIVE_SLOT, N2_EXT_DEVICE_SPECIAL);
		dp.ret_value = N2_AUTO_ACTIVATE; // первое в списке
		ret = commander(&dp);
	}
	
}


void 
N2ModuleExternal::setCallBackFunc(void* pMPC, int(*pSF)(void*, DataPack&))
{
	f_callBack = (setCallBackPtr)connector_->getProcedure(CT("setCallBack"));
	if(f_callBack)
		f_callBack(pMPC, pSF);
}


COUNT 
N2ModuleExternal::getListOfDevices(N2DevicesInfo& info)
{
	COUNT retVal = 0;

	if(!f_command)
		return retVal;
	//enumerationDevices();
	if(!info.infos.empty())
		info.infos.clear();
	DataPack dp;
	dp.pCmd = new N2BFC_DEVICE_INFO;
	N2BFC_DEVICE_INFO* pCmd = static_cast<N2BFC_DEVICE_INFO*> (dp.pCmd);	
	dp.signature.value = MAKE_CODE(CMD_SP_DEVICE_INFO, N2_EXT_DEVICE_SPECIAL);
	//
	Response ret = commander(&dp);
	//
	if(ret.err_ == OK) {
		retVal = dp.ret_value;
		
		for(size_t i=0; i<pCmd->infoDev.infos.size(); i++)
			info.infos.push_back(pCmd->infoDev.infos[i]);
	}
	delete pCmd;

	return retVal;
}


bool N2ModuleExternal::open(INDEX devNum)
{
	bool retVal = false;
	if(!f_command)
		return retVal;
	DataPack dp;
	dp.ret_value = 0;
	dp.signature.value = selfInfo.signIn;
	dp.signature.img1.code = CMD_SP_OPEN;
	dp.signature.img1.numDev = devNum;
	//
	Response ret = commander(&dp);
	//
	retVal = !!dp.ret_value;

	return retVal;
}

bool N2ModuleExternal::close(INDEX devNum)
{
	bool retVal = false;
	if(!f_command)
		return retVal;
	DataPack dp;
	dp.ret_value = 0;
	dp.signature.value = selfInfo.signIn;
	dp.signature.img1.code = CMD_SP_CLOSE;
	dp.signature.img1.numDev = devNum;
	//
	Response ret = commander(&dp);
	//
	retVal = !!dp.ret_value;
	return retVal;
}

Response 
N2ModuleExternal::commander(DataPack* pPack)
{
	Response ret(CMD_HANDLER_NOT_FOUND);

	if(!f_command)
		return ret;

	try {
		ret = f_command(pPack);
	}
	catch(...) {
		pPack->errorDescription = CT("Исключительная ситуация во внешней библиотеке : ") + selfInfo.fileExtLibrary + "!";
		ret.err_ = THROW_EXCEPTION;		
	}
	return ret;
}