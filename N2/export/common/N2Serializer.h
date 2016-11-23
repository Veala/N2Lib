// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Serializer.h
///
///	\brief 		Класс сериализации проекта
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

#pragma once

#include "../../export/common/N2BaseSerialize.h"
#include "../../export/common/N2Register.h"


template <class TNode,
		class TParser>
class N2Serializer : public N2BaseSerialize
{
	TNode* node;
	TParser* pars;
	//vector<std_string> additionalPaths;

public:
	N2Serializer() :
		node(NULL),
		pars(NULL)
	{
		node = N2Register::self()->getMemoryAllocator()->create<TNode>();
		pars = N2Register::self()->getMemoryAllocator()->create<TParser>();
	}
	~N2Serializer() 
	{
        N2Register::self()->getMemoryAllocator()->release(node);
        N2Register::self()->getMemoryAllocator()->release(pars);
	}
	//
	//virtual ITreeNode*
	virtual bool
	loadProject(std_string filename, std_string& errorDescription)
	{
		node->setParser(pars);
		if(!node->parseTree(filename, errorDescription))
			return false;
		//pars->setPaths(&paths);
		//node.registeredTree();
		if(N2Register::plantTree(node->getRootTree()))
			return true; //node->getRootTree();
		else {
			errorDescription = CT("Ошибка регистрации в реестре");
			return false;//return NULL;
		}
    }
	bool
		saveProject(std_string filename) { return false; }

	//virtual bool
	//addSearchPath(std_string path) {
	//	if(path == EMPTY_STR)
	//			return false;
	//	node->addSearchPath(path);		
	//	return true;
	//}

	//virtual void
	//	resetPaths(void)
	//{
	//	node->resetPaths();
	//}

protected:
	//std::vector<std_string> paths;
};

