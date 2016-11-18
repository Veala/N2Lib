// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ModulesManager.cpp
///
///	\brief 		Управитель модулей
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		06.06.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#include "../export/common/N2ModulesManager.h"
#include "../export/common/N2Register.h"
#include "include\N2Modules.h"

N2ModulesManager::N2ModulesManager()
{
}

N2Module*  
N2ModulesManager::createModule(const N2RouteLine* pInfo)
{
	N2Module* pm = NULL;

	switch(pInfo->signIn & N2_MASK_CLASS) {
		case N2_CONSOLE: 
			pm = N2Register::self()->getMemoryAllocator()->create<N2Console>(pInfo->name);
			break;
		case N2_DEBUGER:
			pm = N2Register::self()->getMemoryAllocator()->create<N2Debuger>(pInfo->name);
			break;
		case N2_SYSTEM:
			pm = N2Register::self()->getMemoryAllocator()->create<N2System>(pInfo->name);
			break;
		case N2_INTERNAL:
			pm = N2Register::self()->getMemoryAllocator()->create<N2ModuleInternal>(pInfo->name);
			break;
		default: // ExternalModule
			pm = N2Register::self()->getMemoryAllocator()->create<N2ModuleExternal>(pInfo->name);
	}

	if(!pm)
		return NULL;

	if(!pm->initial(pInfo)) {
		N2Register::self()->getMemoryAllocator()->release(pm);
		return NULL;
	}
	
	//modules_.add(pm);
	
	return pm;
}


bool N2ModulesManager::deleteModule(N2Module* pModule)
{
	return modules_.del(pModule);
}

bool 
N2ModulesManager::updateModulesList(void)
{
	bool retVal = true;
	// затирка
	modules_.clear();
	// заполнение 
	N2ProjectSpecialInfo* pInfo = N2Register::self()->getDeviceInfo();
	if(!pInfo)
		return retVal;
	for(size_t i=0; i<pInfo->modules.size(); i++) {
		N2RouteLine line;
		line.name = pInfo->modules[i].name;
		line.obligative = pInfo->modules[i].obligative;
		line.autoChange = FD_AUTO;
		line.paths = pInfo->pathsDevices;
		/*	std::vector<std_string>::iterator it = pInfo->pathsDevices.begin();
		while(it != pInfo->pathsDevices.end()) {
			line.paths.push_back(*it);
			it ++;
		}*/
		line.fileExtLibrary = pInfo->modules[i].libName;
		line.signIn = pInfo->modules[i].signature;
		//
		const N2RouteLine* pI = const_cast<const N2RouteLine*> (&line);
		N2Module* pM = createModule(pI);
		if(!pM) {
			retVal = false;
			continue;
		}
		modules_.add(pM);
	}

	return retVal;
}


bool 
N2ModulesManager::updateDevices(void)
{
	bool retVal = false;
	for(N2Module* pM=modules_.first(); pM != NULL; pM = modules_.next())
		pM->update();
	return retVal;
}

bool 
N2ModulesManager::AutoExecuteCommand(DataPack* pPack, Response& resp)
{
	bool retVal = false;
	N2ListModules* pList = getListTable();
	if (pList)
	{
		N2Module* pM = pList->find(pPack->signature.img2.devClass);
		if (pM && pM->alive(pPack->signature.img2.numDev))
                {
                    resp = pM->command(pPack);
                    retVal = true;
                }
	}

	return retVal;
}

N2ListModules* 
N2ModulesManager::getListTable(void)
{
	return &modules_;
}


bool 
N2ModulesManager::addModuleManual(N2Module* pModule)
{
	return modules_.add(pModule);
}

