// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Module.cpp
///
///	\brief 		
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
#include "N2Register.h"

void 
N2Module::update()
{
	N2DevicesInfo info;	
	for(size_t i=0; i<getListOfDevices(info); i++) {
		alive(i);
	}
}

bool
N2Module::redirection(SIGN signOut)
{
	if (selfInfo.resolveSwitch)
		return false;
	selfInfo.resolveSwitch = true;
	selfInfo.signOut = signOut;
	return true;
}

bool
N2Module::stopRedirection(void)
{
	if (!selfInfo.resolveSwitch)
            return false;
	selfInfo.resolveSwitch = false;
	return true;
}

const N2RouteLine
N2Module::getRouteLine(void) const
{
	return const_cast<const N2RouteLine&>(selfInfo);
}

COUNT
N2Module::getListOfDevices(N2DevicesInfo& info)
{
	return COUNT(0);
}

bool N2Module::open(INDEX devNum)
{
	return false;
}

bool N2Module::close(INDEX devNum)
{
	return false;
}

bool N2RouteLine::operator == (const N2RouteLine& op) const
{
	bool retVal = false;

	if(signIn != op.signIn)
		return retVal;
	if(name != op.name)
		return retVal;
	if(obligative != op.obligative)
		return retVal;
	if(fileExtLibrary != op.fileExtLibrary)
		return retVal;
	//if(path != op.path)
	//		return retVal;
	if(autoChange != op.autoChange)
		return retVal;
	// signOut не сравнивается
	return true;
}

///////////////////////////////// N2Console
Response
BaseConsoleHandler::reverse(DataPack& dp)
{
	if(pConsole_)
		return pConsole_->reverse(dp);
	
	return Response(CMD_HANDLER_NOT_FOUND);
}

///! Исполнить команду
Response N2Console::command(DataPack* pPacket)
{
	if(pHdlr)
		return pHdlr->command(pPacket);
	
	return Response(CMD_HANDLER_NOT_FOUND);
}

/// открыть устройство
bool 
N2Console::open(INDEX devNum)
{
	if(pHdlr)
		return pHdlr->open(devNum);
	return false;
}

/// Освободить устройство
bool 
N2Console::close(INDEX devNum)
{
	if(pHdlr)
		return pHdlr->close(devNum);
	return false;	
}

///! Сброс устройства
bool N2Console::reset(bool hard)
{
	return false;
}

///! Проверка подключения устройства
bool N2Console::alive(INDEX devNum)
{
	return alive_;
}

bool N2Console::initial(const N2RouteLine* pInfo)
{
	selfInfo = *pInfo;
	return true;
}

COUNT 
N2Console::getListOfDevices(N2DevicesInfo& info)
{
	if(pHdlr) 
		return pHdlr->getListOfDevices(info);
	
	return 0;
}

void 
N2Console::setCallBackFunc(void* pMPC, int(*pSF)(void*, DataPack&))
{
	pObjCall = pMPC;
	pObjFuncCall = pSF;
}

Response 
N2Console::reverse(DataPack& dp)
{
	if(pObjCall == NULL ||
		pObjFuncCall == NULL)
			return Response(CMD_HANDLER_NOT_FOUND);

	pObjFuncCall(pObjCall, dp);

	return Response(OK);
}

///////////////////////////////// N2ModuleInternal

Response
N2ModuleInternal::command(DataPack* pPacket)
{
	return Response(ERR);
}


bool
N2ModuleInternal::reset(bool hard)
{
	return false;
}

bool
N2ModuleInternal::alive(INDEX devNum)
{
	return false;
}

bool
N2ModuleInternal::initial(const N2RouteLine* pInfo)
{
	return false;
}


///////////////////////////////// N2ListModules

N2ListModules::~N2ListModules()
{
	clear();	
}

bool 
N2ListModules::add(N2Module* pM)
{
	if(!pM)
		return false;

	std::vector<N2Module*>::iterator it;
	for(it=vecMods.begin(); it<vecMods.end(); it++) {
		if((*it) == pM)
			return false;
	}
	vecMods.push_back(pM);

	return true;
}

bool 
N2ListModules::del(N2Module* pModule)
{
	if(!pModule) 
		return false;
	std::vector<N2Module*>::iterator it;
	for(it=vecMods.begin(); it<vecMods.end(); it++)
		if((*it) == pModule) {
			N2Register::self()->getMemoryAllocator()->release(*it);
			vecMods.erase(it);
			break;
		}
	
	return true;
}

void
N2ListModules::clear()
{
	for(size_t i=0; i<vecMods.size(); i++)
		N2Register::self()->getMemoryAllocator()->release(vecMods[i]);
	vecMods.clear();
}

N2Module* 
N2ListModules::find(const N2RouteLine* pRl)
{
	std::vector<N2Module*>::iterator it;
	for(it=vecMods.begin(); it<vecMods.end(); it++)
		if((*it)->getRouteLine() == *pRl) {
			return *it;
		}
	return NULL;
}

N2Module* 
N2ListModules::find(SIGN signature)
{
	std::vector<N2Module*>::iterator it;
	for(it=vecMods.begin(); it<vecMods.end(); it++)
		if(((*it)->getSignature() & N2_LMASK_CLASS) == (signature & N2_LMASK_CLASS))
		{
			if ((*it)->getRouteLine().resolveSwitch)
			{
				SIGN sgn = (*it)->getRouteLine().signOut;
				return find(sgn);
			}
			return *it;
		}
	return NULL;
}

N2Module* 
N2ListModules::first(void)
{
	if(vecMods.empty())
		return NULL;
	curIndex = 0;
	return vecMods[0];
}

N2Module* 
N2ListModules::next(void) 
{
	curIndex ++;
	if(curIndex >= vecMods.size())
		return NULL;
	return vecMods[curIndex];
}

N2ListModules::N2ListModules() :
	curIndex(0)
{}

UINT_N2  
N2ListModules::size(void)
 {
	 return vecMods.size();
 }

bool
N2ListModules::redirection(SIGN sign_src, SIGN sign_dst)
{
	bool bRet = false;

	if (sign_src == sign_dst)
		return bRet;

	N2Module* mod_src = NULL;
	N2Module* mod_dst = NULL;
	std::vector<N2Module*>::iterator it;

	for (it = vecMods.begin(); it < vecMods.end(); it++)
	{
		if (((*it)->getSignature() & N2_LMASK_CLASS) == sign_src)
			mod_src = *it;
		if (((*it)->getSignature() & N2_LMASK_CLASS) == sign_dst)
			mod_dst = *it;
	}

	if (mod_src && mod_dst)
		return mod_src->redirection(sign_dst);

	return bRet;
}

bool
N2ListModules::stopRedirection(SIGN signature)
{
	std::vector<N2Module*>::iterator it;
	for (it = vecMods.begin(); it<vecMods.end(); it++)
		if (((*it)->getSignature() & N2_LMASK_CLASS) == signature)
			return (*it)->stopRedirection();
	return false;
}
