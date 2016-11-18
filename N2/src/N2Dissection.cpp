// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Dissection.cpp
///
///	\brief 		Встроенный байт-кодер команд задачи
/// \details	Для разбора команд предназначенных процессору и некоторых
/// \details	команд консоли.
///
/// \copyright  ЗАО НТЦ "Модуль"
/// \author 	Чихичин Д.А.
///
/// \date 		11.07.2014
/// \version 	0.1
///  
///  История изменений:
///  
///

#include "N2Defines.h"
#include "N2Dissection.h"
#include "N2Register.h"
#include "N2Phelper.h"

N2Parser* N2Dissection::pParser_ = NULL;
VectorCommand* N2Dissection::pVecComm_ = NULL;

bool 
N2Dissection::unpack(CFS* pCFS)
{
	if(!pCFS || !N2Dissection::getOrder())
		return false;

	bool retVal = true;
	N2TreeNode<XMLF>* pNode;
	

	XMLF* pXMLF = pCFS->getData();
	if(pXMLF->nametag == EMPTY_STR)
		return retVal;
	vector<DataPack> packet;
	if(pXMLF->tag == N2_XMLFTAG_SINGLE) {
		decode(pXMLF, packet);
		for(size_t i=0; i<packet.size(); i++)
			N2Dissection::getOrder()->push_back(packet[i]);
		packet.clear();
	}
	else if(pXMLF->tag == N2_XMLFTAG_BEGIN) {
		// N2_XMLFTAG_BEGIN
		decode(pXMLF, packet);
		for(size_t i=0; i<packet.size(); i++)
			N2Dissection::getOrder()->push_back(packet[i]);
		packet.clear();
		// проходим по дочерним узлам
		pNode = pCFS->getFirstChild();
		while(pNode) {
			unpack(pNode);
			pNode = pCFS->getNextChild();
		}
		// N2_XMLFTAG_END;
		pXMLF->nametag = std_string("/") + pXMLF->nametag;
		decode(pXMLF, packet);
		for(size_t i=0; i<packet.size(); i++)
			N2Dissection::getOrder()->push_back(packet[i]);
		packet.clear();
	}
	else {
		return retVal;
	}
	return retVal;
}





N2Dissection::RESULT_DECODE
SET_PARSER_ERR(vector<DataPack>& totalPack, DataPack& pack, std_string tag, std_string attr, std_string real_attr)
{
	std_string s = std_string("Тэг <") + tag + std_string(">, атрибут \"") + attr + std_string("\"=\"") +\
				real_attr + std_string("\".   ");
	//N2ErrorBFC* pErr =  N2Register::self()->getMemoryAllocator()->create<N2ErrorBFC>(CT("PARSEERROR: ") + s);	
	//pErr->descriptionError = s;
	//if(pack.pCmd != NULL)
	//	N2Register::self()->getMemoryAllocator()->release(pack.pCmd);
	//pack.pCmd = pErr;
	pack.namePack = s;
	pack.signature.value =  SIGN_CONSOLE(CMD_CON_SYNTAX_ERROR);
	pack.nameTag = CT("PARSER: SYNTAX ERROR");
	totalPack.push_back(pack);
	return N2Dissection::RESULT_DECODE::ERROR;
}

N2Dissection::RESULT_DECODE
SET_ANOTHER_ERR(vector<DataPack>& totalPack, DataPack& pack, std_string decsError)
{
	/*N2ErrorBFC* pErr =  N2Register::self()->getMemoryAllocator()->create<N2ErrorBFC>(CT("PARSEERROR"));	
	pErr->descriptionError = decsError;
	pack.pCmd = pErr;*/
	pack.namePack = decsError;
	pack.signature.value =  SIGN_CONSOLE(CMD_CON_SYNTAX_ERROR);
	pack.nameTag = CT("PARSER ERROR");
	totalPack.push_back(pack);
	return N2Dissection::RESULT_DECODE::ERROR;
}



N2Dissection::RESULT_DECODE
N2DissInternal::decode(XMLF* px, vector<DataPack>& totalPack)
{
	RESULT_DECODE retVal = SUCCESSFUL;
	if(!px)
		return retVal;
	
	//pack = N2Register::self()->getMemoryAllocator()->create<DataPack>("Data Packet");
	DataPack pack;
	pack.nameTag = px->nametag;

////////////////////////////////////////////////////////////////		
// начало подтеста
	if(px->nametag == CT("TASK"))
	{
		std_string atr_guid = px->getValue(CT("usid"));
		std_string name = px->getValue(CT("name"));
		
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2HierarchyBFC>(CT("<TASK>"));
		if(pack.pCmd)
			((N2HierarchyBFC*)pack.pCmd)->usid = atr_guid;
		pack.namePack = name;
		pack.signature.value = SIGN_PROCC(CMD_TASK);	
		
		totalPack.push_back(pack);
		return retVal;
	}
////////////////////////////////////////////////////////////////		
// начало подтеста
	if(px->nametag == CT("/TASK"))
	{	
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BaseFormatCommand>("</TASK>");
		pack.signature.value = SIGN_PROCC(CMD_TASK_END);	
	
		totalPack.push_back(pack);
		return retVal;
	}

////////////////////////////////////////////////////////////////
// начало шага
	if(px->nametag  == CT("STEP"))
	{
		std_string atr_guid = px->getValue(CT("usid"));
		std_string name = px->getValue(CT("name"));

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2HierarchyBFC>("<STEP>");
		pack.namePack = name;
		if(pack.pCmd)
			((N2HierarchyBFC*)pack.pCmd)->usid = atr_guid;
		pack.signature.value = SIGN_PROCC(CMD_STEP);

		totalPack.push_back(pack);
		return retVal;
	}
////////////////////////////////////////////////////////////////
// конец шага
	if(px->nametag  == CT("/STEP"))
	{
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BaseFormatCommand>("</STEP>");
		pack.signature.value = SIGN_PROCC(CMD_STEP_END);	
	
		totalPack.push_back(pack);  return retVal;
	}
////////////////////////////////////////////////////////////////
// декларация переменной
	if(px->nametag  == CT("VARIABLE") ||
		px->nametag  == CT("VAR"))
	{
		std_string type, name, value, size;
		
		type = px->getValue(CT("type"));
		name = px->getValue(CT("var"));
		if(name == "") 
			return SET_PARSER_ERR(totalPack, pack, "VARIABLE", "name", name);			

		value = px->getValue(CT("value"));
		size = px->getValue(CT("size"));
		TYPE_VAR  tv;

		if(!checkType(type, tv))
			return  SET_PARSER_ERR(totalPack, pack, px->nametag, "type", type);
		
		PHelper helper;
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2DeclareBFC>("<VARIABLE>");
		if(pack.pCmd) {
            N2DeclareBFC* cmd = (N2DeclareBFC*)pack.pCmd;
			cmd->type = tv;
			helper.Reset();
			AHE ahe = helper.WhatIs(size);
			if(ahe == AHE_DIGIT) {
				cmd->size = helper.GetValue();
				if(cmd->size == 0)
					cmd->size = 1;
			}
			else {
				cmd->sizeStr = size;
				cmd->size = 0;
			}
		
			helper.Reset();		
			if(helper.WhatIs(value) == AHE_VARIABLE)
				cmd->initVariable = value;
			else {
				switch(cmd->type) {
					case VAR_INT: 
						pack.buffer = (void*) N2Register::self()->getMemoryAllocator()->create<INT_N2>(CT("int"));
						*(static_cast<int*>(pack.buffer)) = helper.StoI(value);
						break;
					case VAR_FLOAT: 
						pack.buffer = (void*) N2Register::self()->getMemoryAllocator()->create<FLOAT_N2>(CT("float"));					
						*(static_cast<float*>(pack.buffer)) = helper.GetValueFloat();
						break;
					case VAR_LONG: 
						pack.buffer = (void*) N2Register::self()->getMemoryAllocator()->create<LONG_N2>(CT("long"));
						*(static_cast<long*>(pack.buffer)) = helper.GetLongValue();
						break;
					case VAR_STRING: 
						pack.buffer = (void*) N2Register::self()->getMemoryAllocator()->create<std_string>(CT("string"));
						*(static_cast<std_string*>(pack.buffer)) = value;
						break;
					case VAR_BOOL: 
						pack.buffer = (void*) N2Register::self()->getMemoryAllocator()->create<bool>(CT("bool"));
						helper.AddFirst("TRUE", 1);		
						helper.Add("FALSE", 0);
						helper.Add("YES", 1);
						helper.Add("NO", 0);
						helper.Add("1", 1);
						helper.Add("0", 0);
						if(helper.WhatIs(value) == AHE_TOKEN)
							*(static_cast<bool*>(pack.buffer)) = !!helper.GetValue();
						break;
					case VAR_TERNAR: 
						pack.buffer = (void*) N2Register::self()->getMemoryAllocator()->create<TERNAR>(CT("TERNAR"));
						helper.AddFirst("YES", TERNAR_YES);
						helper.Add("NO", TERNAR_NO);
						helper.Add("DIS", TERNAR_DISABLE);
						if(helper.WhatIs(value) == AHE_TOKEN)
							*(static_cast<TERNAR*>(pack.buffer)) = (TERNAR)!!helper.GetValue();
						break;

					default:
						pack.buffer = NULL;					
				}
			}		
		}

		pack.namePack = name;
		pack.signature.value = SIGN_PROCC(CMD_VARIABLE);
		
		totalPack.push_back(pack);  return retVal;
	}
////////////////////////////////////////////////////////////////
// бинарнные и унарные операции, в т.ч. с константами
	if(px->nametag  == CT("OPERATION"))
	{
		std_string op1, op2, code, res, type;

		op1 = px->getValue(CT("op1"));
		op2 = px->getValue(CT("op2"));
		code = px->getValue(CT("code"));
		res = px->getValue(CT("result"));
		type = px->getValue(CT("type2"));
	
        PHelper helper;
		helper.AddFirst("DEC", N2OC_DEC);  // унарная
		helper.Add("INC", N2OC_INC);		// унарная
		helper.Add("INIT", N2OC_INIT);
		helper.Add("PLUS", N2OC_PLUS);
		helper.Add("MINUS", N2OC_MINUS);
		helper.Add("DIV", N2OC_DIV);
		helper.Add("AND", N2OC_AND);
		helper.Add("OR", N2OC_OR);
		helper.Add("XOR", N2OC_XOR);
		helper.Add("LG", N2OC_LOG_10);	// унарная
		helper.Add("LOG", N2OC_LOG);
		helper.Add("LN", N2OC_LN);
		helper.Add("MULT", N2OC_MULT);
		helper.Add("SHIFT_LEFT", N2OC_SHIFT_LEFT);
		helper.Add("SHIFT_RIGHT", N2OC_SHIFT_RIGTH);
		helper.Add("MIN", N2OC_MIN);
		helper.Add("MAX", N2OC_MAX);
		helper.Add("MOD", N2OC_MOD);
		helper.Add("NOT", N2OC_NOT);
		AHE ahe = helper.WhatIs(code);
		if(ahe != AHE_TOKEN) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("OPERATION"), CT("code"), code);
			return ERROR;
		}
		if(op1 == EMPTY_STR) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("OPERATION"), CT("op1"), op1);
			return ERROR;		
		}
		//
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2OperationBFC>(CT("<OPERATION>"));
		N2OperationBFC* cmd = (N2OperationBFC*) pack.pCmd;
		if(!cmd) {
			retVal = SET_ANOTHER_ERR(totalPack, pack, "OPERATION: ошибка выделения памяти!");
			return ERROR;		
		}
		checkType(type, cmd->type2);
		cmd->op1 = op1;
		cmd->op2 = op2;
		cmd->code = (N2_OPERATING_CODE)helper.GetValue();
		cmd->opResult = (res == EMPTY_STR) ? op1 : res;


		pack.namePack = CT("OPERATION");
		pack.signature.value = SIGN_PROCC(CMD_OPERATION);
		totalPack.push_back(pack);  return retVal;
	}

////////////////////////////////////////////////////////////////
// условный оператор IF
	if(px->nametag  == CT("IF"))
	{
		std_string variable, cd, val;
		int value = 0;
		int code = 0;

		variable = px->getValue(CT( "var"));
		if(variable == "")
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("IF"), CT("var"), variable);
				return ERROR;}
		cd = px->getValue(CT( "code")); 
		val = px->getValue(CT( "value"));

		PHelper helper;
		if(helper.WhatIs(variable) != AHE_VARIABLE) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("IF"), CT("var"), variable);
			return ERROR;
		}
		if(cd != EMPTY_STR && val != EMPTY_STR) {			
			helper.AddFirst("EQU", N2COMPARE_EQU);
			helper.Add("GR", N2COMPARE_GR);
			helper.Add("LS", N2COMPARE_LS);
			helper.Add("GREQ", N2COMPARE_GREQ);
			helper.Add("LSEQ", N2COMPARE_LSEQ);
			helper.Add("NEQ", N2COMPARE_NEQ);
			if(helper.WhatIs(cd) != AHE_TOKEN) 
				code = N2COMPARE_UNDEFINE;
			else 
				code = helper.GetValue();
		}
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC1>(CT("<IF>"));
		N2BFC1* cmd = (N2BFC1*) pack.pCmd;
		cmd->nameVariable1 = variable;
		cmd->nameVariable2 = val;
		cmd->codeCompare = (N2_COMPARE_CODES)code;

		pack.namePack = CT("IF");
		pack.signature.value = SIGN_PROCC(CMD_IF);		
		totalPack.push_back(pack);  return retVal;
	}

////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("/IF"))
	{
		pack.namePack = CT("/IF");
		pack.signature.value = SIGN_PROCC(END_CMD);
		totalPack.push_back(pack);  return retVal;
	}

////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("EMPTY"))
	{
		//pack.namePack = CT("");
		pack.signature.value = SIGN_PROCC(CMD_EMPTY);
		totalPack.push_back(pack);  return retVal;
	}
////////////////////////////////////////////////////////////////
// условный оператор ELSE
	if(px->nametag  == CT("ELSE"))
	{
		pack.namePack = CT("ELSE");
		pack.signature.value = SIGN_PROCC(CMD_ELSE);

		totalPack.push_back(pack);  return retVal;
	}	
////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("/ELSE"))
	{
		pack.namePack = CT("/ELSE");
		pack.signature.value = SIGN_PROCC(END_CMD);
		totalPack.push_back(pack);  return retVal;
	}

////////////////////////////////////////////////////////////////
// цикл теста
	if(px->nametag  == CT("FOR"))
	{
		std_string param_cycle, b,e,s;
		unsigned short step = 0;
		int begin = 0, end = 0;
		bool n = false;
		bool vars[3] = {false, false, false};

		param_cycle = px->getValue(CT( "var"));
		if(param_cycle == EMPTY_STR)
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("FOR"), CT("var"), param_cycle);
				return ERROR;}
		b = px->getValue(CT( "begin"));
		e = px->getValue(CT( "end"));
		s = px->getValue(CT( "step"));	
		string sn = px->getValue(CT( "decrement"));	
		PHelper helper;
		helper.AddFirst("YES", YES);
		helper.Add("NO", NO);
		AHE ahe = helper.WhatIs(sn);
		if(ahe == AHE_TOKEN && helper.GetName() == "YES")		
				n = true;
		
		helper.Reset();
		ahe = helper.WhatIs(param_cycle);
		if(ahe != AHE_VARIABLE)
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("FOR"), CT("var"), param_cycle);
				return ERROR;}
		// begin
		ahe = helper.WhatIs(b);
		if(ahe == AHE_DIGIT)
				begin = helper.GetValue();
		else if(ahe == AHE_VARIABLE)
				vars[0] = true;
		else	
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("FOR"), CT("begin"), b);
				return ERROR;}
		// end
		ahe = helper.WhatIs(e);
		if(ahe == AHE_DIGIT)
				end = helper.GetValue();
		else if(ahe == AHE_VARIABLE)
				vars[1] = true;
		else	
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("FOR"), CT("end"), e);
				return ERROR;}
		// step		
		ahe = helper.WhatIs(s);
		if(ahe == AHE_DIGIT)
				step = helper.GetValue();
		else if(ahe == AHE_VARIABLE)
				vars[2] = true;
		else	
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("FOR"), CT("step"), s);
				return ERROR;}
		
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC2>(CT("<FOR>"));
		N2BFC2* cmd = (N2BFC2*) pack.pCmd;
		if(vars[0])
			cmd->s_var[0] = b;
		cmd->i_var[0] = begin;
		if(vars[1])
			cmd->s_var[1] = e;
		cmd->i_var[1] = end;
		if(vars[2])
			cmd->s_var[2] = s;
		cmd->i_var[2] = step;
		cmd->dec = n;
		pack.namePack = param_cycle;
		pack.signature.value = SIGN_PROCC(CMD_FOR);	

		totalPack.push_back(pack);  return retVal;
	}
////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("/FOR"))
	{
		pack.namePack = CT("/FOR");
		pack.signature.value = SIGN_PROCC(END_CMD);
		totalPack.push_back(pack);  return retVal;
	}

////////////////////////////////////////////////////////////////
// операции сравнения
	if(px->nametag == CT("COMPARE"))
	{
		std_string op1, op2, code, result;

		op1 = px->getValue(CT("op1"));
		op2 = px->getValue(CT("op2")); 
		code = px->getValue(CT("code"));
		result = px->getValue(CT("result"));

		if(op1 == EMPTY_STR || op2 == EMPTY_STR)
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("COMPARE"), (op1 == "") ? "op1" : "op2", "");
				return ERROR;}
		if(result == "")
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("COMPARE"), CT("result"), result);
				return ERROR;}
							
		PHelper helper;
		helper.AddFirst("EQU", 20);
		helper.Add("GR", 21);
		helper.Add("LS", 22);
		helper.Add("GREQ", 23);
		helper.Add("LSEQ", 24);
		helper.Add("NEQ", 25);
		AHE ahe = helper.WhatIs(code);
		if(ahe != AHE_TOKEN)
				{retVal = SET_PARSER_ERR(totalPack, pack, CT("COMPARE"), CT("code"), code);
				return ERROR;}
		
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC1>(CT("<COMPARE>"));
		N2BFC1* cmd = (N2BFC1*) pack.pCmd;

		pack.namePack = result;
		cmd->nameVariable1 = op1;
		cmd->nameVariable2 = op2;
		cmd->codeCompare = (N2_COMPARE_CODES)helper.GetValue();
	
		pack.signature.value = SIGN_PROCC(CMD_COMPARE);
		
		totalPack.push_back(pack);  return retVal;
	}

////////////////////////////////////////////////////////////////
	if(px->nametag == CT("BREAK"))
	{

		pack.namePack = CT("BREAK");
		pack.signature.value = SIGN_PROCC(CMD_BREAK);
			
		totalPack.push_back(pack);  return retVal;
	}


////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("EXECUTE"))
	{
		std_string name = px->getValue(CT( "name"));
		std_string param = px->getValue(CT( "param"));
		std_string out = px->getValue(CT( "out"));
		std_string result = px->getValue(CT( "result"));
		
		if(name == "") 
			{retVal = SET_PARSER_ERR(totalPack, pack, CT("EXECUTE"), CT("name"), name);
				return ERROR;}	
		if(result == "") 
			{retVal = SET_PARSER_ERR(totalPack, pack, CT("EXECUTE"), CT("result"), result);
				return ERROR;}	

		PHelper helper;
		helper.AddFirst("DISPLAY_REDIR");
		AHE ahe = helper.WhatIs(out);

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC2>(CT("<EXECUTE>"));
		N2BFC2* cmd = (N2BFC2*) pack.pCmd;
		pack.namePack = CT("EXECUTE");
		cmd->i_var[0] = (ahe == AHE_TOKEN) ? helper.GetValue() : 0; // out
		cmd->s_var[0] = name;
		cmd->s_var[1] = param;
		cmd->s_var[2] = result;
		pack.signature.value = SIGN_PROCC(CMD_EXECUTE);
			
		totalPack.push_back(pack);  return retVal;
	}


////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("EXIT"))
	{
		std_string name = px->getValue(CT( "name"));
		std_string write = px->getValue(CT( "write"));
		if(name.empty())
			name = write;
		pack.namePack = name;
		pack.signature.value = SIGN_PROCC(CMD_EXIT);
			
		totalPack.push_back(pack);  return retVal;
	}	

////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("TIMER"))
	{
		std_string name = px->getValue(CT("name"));
		std_string command = px->getValue(CT("command"));
		std_string value = px->getValue(CT("value"));
		
		if(name == "") 
			{retVal = SET_PARSER_ERR(totalPack, pack, CT("TIMER"), CT("name"), name);
				return ERROR;}	
		if(command == "") 
			{retVal = SET_PARSER_ERR(totalPack, pack, CT("TIMER"), CT("command"), command);
				return ERROR;}	

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC2>(CT("<TIMER>"));
		N2BFC2* cmd = (N2BFC2*) pack.pCmd;

		PHelper helper;
		helper.AddFirst("TIMER0", 0);
		helper.Add("TIMER1", 1);
		helper.Add("TIMER2", 2);
		helper.Add("TIMER3", 3);
		helper.Add("TIMER4", 4);
		helper.Add("TIMER5", 5);
		helper.Add("TIMER6", 6);
		helper.Add("TIMER7", 7);
		helper.Add("TIMER8", 8);
		helper.Add("TIMER9", 9);
		helper.Add("TIMER10", 10);
		AHE ahe = helper.WhatIs(name);
		if(ahe != AHE_TOKEN)
				return SET_PARSER_ERR(totalPack, pack, CT("TIMER"), CT("name"), name);
		cmd->i_var[0] = helper.GetValue();
		
		helper.AddFirst("INIT", 0);
		helper.Add("GET", 1);
		helper.Add("RESOLUTION", 2);
		helper.Add("STOP", 3);
		helper.Add("WAIT", 4);
		helper.Add("START", 5);
		ahe = helper.WhatIs(command);
		if(ahe != AHE_TOKEN)
				return SET_PARSER_ERR(totalPack, pack, CT("TIMER"), CT("command"), command);
		cmd->i_var[1] = helper.GetValue();
		
		helper.AddFirst("SEC", 1);
		helper.Add("MS", 0);
		ahe = helper.WhatIs(value);
		cmd->i_var[2] = helper.GetValue();
		
		pack.namePack = (CT("TIMER"));
		pack.signature.value = SIGN_PROCC(CMD_TIMER);
			

		totalPack.push_back(pack);  return retVal;
	}	

////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("WHILE"))
	{
		int var_val = 0;
		std_string var = px->getValue(CT("var"));
		
		if(var == "") 
			{retVal = SET_PARSER_ERR(totalPack, pack, CT("WHILE"), CT("var"), var);
				return ERROR;}	

		PHelper helper;
		helper.AddFirst("TRUE", 1);
		helper.Add("FALSE", 0);
		AHE ahe = helper.WhatIs(var);
		if(ahe == AHE_TOKEN || ahe == AHE_DIGIT)
			var_val = helper.GetValue();		

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC3>(CT("<WHILE>"));
		N2BFC3* cmd = (N2BFC3*) pack.pCmd;

		pack.namePack = CT("WHILE");
		cmd->var = var;
		cmd->val = var_val;
		pack.signature.value = SIGN_PROCC(CMD_WHILE);
			
		totalPack.push_back(pack);  return retVal;
	}	

////////////////////////////////////////////////////////////////
	if(px->nametag  == CT("/WHILE"))
	{
		pack.namePack = CT("/WHILE");
		pack.signature.value = SIGN_PROCC(END_CMD);
		totalPack.push_back(pack);  return retVal;
	}

		
//*****************************************************
//
	if(px->nametag == CT("LOAD_MACRO"))
	{
		if(!pParser_)
			return SET_ANOTHER_ERR(totalPack, pack, CT("Парсер не установлен"));

		std_string file = px->getValue(CT("file"));
		std_string name = px->getValue(CT("name"));
		
		if(file == CT(""))
			return SET_PARSER_ERR(totalPack, pack, CT("LOAD_MACRO"), CT("file"), file);
		if(name == CT(""))
			return SET_PARSER_ERR(totalPack, pack, CT("LOAD_MACRO"), CT("name"), name);
				
		try{
			std_string errDescr;
			CFS* pCFS = pParser_->parse(file, errDescr, "MACROS");
			if (pCFS == NULL) {
				return SET_ANOTHER_ERR(totalPack, pack, errDescr);
			}
			// поиск макроса по имени
			XMLF curXML(CT("MACRO")), *tmpXML;
			CFS* tmpNode = pCFS->getChild(&curXML);
			if(!tmpNode) 
				return SET_ANOTHER_ERR(totalPack, pack, CT("Макрос не найден!"));
			
			bool find = false;
			///* Прописывем метку начала загруженного макроса*/
			//XMLF begin("LOAD_MACRO_BEGIN");
			//begin.tag = N2_XMLFTAG_SINGLE;
			//ATTR atrb("name", name);
			//begin.attr.push_back(atrb);
			//CFSC maker;
			//CFS* pBegCFS = maker.createNode();
			//pBegCFS->setData(&begin);
			//unpack(pBegCFS);
			///*   */
			while(tmpNode) {
				tmpXML = tmpNode->getData();
				if(tmpXML && tmpXML->find(CT("name"), name)) {
					// распаковка макроса в вектор команд
					find = true;
					if(!unpack(tmpNode))
					throw "Tmd"; // пока так
				}
				tmpNode = pCFS->getNextChild();
			}

			if(!find) 
					return SET_ANOTHER_ERR(totalPack, pack, CT("Макрос не найден!"));

		}//try
		catch(...) {
			std_string de(CT("Исключение при загрузке макроса - ") + name + \
							std_string(CT("  из файла - ")) + file);
			return SET_ANOTHER_ERR(totalPack, pack, de);
		}

		pack.namePack = CT("Макрос \"") + name + CT("\" загружен!");
		pack.signature.value = SIGN_PROCC(CMD_LOADED_MACRO);
		totalPack.push_back(pack);  return retVal;
	}	


////*****************************************************
//// 
//	if(px->nametag == CT("LOAD_MACRO_BEGIN"))
//	{
//		pack.namePack = px->getValue(CT("name"));
//		pack.signature.value = SIGN_PROCC(CMD_LOAD_MACRO_BEGIN);
//		totalPack.push_back(pack);  return retVal;
//	}	

//*****************************************************
// 
	if(px->nametag == CT("FORMAT_CONST"))
	{
		std_string nw = px->getValue(CT("new"));
		std_string prefix = px->getValue(CT("prefix"));
		std_string var = px->getValue(CT("var"));
		std_string postfix= px->getValue(CT("postfix"));
		std_string symbol= px->getValue(CT("symbol"));
		
		if(nw == EMPTY_STR || var == EMPTY_STR) 
			{
			retVal = SET_PARSER_ERR(totalPack, pack, CT("FORMAT_CONST"), CT((nw=="")?"nw":"var"), (nw=="")?nw:var);
			return ERROR;}
	
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC_ARRAY_STRING>(CT("<FORMAT_CONST>"));
		N2BFC_ARRAY_STRING* cmd = (N2BFC_ARRAY_STRING*) pack.pCmd;		
		pack.namePack = nw;
		cmd->add(prefix);
		cmd->add(var);
		cmd->add(postfix);
		cmd->add(symbol);

		pack.signature.value = SIGN_PROCC(CMD_FORMAT_CONST);		
		
	totalPack.push_back(pack);  return retVal;
	}	
//*****************************************************
//
	if(px->nametag  == CT("MACRO"))
	{
		pack.namePack = px->getValue(CT("name"));
		pack.signature.value = SIGN_PROCC(CMD_MACRO);		
		totalPack.push_back(pack);  return retVal;	
	}

	if(px->nametag  == CT("/MACRO"))
	{
		pack.namePack = px->getValue(CT("name"));
		pack.signature.value = SIGN_PROCC(END_MACRO);		
		totalPack.push_back(pack);  return retVal;	
	}

//*****************************************************
	if(px->nametag == CT("PRAGMA"))
	{
		std_string param = px->getValue(CT( "param"));
		std_string value = px->getValue(CT( "value"));
		int val = 0;
		
		if(param == EMPTY_STR)
			{retVal = SET_PARSER_ERR(totalPack, pack, CT("PRAGMA"), CT("param"), param);
			return ERROR;}
		
		PHelper helper;
		helper.AddFirst("ERROR_REDECLARE", PRAGMA_ERROR_REDECLARE);
		helper.AddFirst("AUTOCASTING", PRAGMA_AUTOCASTING);
		AHE ahe = helper.WhatIs(param);
		if(ahe != AHE_TOKEN) {
				retVal = SET_PARSER_ERR(totalPack, pack, CT("PRAGMA"), CT("param"), param);
				return ERROR;
			}	
		
		helper.AddFirst("ON", 1);
		helper.Add("OFF", 0);
		ahe = helper.WhatIs(value);
		if(ahe == AHE_TOKEN || 	ahe == AHE_DIGIT) {
			val = helper.GetValue();
		}
		else {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("PRAGMA"), CT("value"), value);
			return ERROR;}								

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC3>(CT("<PRAGMA>"));
		N2BFC3* cmd = (N2BFC3*) pack.pCmd;		

		cmd->var = param;
		cmd->val = val;
		pack.signature.value = SIGN_PROCC(CMD_PRAGMA);
		totalPack.push_back(pack);  return retVal;
	}		

//*****************************************************
	if(px->nametag == CT("CAST"))
	{
		std_string op1, op2;

		op1 = px->getValue(CT( "op1"));
		op2 = px->getValue(CT( "op2")); 

		if(op1 == EMPTY_STR || op2 == EMPTY_STR) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("CAST"), CT("op1 or op2"), ((op1 == EMPTY_STR) ? op1 : op2));
			return ERROR;
		}

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC3>(CT("<CAST>"));
		N2BFC3* cmd = (N2BFC3*) pack.pCmd;	

		pack.signature.value = SIGN_PROCC(CMD_CAST);
		pack.namePack = op1;
		cmd->var = op2;
		
		totalPack.push_back(pack);  return retVal;
	}	

//*****************************************************
// 13.05.11
	if(px->nametag == CT("OPEN_DEVICE"))
	{
		std_string op1, op2;

		std_string sign = px->getValue(CT("sign"));
		std_string ok = px->getValue(CT("ok")); 
		std_string handle = px->getValue(CT("handleName")); 
		std_string param = px->getValue(CT( "param")); 
		std_string num = px->getValue(CT( "numDevice")); 
		std_string oblig = px->getValue(CT( "obligative")); 
		UINT_N2 unum, usign, uparam, uoblig;


		if(handle == EMPTY_STR) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("OPEN_DEVICE"), CT("handleName"), handle);
			return ERROR;
		}
		
		// первый операнд (с кодом операции)
		PHelper helper;
		helper.AddFirst("AUTO", FD_AUTO);
		helper.Add("MANUAL", FD_MANUAL);
		AHE ahe = helper.WhatIs(param);
		uparam = (ahe == AHE_TOKEN) ? helper.GetValue() : FD_AUTO;
		helper.Reset();

		helper.AddFirst("YES", 1);
		helper.Add("NO", 0);
		helper.Add("TRUE", 1);
		helper.Add("FALSE", 0);
		if(helper.WhatIs(oblig) == AHE_TOKEN)
			uoblig = helper.GetValue();
		else
			uoblig = 1; // по умолчанию

		if(helper.WhatIs(sign) != AHE_DIGIT) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("OPEN_DEVICE"), CT("sign"), sign);
			return ERROR;										
		}
		usign = helper.StoI(sign, RC_HEX);
		unum = helper.StoI(num);

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC2>(CT("<CAST>"));
		N2BFC2* cmd = (N2BFC2*) pack.pCmd;

		pack.signature.value = SIGN_PROCC(CMD_OPEN_DEVICE);
		cmd->s_var[0] = handle;
		cmd->s_var[1] = ok;
		cmd->s_var[2] = sign;
		cmd->i_var[0] = uoblig;
		cmd->i_var[1] = uparam;
		cmd->i_var[2] = unum;

		totalPack.push_back(pack);  return retVal;
	}	
		
//*****************************************************
	if(px->nametag  == CT("CLOSE_DEVICE"))
	{
		std_string handle = px->getValue(CT( "handleName")); 

		if(handle == EMPTY_STR) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("OPEN_DEVICE"), CT("handleName"), handle);
			return ERROR;
		}
		
		pack.namePack = handle;
		pack.signature.value = SIGN_PROCC(CMD_CLOSE_DEVICE);
		
		totalPack.push_back(pack);  return retVal;
	}			

//*****************************************************
	if(px->nametag == CT("DEVICE"))
	{
		std_string handle = px->getValue(CT( "handleName")); 

		if(handle == EMPTY_STR) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("DEVICE"), CT("handleName"), handle);
			return ERROR;
		}
		
		pack.namePack = handle;
		pack.signature.value = SIGN_PROCC(CMD_DEVICE);
		
		totalPack.push_back(pack);  return retVal;
	}			

//*****************************************************
	if(px->nametag == CT("/DEVICE"))
	{
		pack.signature.value = SIGN_PROCC(CMD_DEVICE_END);
		
		totalPack.push_back(pack);  return retVal;
	}			

//*****************************************************
	if(px->nametag == CT("MARK"))
	{
		std_string name = px->getValue(CT("name")); 

		if(name == EMPTY_STR) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("MARK"), CT("name"), name);
			return ERROR;
		}
		
		pack.namePack = name;
		pack.signature.value = SIGN_PROCC(CMD_MARK);
		
		totalPack.push_back(pack);  return retVal;
	}	

//*****************************************************
	if(px->nametag == CT("GOTO"))
	{
		std_string mark = px->getValue(CT("mark")); 

		if(mark == EMPTY_STR) {
			retVal = SET_PARSER_ERR(totalPack, pack, CT("MARK"), CT("mark"), mark);
			totalPack.push_back(pack);  return retVal;
		}
		
		pack.namePack = mark;
		pack.signature.value = SIGN_PROCC(CMD_GOTO);
		
		totalPack.push_back(pack);  return retVal;
	}	

//*****************************************************
	if(px->nametag  == CT("CON_WRITE") ||
		px->nametag  == CT("DEBUG"))
	{
		std_string wr = px->getValue(CT("write"));
		std_string form = px->getValue(CT("format"));
		std_string overwrite = px->getValue(CT("overwrite"));
		std_string typewr = px->getValue(CT("type"));

		pack.namePack = wr;
		//pack.signature.value = SIGN_CONSOLE(((px->nametag==CT("CON_WRITE")) ? CMD_CON_WRITE : CMD_CON_DEBUG));
		pack.signature.img2.code = (px->nametag == CT("CON_WRITE")) ? CMD_CON_WRITE : CMD_CON_DEBUG;
		pack.signature.img2.devClass = N2_CONSOLE;

		PHelper hlp;
		hlp.AddFirst("HEX", IFV_HEX);
		hlp.Add("DEC", IFV_DEC);
		hlp.Add("BIN", IFV_BIN);
		if(hlp.WhatIs(form) == AHE_TOKEN)
			pack.ret_value = hlp.GetValue();
		else
			pack.ret_value = IFV_DEC;
		int type = TCW_GEN;
		if (!typewr.empty())
		{
			hlp.ClearTokens();
			hlp.AddFirst("GEN", TCW_GEN);
			hlp.Add("TXT", TCW_TXT);
			hlp.Add("VAR", TCW_VAR);
			hlp.Add("VAL", TCW_VAL);
			if (hlp.WhatIs(typewr) == AHE_TOKEN)
				type = hlp.GetValue();
		}
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC_ARRAY_INT>(CT("<N2BFC_ARRAY_STRING>"));
		N2BFC_ARRAY_INT* cmd = (N2BFC_ARRAY_INT*)pack.pCmd;
		cmd->add(overwrite == "YES" ? 1 : 0);
		cmd->add(type);

	    totalPack.push_back(pack);  return retVal;
	}

//*****************************************************
	if(px->nametag  == CT("CON_LOG"))
	{
		std_string wr = px->getValue(CT("write"));
		
		pack.namePack = wr;
		pack.signature.value = SIGN_CONSOLE(CMD_CON_LOG);

	totalPack.push_back(pack);  return retVal;
	}

//*****************************************************
	if(px->nametag  == CT("USE_GLOBAL"))
	{
		std_string var = px->getValue(CT("var"));
		
		pack.namePack = var;
		pack.signature.value = SIGN_PROCC(CMD_USE_GLOBAL);
		if(var == EMPTY_STR) {
			SET_PARSER_ERR(totalPack, pack, CT("USE_GLOBAL"), CT("var"), var);
			return ERROR;
		}

	totalPack.push_back(pack);  return retVal;
	}

//*****************************************************
	if(px->nametag  == CT("TABLE") ||
		px->nametag  == CT("VAR_TABLE"))
	{
		std_string type = px->getValue(CT("type"));
		std_string name = px->getValue(CT("name"));
		std_string value = px->getValue(CT("value"));
		std_string row = px->getValue(CT("row"));
		std_string column = px->getValue(CT("column"));
		TYPE_VAR tv;

		if(!checkType(type, tv))
			return SET_PARSER_ERR(totalPack, pack, px->nametag, CT("type"), type);

		if(name == EMPTY_STR) 
			return SET_PARSER_ERR(totalPack, pack, px->nametag, CT("name"), name);

		N2DeclareBFC2* bfc2= new N2DeclareBFC2;
		pack.pCmd = bfc2;
		bfc2->type = tv;
		PHelper helper;
		switch(helper.WhatIs(row)) {
			case AHE_DIGIT: 
				bfc2->row = helper.GetValue();
				break;
			case AHE_VARIABLE:
				bfc2->s_row = row;
			default: {
				return SET_PARSER_ERR(totalPack, pack, px->nametag, "row", row);
			}
		}
		switch(helper.WhatIs(column)) {
			case AHE_DIGIT: 
				bfc2->column = helper.GetValue();
				break;
			case AHE_VARIABLE:
				bfc2->s_column = row;
			default: {
				return SET_PARSER_ERR(totalPack, pack, px->nametag, "column", column);
			}
		}
		bfc2->s_value = value;
		pack.namePack = name;
		pack.signature.value = SIGN_PROCC(CMD_TABLE);

	totalPack.push_back(pack);  return retVal;
	}

//*****************************************************
	if(px->nametag  == CT("TABULAR"))
	{
		std_string table = px->getValue(CT("table"));
		std_string var = px->getValue(CT("var"));
		std_string code = px->getValue(CT("code"));
		std_string row = px->getValue(CT("row"));
		std_string column = px->getValue(CT("column"));

		if(var == EMPTY_STR) 
			return SET_PARSER_ERR(totalPack, pack, px->nametag, CT("var"), var);
		if(table == EMPTY_STR) 
			return SET_PARSER_ERR(totalPack, pack, px->nametag, CT("table"), table);
		if(code == EMPTY_STR) 
			return SET_PARSER_ERR(totalPack, pack, px->nametag, CT("code"), code);


		N2BFC_ARRAY_STRING* pCmd = new N2BFC_ARRAY_STRING;
		pack.pCmd = pCmd;
		pCmd->add(table);
		pCmd->add(var);		
		pCmd->add(row);
		pCmd->add(column);
		pCmd->add(code);

		pack.namePack = var;
		pack.signature.value = SIGN_PROCC(CMD_TABULAR);

		totalPack.push_back(pack);  return retVal;
	}

//*****************************************************
	if(px->nametag == CT("GET_FROM_ARRAY") ||
		px->nametag == CT("GFA"))
	{
		std_string var = px->getValue(CT("var"));
		std_string arr = px->getValue(CT("array"));
        std_string index = px->getValue(CT("index"));
		
		if(var.empty() || arr.empty()) {
            SET_PARSER_ERR(totalPack, pack, CT("GET_FROM_ARRAY"), var.empty()?CT("var"):CT("array"), \
				var.empty()?var:arr);
			return ERROR;
		}
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC_ARRAY_STRING>(CT("<GFA>"));
		N2BFC_ARRAY_STRING* pCmd = (N2BFC_ARRAY_STRING*)pack.pCmd;

		pCmd->add(var);
		pCmd->add(arr);
        pCmd->add(index);
		
		pack.signature.value = SIGN_PROCC(CMD_GFA);	
	
		totalPack.push_back(pack);  return retVal;
	}

	
//*****************************************************
	if(px->nametag == CT("SET_TO_ARRAY") ||
		px->nametag == CT("STA"))
	{
		std_string value = px->getValue(CT("value"));
		std_string arr = px->getValue(CT("array"));
        std_string index = px->getValue(CT("index"));
		
		if(arr.empty()) {
            SET_PARSER_ERR(totalPack, pack, CT("STA"), CT("array"), arr);
			return ERROR;
		}
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC_ARRAY_DUX>(CT("<STA>"));
		N2BFC_ARRAY_DUX* pCmd = (N2BFC_ARRAY_DUX*)pack.pCmd;

		// arr
		pCmd->add(arr, 0);
		// index
		PHelper helper;
		AHE ahe = helper.WhatIs(index);
		if(ahe == AHE_VARIABLE)
			pCmd->add(index, 0);
		else if(ahe == AHE_DIGIT)
			pCmd->add(EMPTY_STR, helper.GetValue());
		else {
            SET_PARSER_ERR(totalPack, pack, CT("STA"), CT("array"), arr);
			return ERROR;
		}
		// value
		pCmd->add(value, 0);
        
		pack.signature.value = SIGN_PROCC(CMD_STA);	
	
		totalPack.push_back(pack);  return retVal;
	}

//*****************************************************
	if(px->nametag == CT("RIBBON_TO_ARRAY"))
	{
		std_string arr = px->getValue(CT("array"));
		
		if(arr.empty()) {
            SET_PARSER_ERR(totalPack, pack, CT("RIBBON_TO_ARRAY"), CT("array"), arr);
			return ERROR;
		}
        
		PHelper helper;
		helper.SetDelimiter(" ,;");
		helper.HashString(px->body);

		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC_ARRAY_STRING>(CT("<RIBBON_TO_ARRAY>"));
		N2BFC_ARRAY_STRING* pCmd = (N2BFC_ARRAY_STRING*)pack.pCmd;
		
		std_string s = helper.GetFirstFlag();
		while (s != EMPTY_STR) {
			pCmd->add(s);
			s = helper.GetNextFlag();
		}

		pack.namePack = arr;
		pack.signature.value = SIGN_PROCC(CMD_RIBBON_TO_ARRAY);	
	
		totalPack.push_back(pack);  return retVal;
	}
//*****************************************************

	if(px->nametag == CT("SET_GLOBAL"))
	{
		std_string var = px->getValue(CT("var"));
		std_string value = px->getValue(CT("value"));
        std_string index = px->getValue(CT("index"));
		
		if(var.empty() || value.empty()) {
            SET_PARSER_ERR(totalPack, pack, CT("SET_GLOBAL"), var.empty()?CT("var"):CT("value"), \
				var.empty()?var:value);
			return ERROR;
		}
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC_ARRAY_STRING>(CT("<SET_GLOBAL>"));
		N2BFC_ARRAY_STRING* pCmd = (N2BFC_ARRAY_STRING*)pack.pCmd;

		pCmd->add(var);
		pCmd->add(value);
        pCmd->add(index);
		
		pack.signature.value = SIGN_PROCC(CMD_SET_GLOBAL);	
	
		totalPack.push_back(pack);  return retVal;
	}
//*****************************************************

	if(px->nametag == CT("SET_GLOBAL_TABLE"))
	{
		std_string var = px->getValue(CT("var"));
		std_string value = px->getValue(CT("value"));
        std_string row = px->getValue(CT("row"));
		std_string column = px->getValue(CT("column"));
		
		if(var.empty() || value.empty()) {
            SET_PARSER_ERR(totalPack, pack, CT("SET_GLOBAL_TABLE"), var.empty()?CT("var"):CT("value"), \
				var.empty()?var:value);
			return ERROR;
		}
		pack.pCmd = N2Register::self()->getMemoryAllocator()->create<N2BFC_ARRAY_STRING>(CT("<SET_GLOBAL_TABLE>"));
		N2BFC_ARRAY_STRING* pCmd = (N2BFC_ARRAY_STRING*)pack.pCmd;

		pCmd->add(var);
		pCmd->add(value);
        pCmd->add(row);
		pCmd->add(column);
		
		pack.signature.value = SIGN_PROCC(CMD_SET_GLOBAL);	
	
		totalPack.push_back(pack);  return retVal;
	}
//*****************************************************	
	
	
	retVal = NOT_FOUND;
	return retVal;
}


bool 
N2DissInternal::checkType(std_string type, TYPE_VAR& tv)
{
	PHelper helper;
	helper.AddFirst("INT", VAR_INT);
	helper.Add("BOOL", VAR_BOOL);
	helper.Add("FLOAT", VAR_FLOAT);
	helper.Add("LONG", VAR_LONG);
	helper.Add("STRING", VAR_STRING);
	helper.Add("TERNAR", VAR_TERNAR);
	helper.Add("TERN", VAR_TERNAR);
	if(helper.WhatIs(type) != AHE_TOKEN) {
		tv = VAR_UNDEFINED;
		return false;
	}
	tv = (TYPE_VAR) helper.GetValue();
	return true;
}


N2Dissection::RESULT_DECODE
N2DissTotal::decode(XMLF* px, vector<DataPack>& pack)
{
	RESULT_DECODE retVal = NOT_FOUND;

	//retVal = inter_.decode(px, pack);

	//if(retVal != N2Dissection::NOT_FOUND)
	//	return retVal;

	//for(size_t i=0; i<vecExpand_.size(); i++) {
	//	N2Dissection::RESULT_DECODE temp = vecExpand_[i]->decode(px, pack);
	//	if(temp != N2Dissection::NOT_FOUND)
	//		retVal = temp;
	//}
		
	for(size_t i=0; i<vecExpand_.size(); i++) {
		vector<DataPack> tmpPack;
		retVal = vecExpand_[i]->decode(px, tmpPack);
		for(size_t p=0; p<tmpPack.size(); p++)
			pack.push_back(tmpPack[p]);
		tmpPack.clear();
	}
	return retVal;
}


N2DissTotal::N2DissTotal()
{
	vecExpand_.push_back(&inter_);
}


bool 
N2DissTotal::addDissector(N2Dissection* pDiss)
{
	if(!pDiss)
		return false;
	vecExpand_.push_back(pDiss);
	return true;
}


N2DissTotal::~N2DissTotal()
{
	resetExternalDissectors();
}


void
N2DissTotal::resetExternalDissectors(void)
{
	for(size_t i=0; i<vecExpand_.size(); i++) {
		if(vecExpand_[i] != NULL)
			delete vecExpand_[i];
	}
	vecExpand_.clear();
}


bool 
N2DissTotal::unpackWhole(CFS* pCFS, VectorCommand* vecComm)
{
	N2Dissection::setOrder(vecComm);
	return unpack(pCFS);
}

