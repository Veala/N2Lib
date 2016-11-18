// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2ProjectNode.h
///
///	\brief 		Интерфейс проектного узла
/// \details	Данные описывающие узел дерева загруженного проекта
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

#include "isolator.h"
//#include "configuration.h"
//#include "N2HelpParserProject.h"
#include "ITreeNode.h"
#include "N2Parser.h"

using namespace std;



class N2ProjectNode
{
	static int cnt_;
	ITreeNode* subtree_;

protected:
	USID usid_;
	N2Parser* pParser_;
	ITreeNode* root_;

public :	
	virtual
	int operator == (N2ProjectNode& c)
	{
		if(&c == this)
			return 1;
		return (usid_ == c.usid_);
	}

	N2ProjectNode() :
		pParser_(NULL),
		subtree_(NULL),
		root_(NULL)
	{}

	N2ProjectNode(ITreeNode* t) :
		pParser_(NULL), subtree_(t), root_(NULL)
	{}

	virtual bool
	setParser(N2Parser* pParser)
	{
		if(!pParser)
			return false;
		pParser_ = pParser;
		return true;
	}

	virtual N2Parser*
		parser(void) 
	{
		return pParser_;
	}

	virtual bool
		parseTree(std_string filename, std_string& errorDescription) = 0;

	//virtual bool
	//	registeredTree(void) = 0;

	virtual ITreeNode*
		getRootTree(void)
	{
		return root_;
	}

	virtual ITreeNode*
		TreeNode(void)
	{
		return subtree_;
	}

	/*virtual void
		setTreeNode(ITreeNode* pTreeNode)
	{
		subtree_ = pTreeNode;
	}*/

	virtual USID*
		usid() {return &usid_;}

};



