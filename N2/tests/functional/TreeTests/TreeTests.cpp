// TreeTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "../../../export/common/N2TreeNode.h"
#include "../../../export/common/user/SciurusProjectNode2014.h"
#include "../../Testing.h"

#include <iostream>

using namespace std;

struct Configuration
{

	string name;
	string file;
	int x;

	int operator == (Configuration& c)
	{
		if(&c == this)
			return 1;
		return (x == c.x);
	}
};

static unsigned short level;
template<class T>
void printTree(N2TreeNode<T>* pNode)
{
	if(!pNode)
	{
		level = 0;
		return;
	}
	if (level == 0) 		printf("------TREE------------\n");

	printf("- level = %u data = %s\n", level, pNode->getData()->c_str());
	N2TreeNode<T>* temp = pNode->getFirstChild();
	level++;
	while(temp){
		printTree(temp);
		temp = pNode->getNextSibling();
	}
	level--;
};

using namespace GloTest;

int _tmain(int argc, _TCHAR* argv[])
{
	///////////////////////////////////////////////
	// Общие ф-ции использования дерева
	///////////////////////////////////////////////
	TEST_INIT("TreeTests");
	N2TreeNode<string>* p_s0;
	N2TreeNodeCreator<string> maker;
	
	string s0 = "s0",s01 = "s01", s02("s02"), s03("s03"), s03m("s03m");
	string s021("s021"), s022("s022");
	string s031("s031"), s032("s032");
	string s0211("s0211"), s0212("s0212"), s0213("s0213");
	TEST_CHK((p_s0 = maker.createNode()) != NULL);
	TEST_CHK(&s0 != NULL);
	p_s0->setData(&s0);
	TEST_CHK(*(p_s0->getData()) == s0);

	TEST_CHK(maker.setChild(p_s0, &s01) != NULL);
	TEST_CHK(maker.setChild(p_s0, &s02) != NULL);
	TEST_CHK(maker.setChild(p_s0, &s02) == NULL);

	N2TreeNode<string>* p_s02;
	TEST_CHK(( p_s02 = p_s0->getChild( &s02)) != NULL) ;
	TEST_CHK(maker.setChild(p_s02, &s021) != NULL);
	TEST_CHK(maker.setChild(p_s02, &s022) != NULL);

	N2TreeNode<string>* p_s03;
	TEST_CHK(( p_s03 = maker.setChild(p_s0, &s03)) != NULL);
	TEST_CHK(maker.setChild(p_s03, &s031) != NULL);
	TEST_CHK(maker.setChild(p_s03, &s032) != NULL);

	N2TreeNode<string>* p_s021;
	TEST_CHK(( p_s021 = p_s02->getChild( &s021)) != NULL) ;
	TEST_CHK(maker.setChild(p_s021, &s0211) != NULL);
	TEST_CHK(maker.setChild(p_s021, &s0212) != NULL);
	TEST_CHK(maker.setChild(p_s021, &s0213) != NULL);



	level = 0;
	printTree<string>(p_s0);

	p_s03->setData(&s03m);
	string * p_data_s03 = p_s03->getData();
	TEST_CHK(*p_data_s03 == s03m);
	printTree<string>(p_s03);

	//printTree<string>( p_s02);
	//printTree<string>(p_s03);
	//printTree<string>(p_s021);
	
	///////////////////////////////////////////////
	// Использование дерева под сложные переменные
	///////////////////////////////////////////////
	TEST_INIT("TreeTests - 2");
	N2TreeNode<SciurusProjectNode2014>* node;
	N2TreeNodeCreator<SciurusProjectNode2014> creator;

	



	/////////////////////////////////////////////////////
	// Использование дерева под хранение иерархии проекта
	/////////////////////////////////////////////////////
	
	GloTest::printResult();
	return GloTest::errors();

}

