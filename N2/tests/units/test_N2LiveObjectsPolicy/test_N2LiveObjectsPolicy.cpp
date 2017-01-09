// test_N2LiveObjectsPolicy.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "../../Testing.h"
#include "N2LiveObjectsPolicy.h"
#include "N2Register.h"
#include "isolator.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace GloTest;
	TEST_INIT("N2LiveObjectsPolicy");

	//////struct OLS_Heap_New begining

	//std_string test_name = "";
	//float* p_float;
	//
	//TEST_CHK(p_float = OLS_Heap_New::create<float>(test_name));
	//OLS_Heap_New::release(p_float);
	//TEST_CHK(p_float == NULL);
	//p_float = OLS_Heap_New::create<float>(test_name);
	//OLS_Heap_New::voidRelease(p_float);
	//TEST_CHK(p_float == NULL);
	////
	//TEST_CHK(p_float = OLS_Heap_New::create<float>(test_name));
	//OLS_Heap_New::release(p_float);
	//TEST_CHK(p_float == NULL);
	//p_float = OLS_Heap_New::create<float>(test_name);
	//OLS_Heap_New::voidRelease(p_float);
	//TEST_CHK(p_float == NULL);
	////
	//TEST_CHK(p_float = OLS_Heap_New::create<float>(test_name));
	//OLS_Heap_New::release(p_float);
	//TEST_CHK(p_float == NULL);
	//p_float = OLS_Heap_New::create<float>(test_name);
	//OLS_Heap_New::voidRelease(p_float);
	//TEST_CHK(p_float == NULL);

	//////struct OLS_Heap_New end

	//////struct OLS_HeapWithGarbage begining

	//TEST_CHK(p_float = OLS_HeapWithGarbage::create<float>(test_name));
	//OLS_HeapWithGarbage::release(p_float);
	//TEST_CHK(p_float == NULL);
	//p_float = OLS_HeapWithGarbage::create<float>(test_name);
	//OLS_HeapWithGarbage::voidRelease(p_float);
	//TEST_CHK(p_float == NULL);
	////
	//TEST_CHK(p_float = OLS_HeapWithGarbage::create<float>(test_name));
	//OLS_HeapWithGarbage::release(p_float);
	//TEST_CHK(p_float == NULL);
	//p_float = OLS_HeapWithGarbage::create<float>(test_name);
	//OLS_HeapWithGarbage::voidRelease(p_float);
	//TEST_CHK(p_float == NULL);
	////
	//TEST_CHK(p_float = OLS_HeapWithGarbage::create<float>(test_name));
	//OLS_HeapWithGarbage::release(p_float);
	//TEST_CHK(p_float == NULL);
	//p_float = OLS_HeapWithGarbage::create<float>(test_name);
	//OLS_HeapWithGarbage::voidRelease(p_float);
	//TEST_CHK(p_float == NULL);
	//////struct OLS_HeapWithGarbage end
	
	

	std_string test_name = "";
	float* p_float;
	OLS_Heap* pma = N2Register::self()->getMemoryAllocator();

	TEST_CHK(p_float = pma->create<float>(test_name));
	pma->release(p_float);
	TEST_CHK(p_float == NULL);
	//p_float = pma->create<float>(test_name);
	//pma->voidRelease(p_float);
	//TEST_CHK(p_float == NULL);
	//
	TEST_CHK(p_float = pma->create<float>(test_name));
	pma->release(p_float);
	TEST_CHK(p_float == NULL);
	//p_float = pma->create<float>(test_name);
	//pma->voidRelease(p_float);
	//TEST_CHK(p_float == NULL);
	//
	TEST_CHK(p_float = pma->create<float>(test_name));
	pma->release(p_float);
	TEST_CHK(p_float == NULL);
	//p_float = pma->create<float>(test_name);
	//pma->voidRelease(p_float);
	//TEST_CHK(p_float == NULL);

	GloTest::printResult();
	return GloTest::errors();
	
	return 0;
}

