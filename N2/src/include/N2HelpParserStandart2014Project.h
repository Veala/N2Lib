// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2HelpParserStandart2014Project.h
///
///	\brief 		Класс помощи разборки проекта
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


//#include "N2HelpParserProject.h"
#include "../common/N2Standart2014ProjectNode.h"
#include "../common/isolator.h"
#include "N2ProjectNode.h"
#include "N2Defines.h"

using namespace N2_Defines;

class N2HelpParserStandart2014Project //: public N2HelpParserProject
{
	N2TreeNode<N2Standart2014ProjectNode>* pTreeNode;

	TYPE_VAR getTypeFromString(std_string str);

public:
	N2HelpParserStandart2014Project():
		pTreeNode(NULL)
	{}	

	std_string 
	getProjectFiles(std_string fileToParse, N2Parser* pParser, std_string& fileVoile);

	bool yes_no(std_string val);

	int strToInt(std_string val);

	ITreeNode* getTree();

	bool exists(std_string filename);

	bool 
	fullParseConst(std_string filename, N2Parser* pParser, bool loadEnvironment);

	bool
	fullParseVoile(std_string filename, N2Parser* pParser, bool loadEnvironment);

	void
	rollUpTree(CFS* pCFS, N2TreeNode<N2Standart2014ProjectNode>* pNode);

	bool
	rollUpEnvr(CFS* pCFS);

	bool
	createFileVoile(std_string filename);


};

