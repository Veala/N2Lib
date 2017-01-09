//
// N2VariableComplex.cpp: 
//

#include "stdafx.h"

#include "../../Testing.h"
#include "../../../export/common/N2Variable.h"
//#include "../../../export/common/N2Register.h"
#include "../../../export/common/N2Misc.h"


int _tmain(int argc, _TCHAR* argv[])
{	
	using namespace GloTest;
	TEST_INIT("Complex Variable");

	N2VariableINT vInt(CT("myInt"));
	int x = 35;
	vInt.set(x);
	vInt.get();
	TEST_CHK(*vInt.get() == 35);

	N2VariableFLOAT vFlt(CT("myFlt"));
	float y = (float) 8.79;
	TEST_CHK(vFlt.set(y));
	TEST_CHK(*vFlt.get() == (float)8.79); // что делать с точностью float ?

	N2VariableSTR vStr(CT("myStr"));
	std_string s = CT("example string");
	std_string s2 = CT("example string2");
	TEST_CHK(vStr.set(s));
	TEST_CHK(*vStr.get() == CT("example string"));

	N2VariableSTR vScr (CT("vScrN"));
	TEST_CHK(vScr.name() == CT("vScrN"));
	TEST_CHK(vScr.type() == VAR_STRING);
	TEST_CHK(vScr.add(&vInt) == NULL);

	//// (COUNT) 0 ??? - м.б. начинать с 0, а в dimension() выдавать +1? 
	N2VariableSTR vS0(CT("vScrF"), (COUNT) 0);
	TEST_CHK(vS0.type() == VAR_STRING);
	TEST_CHK(vS0.dimension() == (COUNT) 0);
	TEST_CHK(!vS0.set(s)); 
	TEST_CHK(vS0.get() == NULL);
	//TEST_CHK(false);  // (COUNT) 0 ??? - uncomment previous

	N2VariableSTR vScrF(CT("vScrF"), (COUNT) 2);
	TEST_CHK(vScrF.type() == VAR_STRING);
	TEST_CHK(vScrF.dimension() == (COUNT) 2);
	TEST_CHK(vScrF.set(s)); 
	//TEST_CHK(vScrF.set(&x)); //жестокое приведение void * к типу, при ошибке типа аргумента - сист. исключение 
	//TEST_CHK(false); // RUN ERROR - uncomment previous

	TEST_CHK(vScrF.set(s2, (INDEX) 1));
	TEST_CHK(*vScrF.get() == CT("example string"));
	TEST_CHK(*vScrF.get() == s);
	TEST_CHK(*vScrF.get((INDEX) 1) == CT("example string2"));


	//TEST_CHK(false); // COMPIL ERROR - uncomment previous


	//N2VariableComplex vComp2(CT("Csuper_2d"), 1);
	//N2VariableComplex vCompI0(CT("Csuper_I0"),1);
	//N2VariableComplex vCompI1(CT("Csuper_I1"),1);
	//N2VariableComplex vCompI2(CT("Csuper_I2"),1);

	//N2BaseVariable* pvCompI0 = (N2BaseVariable*) &vCompI0;
	//TEST_CHK(vComp2.add(pvCompI0) != NULL);
	//TEST_CHK(vCompI0.name() == CT("Csuper_I0_Renamed"));				// ??? переименование в самом добавляемом
	//N2BaseVariable* pvCompI0r;
 //   //TEST_CHK((pvCompI0r = vComp2.get( CT("Csuper_2d.Csuper_I0_Renamed"))) == pvCompI0);
 //   //TEST_CHK((pvCompI0r = vComp2.get( CT("Csuper_I0_Renamed"))) == pvCompI0);

	//N2BaseVariable* pvCompI1 = (N2BaseVariable*) &vCompI1;
	//TEST_CHK(vComp2.add(pvCompI1) != NULL);
	//N2BaseVariable* pvCompI1r;
 //   //TEST_CHK((pvCompI1r = vComp2.get(CT("Csuper_I1_Renamed"), (INDEX) 1)) == pvCompI1);
 //   //TEST_CHK((pvCompI1r = vComp2.get( CT("Csuper_2d.Csuper_I1_Renamed[1]"))) == pvCompI1);

	//N2BaseVariable* pvCompI2 = (N2BaseVariable*) &vCompI2;
	//TEST_CHK(vComp2.add(pvCompI2) != NULL);
	//N2BaseVariable* pvCompI2r;
 //   //TEST_CHK((pvCompI2r = vComp2.get( CT("Csuper_I2_Renamed"), (INDEX) 2)) == pvCompI2);
 //   //TEST_CHK((pvCompI2r = vComp2.get( CT("Csuper_2d.Csuper_I2_Renamed"))) == pvCompI2);

	///// новый (правильный) механизм создания переменных
	//N2VariableINT vi1(CT("ivar1"), 10);
	//N2VariableINT vi2(CT("ivar2"));
	//N2VariableFLOAT vf1(CT("fvar1"));
	//N2VariableFLOAT vf2(CT("fvar2"), 2);
	//N2VariableSTR vs1(CT("vstr1"), 5);
	//N2VariableComplex vc1(CT("super1"), 2);
	//TEST_CHK(vc1.name() == CT("super1"));
	//TEST_CHK(vc1.dimension() == (COUNT) 2);
	//N2VariableComplex vc2(CT("super2"));
	//////
	//N2VariableComplex* mn = new N2VariableComplex(CT("my"));
	//
	//N2BaseVariable* temp;
	//vc2.add(&vi1);
	//TEST_CHK((temp = vc1.add((N2BaseVariable*)(&vc2))) != NULL);
	//TEST_CHK(temp->add(&vi1) != NULL);
	//TEST_CHK(vc1.add(&vi1) != NULL);
	//TEST_CHK(vc2.add(&vf2) != NULL);
	//TEST_CHK(mn->add(&vc1) != NULL);
	//TEST_CHK(mn->add(&vc2) != NULL);
	//TEST_CHK(mn->add(&vi2) != NULL);

	//TEST_CHK(!!(temp = mn->getNamed(CT("my.super1[0].super2-2.ivar1[3]"))) );
	////TEST_CHK(!!(temp = mn->getMember("my.firstMassive[0].super2-2.ivar2")) );
	//if(temp)
	//{
	//	N2VariableINT* pvi = (N2VariableINT*)temp;
	//	int ix = 23;
	//	TEST_CHK(pvi->set(ix, 5));
	//	TEST_CHK(*pvi->get(5) == 23);
	//}
	///////////////////////////// вариант 2

	///////// Таблицы
	//N2VariableIntTABLE tabli(

	////vi2->operator delete[];
	//delete [] mn;

	///// Сложные переменные
	//N2VariableComplex* pCpx = new N2VariableComplex [3] ();

	/////////////////////////////////////////////////////////////
 //	N2MemoManager* pMM = N2Register::self()->getMemManager();
	//cout << "Print memory allocation: " << endl;
	//for(size_t i=0; i<pMM->memory.size(); i++) {
	//	cout << i << ".  " << pMM->memory[i].operation.c_str() << \
	//		"   VAR: " << pMM->memory[i].variableName.c_str() << \
	//		"   size= " << pMM->memory[i].sizeOfObject << \
	//		"   count= " <<  pMM->memory[i].number << endl;
	//}

	/// Создание переменных на "фабрике" :
	N2VariableCreator maker;
	N2BaseVariable* pBv1 = NULL, *pBv2 = NULL;
	pBv1 = maker.createSimplex<int>("si_x", 12);
	pBv2 = maker.createComplex("c_complex");
	pBv2->add(pBv1);
	pBv1 = maker.createTable<int>("ti_y", 10, 10, 2);
	pBv2->add(pBv2->clone());
	pBv2->add(pBv1);

	GloTest::printResult();
	return GloTest::errors();
}

