// MemoryAllocationAndControl.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "../../../export/common/N2LiveObjectsPolicy.h"
#include "../../../export/common/N2Serializer.h"
#include "../../../export/common/N2Standart2014ProjectNode.h"
#include "../../../export/common/N2Register.h"
#include "../include/N2Control.h"

template<class T,
		class OLS = OLS_HeapWithGarbage>
class AllocatorM
{
	T* pt;
public:
	bool create(T value){
		pt = OLS::create<T>(CT(""));
		if(!pt)
			return false;
		*pt = value;
		return true;
	}

	bool delT(){
		return OLS::release<T>(pt);
	}

	bool delVoid(){
		OLS::voidRelease(pt);
		return true;
	}

	void print() {
		std::cout << "ix = " << *pt << "  &ix = " << pt << endl;
	}
};

class A 
{
	int x;
};



int _tmain(int argc, _TCHAR* argv[])
{

	int* ix = OLS_HeapWithGarbage::create<int>(CT(""));
	*ix = 3;
	std::cout << "ix = " << *ix << "  &ix = " << ix << endl;
	//OLS_HeapWithGarbage::release<int>(ix);
	OLS_HeapWithGarbage::voidRelease(ix);
	std::cout << "ix = " << *ix << "  &ix = " << ix << endl;

	int* pmi = new int;
	//int* pmi = new int[10];
	//for(int i=0; i<10; i++) pmi[i] = i;
	int tempi = *pmi;
	std::cout << "tempi = " << tempi << endl;
	delete [] pmi;

	A* pA = new A;
	//delete [] pA;

	//pA = OLS_Heap_New::create<A>(CT("aaa"));
	OLS_Heap_New::voidRelease(pA);

	//
	typedef N2Serializer<N2Standart2014ProjectNode, N2ParserXML<N2TinyXMLParser> >  mntype;
	//N2BaseSerialize* pSer = new N2Serializer<N2Standart2014ProjectNode, N2ParserXML<N2TinyXMLParser> >;
	mntype* pSer = new mntype[1];
	delete [] pSer;

	//AllocatorM<N2Serializer<N2Standart2014ProjectNode, N2DefaultXMLParserT> > alt;
	//alt.create(N2Serializer<N2Standart2014ProjectNode, N2DefaultXMLParserT> ());
	//alt.delVoid();


	return 0;
}

