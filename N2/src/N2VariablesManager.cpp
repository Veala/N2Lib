// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2VariablesManager.cpp
///
///	\brief 		
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		21.03.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#include "include\N2VariablesManager.h"
#include "../common/N2Register.h"


bool N2VariablesManager::declare(N2BaseVariable* pVar/*, N2_VMT type*/)
{
	if(!pVar)
		return false;
	for(size_t i=0; i<cache.size(); i++) {
		
		if(cache[i]->name() == pVar->name())
			return false;
	}

	cache.push_back(pVar);
	return true;
}


bool N2VariablesManager::release(std_string name/*, N2_VMT type*/)
{
	vector<N2BaseVariable*>::iterator it;
	for(it = cache.begin(); it != cache.end(); it++) {
	
		if((*it)->name() == name) {
			N2BaseVariable* pv = *it;
			cache.erase(it);
			N2Register::self()->getMemoryAllocator()->release(pv);
			return true;
		}
	}

	return false;
}
    
void N2VariablesManager::clear(/*N2_VMT type*/)
{
	vector<N2BaseVariable*>::iterator it;
	for(it = cache.begin(); it != cache.end(); it++) {
		N2BaseVariable* pv = *it;
		N2Register::self()->getMemoryAllocator()->release(pv);
	}
	cache.clear();
}

N2BaseVariable* 
N2VariablesManager::getVar(std_string name)
{
	 vector<N2BaseVariable*>::iterator it;
	for(it = cache.begin(); it != cache.end(); it++) {
			if((*it)->name() == name) 
				return *it;
	}
	return NULL;
}

//N2BaseVariable* 
//N2VariablesManager::getGlobal(std_string name)
//{
//	 vector<N2BaseVariable*>::iterator it;
//	for(it = globalVariable.begin(); it != globalVariable.end(); it++) {
//			if((*it)->name() == name) 
//				return *it;
//	}
//	return NULL;	
//}

//bool N2VariablesManager::setValue(TYPE type, std_string name, void* val, INDEX index)
//{
//	    vector<N2BaseVariable*>::iterator it;
//		for(it = cache.begin(); it != cache.end(); it++) {
//			if((*it)->name == name) {
//				if((*it)->type() != type)
//					return false;
//				switch((*it)->type()) {
//					// небезопасные преобразования, надо что-то другое
//					case 	T_INT: (static_cast<N2VariableINT*>(*it))->set(val, index); break;
//					case 	T_LNG: (static_cast<N2VariableLONG*>(*it))->set(val, index); break;
//					case 	T_STR: (static_cast<N2VariableSTR*>(*it))->set(val, index); break;
//					case 	T_FLT: (static_cast<N2VariableFLOAT*>(*it))->set(val, index); break;
//					case 	T_BOOL: (static_cast<VariableBOOL*>(*it))->set(val, index); break;   
//					default: return false;
//				}
//				return true;
//			}
//		}
//		return false;
//}
