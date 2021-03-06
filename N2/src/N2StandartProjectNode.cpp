// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Standart2014ProjectNode.cpp
///
///	\brief 		
/// \details	
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		19.06.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#include "../export/common/N2Standart2014ProjectNode.h"
#include "include/N2HelpParserStandart2014Project.h"


std_string N2Standart2014ProjectNode::mark = CT("NODE");
N2Standart2014SpecialInfo N2Standart2014ProjectNode::info_;

N2Standart2014ProjectNode::N2Standart2014ProjectNode():
	enable(true),
	execute(false),
	name(CT("metka 1"))
{	
	
}

N2Standart2014ProjectNode::~N2Standart2014ProjectNode()
{
}

bool N2Standart2014ProjectNode::interpretation(CFS *parsedTree)
{
	return false;
}

//N2HelpParserProject*
//N2Standart2014ProjectNode::help(void)
//{
//	return pHelper_;
//}
//
//bool
//N2Standart2014ProjectNode::setHelper(N2HelpParserProject* pHelper)
//{
//	if(!pHelper)
//		return false;
//	delete pHelper_;
//	pHelper_ = pHelper;
//	return true;
//}


bool
N2Standart2014ProjectNode::parseTree(std_string filename, std_string& error)
{
	bool retVal = false;
	bool loadEnv = false;
	N2HelpParserStandart2014Project* helper = new N2HelpParserStandart2014Project();
	// получаем парсер
	N2Parser* pPars = parser();
	if(!pPars)
		return retVal;
	// 1. найти файл проекта 
	bool ok = helper->exists(filename);
	if(!ok)
		return retVal;
	// 2. найти файлы дерева и вуали
	std_string fVoile;
	std_string fConst = helper->getProjectFiles(filename, pPars, fVoile);
	if(fVoile == EMPTY_STR ||
		helper->exists(fVoile)) {
		// здесь: создание файла вуали
		//help->createFileVoile();
		loadEnv = true;
	}
	// 4. разбор и заполнение дерева, спец. информации, переменных окружения
	ok = helper->fullParseConst(fConst, pPars, loadEnv);
	if(!ok)
		return retVal;
	// 5. разбор файла вуали
	ok = helper->fullParseVoile(fVoile, pPars, !loadEnv);
	if(!ok) {
		helper->createFileVoile(fVoile);
	}
	root_ = helper->getTree();
	delete helper;
	return true;
}


//bool
//N2Standart2014ProjectNode::registeredTree(void)
//{
//	return N2Register::plantTree(root_);
//}

//ITreeNode*
//N2Standart2014ProjectNode::getRootTree(void)
//{		
//	return root_;
//}