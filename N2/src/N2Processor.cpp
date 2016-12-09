///////////////////////////////////////////////////////////
//
//  N2Processor.cpp
//
//	Наименование:  	
//  Описание:		
//
//  Дата создания:  19.04.2006
//  Автор:			Чихичин Д.А.
//  
///////////////////////////////////////////////////////////
//  История изменений:
//  
//
///////////////////////////////////////////////////////////

#include "include/N2Processor.h"
#include "../../export/common/N2Commands.h"
//#include <process.h>
#include <time.h>
#include "N2PHelper.h"


N2Processor::N2Processor():
	pModsMan_(NULL)
{
	current_command_in_proccess = NULL;
	srand(::clock());
	//handle_device = false;
	initial = false;
	fatal_error = false;
	pragma = 0;
}


N2Processor::~N2Processor()
{
#ifdef INSTRUCTION_PROFILER
	N2Register::self()->log()->ProfilerStop();
#endif
}


#define GET_DEVICE_SIGN(x) (x & 0x00FFFFFF)

#define GET_TYPE(x) (x & 0xFF)

//
#define COMMAND_TO_PROCESSOR(x) CHECK_CLASS(x, N2_PROCESSOR)
#define COMMAND_TO_DISPLAY(x)  CHECK_CLASS(x, N2_CONSOLE)
//#define COMMAND_TO_HANDLE(x) CHECK_CLASS(x, N2_PROCESSOR)


//////////////


/* ИСПОЛНИТЕЛЬ */
bool N2Processor::tick(/*Order* order*/)
{
	if(!initial)
		return false;

	DataPack* tc;
	if(queue_empty)
			return false;
	tc = pOrder_->GetExecuteCommand();
	current_command_in_proccess = tc;
	if(!tc) 
		{
		queue_empty = true;
		N2Register::self()->log()->WriteError("N2Processor::Clock",0, "Пустая очередь или ошибка исполнения теста");
		/* ошибка в журнал */
		return false;
		}

	int nd = 0;

#ifdef INSTRUCTION_PROFILER
	N2Register::self()->log()->ProfilerInit(&pOrder_, pOrder_->GetSizeOrder());
	clock_t b, e;
	b = clock();
#endif

	// Флаг определяющий необходимость инкрементирования счетчика команд.
	bool binc = true;

	//if(tc->signature.img2.devClass == 0) {
	//	OnProcedureProcessError(std_string("Нулевая сигнатура команды : ") + tc->nameTag, tc->signature.value, true);
	//	return true;
	//}

	/**/
	Response response;

	switch (tc->signature.img2.devClass)
	{
	case 0: 
		OnProcedureProcessError(std_string("Нулевая сигнатура класса устройства : ") + tc->nameTag, tc->signature.value, true);
		break;
    case N2_PROCESSOR:
		binc = SelfExec(tc);
		break;
	case N2_CONSOLE:
	case N2_DEBUGER:
	case N2_SYSTEM:
		if( ! pModsMan_->AutoExecuteCommand(tc, response) ) {			
			OnProcedureProcessError(std_string("Устройство для исполнения не найдено : ") + tc->nameTag, tc->signature.value, true);
		}
		if(response.err_ != OK) 
			onErrorHappened(tc, response);
		break;
	default:
		if(!stackHands.empty()) {
			tc->signature.img2.devClass = (WORD_N2)stackHands.top().pModule->getSignature(); 
			tc->signature.img2.numDev = stackHands.top().numberDevice;
		}
		else
			tc->signature.img2.numDev = N2_ACTIVE_DEVICE;

		if( ! pModsMan_->AutoExecuteCommand(tc, response) ) {			
			OnProcedureProcessError(std_string("Устройство для исполнения не найдено : ") + tc->nameTag, tc->signature.value, true);
		}
		if(response.err_ != OK) 
			onErrorHappened(tc, response);
		break;
	}

	/**/
	//if(COMMAND_TO_PROCESSOR(tc->signature.value)) 
	//	binc = SelfExec(tc);

	//else  { //	Отсылаем устройству{ 
	//	if(!stackHands.empty()) {
	//		//if(tc->signature.img2.devClass == stackHands.top().pModule->getSignature()) {
	//		if(tc->signature.img2.devClass != N2_PROCESSOR &&
	//			tc->signature.img2.devClass != N2_CONSOLE &&
	//			tc->signature.img2.devClass != N2_DEBUGER && 
	//			tc->signature.img2.devClass != N2_SYSTEM) {
	//				
	//				tc->signature.img2.devClass = (WORD_N2)stackHands.top().pModule->getSignature(); 
	//				tc->signature.img2.numDev = stackHands.top().numberDevice;
	//		}
	//	}
	//	else 
	//		tc->signature.img2.numDev = N2_ACTIVE_DEVICE;
	//	int err = 0;
	//	Response response;
	//	if( ! pModsMan_->AutoExecuteCommand(tc, response) ) {
	//		N2Register::self()->log()->WriteError("N2Processor::tick", err, "Устройство для исполнения не найдено!");
	//	}
	//	if(response.err_ != OK) 
	//		onErrorHappened(tc, response);
	//	binc = true;
	//}

#ifdef INSTRUCTION_PROFILER
	e = clock();
	N2Register::self()->log()->Profiler(tc, pOrder_->GetCIP(), e - b);
#endif
	
	if (binc)
	    pOrder_->IncCIP();
	
	// это VVVVV неправильно переделать 
	return true;
}



bool N2Processor::inject(DataPack* pack)
{
	if(pack->signature.img2.devClass == N2_PROCESSOR) 
		SelfExec(pack);
	else  { //	Отсылаем устройству 
		int err = 0;
		pack->signature.img2.numDev = N2_ACTIVE_DEVICE;
		Response resp;
		if( ! pModsMan_->AutoExecuteCommand(pack, resp) ) {
			N2Register::self()->log()->WriteError("N2Processor::inject", err, "Устройство для исполнения не найдено!");
			return false;
		}
		if(resp.err_ != OK)
			onErrorHappened(pack, resp);
	}	
	return true;
}


bool N2Processor::SelfExec(DataPack *tc)
{
    if(!initial)
        return false;

    const std_string head = std_string(CT("Команда - ")) + tc->nameTag + CT(" : ");

    switch(tc->signature.img1.code)
    {
    case 0:
        {
        } break;
    case CMD_TASK: // начало задачи
        {
        //vars.Clear();
        cur_USID = tc->namePack;
        N2Register::self()->log()->Write(std_string("Начало задачи - ") + tc->namePack);
        step_log = true;
        //
        DataPack dp;
        Response resp;
        dp.namePack = tc->namePack;
        dp.signature.value =  MAKE_CODE(CMD_PROCESSOR_EVENT, N2_CONSOLE);
        pModsMan_->AutoExecuteCommand(&dp, resp);
        } break;

    case CMD_TASK_END: // конец задачи
        {
        N2Register::self()->log()->Write(std_string("Конец задачи - ") + tc->namePack);
        cur_USID = "";
        //vars.Clear();
        } break;

    case CMD_STEP: // начало шага
        {
        if(step_log)
            if(tc->namePack != EMPTY_STR)
                N2Register::self()->log()->Write(tc->namePack.c_str());
        nameStep = tc->namePack;
        //
        DataPack dp;
        Response resp;
        dp.namePack = tc->namePack;
        dp.signature.value =  MAKE_CODE(CMD_PROCESSOR_EVENT, N2_CONSOLE);
        pModsMan_->AutoExecuteCommand(&dp, resp);
        } break;
    case CMD_STEP_END: // конец шага
        {
        // empty
        } break;

    case 5: // включение
        {
        step_log = true;
        } break;

    case 6: // отключение
        {
        step_log = false;
        } break;

    case 7: // заголовочный пакет очереди команд
        {
            queue_empty = false;
        } break;

    /// условная команда IF
//	case CMD_IF:
//		{
//		bool sol = false;
//		N2BFC1* cmd = (N2BFC1*)tc->pCmd;

//		N2BaseVariable* pVar1 = manVars.getVar(cmd->nameVariable1);
//		if(!pVar1) {
//				OnProcedureProcessError(head + "Переменной " + cmd->nameVariable1 +" не существует!", tc->signature.value, true);
//				break;
//			}

//		if(cmd->nameVariable2 != EMPTY_STR &&
//			cmd->codeCompare != N2COMPARE_UNDEFINE) {
			
//			N2BaseVariable* pVar2 = manVars.getVar(cmd->nameVariable2);
//			if(!pVar2) {
//				//проверка числового значения
//				PHelper helper;
//				helper.AddFirst("TRUE", 1);
//				helper.Add("FALSE", 0);
//				AHE ahe = helper.WhatIs(cmd->nameVariable2);
//				if(ahe == AHE_TOKEN ||
//					ahe == AHE_DIGIT) {
//						N2VariableCreator maker;
//						pVar2 = maker.createSimplex(pVar1->type());
//						int x = helper.GetValue();
//						pVar2->setVoid(&x);   /////// ?????????????
//				}
//			}
//			//else {
//			//	OnProcedureProcessError("значение атрибута value в команде IF недопустимо!", tc->signature.value, false);
//			//	break;
//			//}
//			sol = pVar1->compare(cmd->codeCompare, pVar2);
//		}
//		else {
			
//			if(!pVar1) {
//				//проверка числового значения
//				PHelper helper;
//				helper.AddFirst("TRUE", 1);
//				helper.Add("FALSE", 0);
//				AHE ahe = helper.WhatIs(cmd->nameVariable1);
//				if(ahe == AHE_TOKEN ||
//					ahe == AHE_DIGIT) {
//						sol = !!helper.GetValue();
//				}
//				else {
//					OnProcedureProcessError(head + "Переменной " + cmd->nameVariable1 +" не существует!", tc->signature.value, true);
//					break;
//				}
//			}
//			switch(pVar1->type()) {
//				case VAR_INT: sol = !! *((N2VariableINT*)pVar1)->get();
//					break;
//				case VAR_BOOL: sol = *((N2VariableBOOL*)pVar1)->get();
//					break;
//				default:
//					OnProcedureProcessError("Неверный тип переменной!", \
//						tc->signature.value, true);
//			}
//		}
//		// принятие решения
//		if(!sol)
//			{
//			pOrder_->JumpWithCurrent();
//			return false;
//			}
//		} break;



    case 18: // начало блока операторов
        {
        OnProcedureProcessError("Ошибка - начала блока операторов\nИнструкция незаконна!", \
            tc->signature.value, true);
            //return;
        } break;
		
    case END_CMD: // конец блока операторов
        {
            pOrder_->JumpWithCurrent();
            return false;
        } break;
    // ...

//	case CMD_VARIABLE: // Инициализация переменной
//		{
//			if(!tc->pCmd || tc->pCmd->label != N2_BFCDECL) {
//				OnProcedureProcessError(head + (CT("Ошибка создания переменной")) + tc->namePack, \
//					tc->signature.value, false);
//				break;
//			}
		
//			N2DeclareBFC* pCmd = (N2DeclareBFC*)tc->pCmd;
//			short size = pCmd->size;
//			if(pCmd->sizeStr != EMPTY_STR) {
//				N2BaseVariable* pVS = manVars.getVar(pCmd->sizeStr);
//				if(!pVS || (pVS->type() != VAR_INT || pVS->type() != VAR_LONG)) {
//					OnProcedureProcessError(head + CT("Переменная массива ") + pCmd->sizeStr + " не найдена.", \
//					tc->signature.value, false);
//					break;
//				}
//				size = maker.getIntFromSimplexVar(pVS);
//			}
//			if(size == 0)
//				size = 1;
//			N2BaseVariable* pVar;
//			pVar = maker.createSimplex(pCmd->type, tc->namePack, size);
//			if (pVar)
//			{
//				pVar->setVoid(tc->buffer);
//				if (!pCmd->initVariable.empty())
//				{
//					N2BaseVariable* pVal = manVars.getVar(pCmd->initVariable);
//					if (!pVal) {
//						pVal = maker.createSimplex(VAR_STRING, "tmpX", size);
//						if (pVal)
//							((N2VariableSTR*) pVal)->set(pCmd->initVariable);
//					}
//					if (pVal)
//						pVar->set(pVal);
//				}
//			}

//			if(!manVars.declare(pVar))
//				OnProcedureProcessError(head + ("Переменная \"") + tc->namePack + \
//										std_string ("\" существует или не может быть создана. "), \
//										tc->signature.value, false);

//		} break;


//	case CMD_OPERATION: // Операция с двумя  переменными  <OPERATION>
//		{
//			const std_string title = CT("Команда OPERATION : ");
//			if(!tc->pCmd || tc->pCmd->label != N2_BFCOPER) {
//				OnProcedureProcessError(title + CT("ошибка состава команды"), tc->signature.value, false);
//				break;
//			}
		
//			tc->namePack;
//			N2OperationBFC* pCmd = (N2OperationBFC*)tc->pCmd;
//			N2BaseVariable* pOp1 = manVars.getVar(pCmd->op1);
//			if(!pOp1) { // && (pragma == PRAGMA_ERROR_REDECLARE) ) {
//				OnProcedureProcessError(std_string("Переменная \"") + pCmd->op1 + CT("\" не существует! "), \
//					tc->signature.value, false);
//				break;
//			}
//			N2BaseVariable* pOp2 = manVars.getVar(pCmd->op2);
//			N2BaseVariable* pRes = manVars.getVar(pCmd->opResult);
//			if(!pRes)
//				pRes = pOp1;

//			N2_OPERATING_CODE code = pCmd->code;
//			//
//			if(pOp2) {
//				if(pOp1->type() != pOp2->type()) { // приведение оператора 2 к опер. 1
//					N2BaseVariable* p2 = pOp2;
//					pOp2 = manVars.creator.createSimplex(pOp1->type(), "");
//					if (pOp2) pOp2->set(p2);
//					//OnProcedureProcessError(std_string(CT("Разнотипные операнды!")), \
//					//	tc->signature.value, false);
//				}
//			}
//			else {
//				if(pCmd->op2 != EMPTY_STR) {
//						pOp2 = manVars.creator.createSimplex(pOp1->type(), "%temp");
//						N2BaseVariable* strVar = manVars.creator.createSimplex(VAR_STRING, "%temp2");
//						if(pOp2!=0 && strVar!=0)
//						{
//							((N2VariableSTR*)strVar)->set(pCmd->op2);
//							pOp2->set(strVar);
//						}
//				}
//			}
//			if(pRes->type() != pOp1->type()) {
//				OnProcedureProcessError(std_string(CT("Неверный тип результата!")), \
//					tc->signature.value, false);
//			}
//			// операция
//			N2_ERRORS_OPCODES erc = pOp1->operation(code, pOp2, pRes);
//			if(erc != N2EC_SUCCESS)
//				OnProcedureProcessError(std_string(CT("Операция над типами невыполнима!")), \
//				tc->signature.value, false);

//		} break;


//	case CMD_FOR: // FOR
//		{
//		int end = 0;
//		int step = 0;
//		int beg = 0;
//		N2BFC2* cmd = (N2BFC2*)tc->pCmd;
//		PHelper help;
//		N2BaseVariable* pTemp = NULL;
//		N2VariableCreator creator;
//		N2VariableINT* pIv = (N2VariableINT*) creator.createSimplex(VAR_INT);
//		if (!pIv)
//			return false;
//		// begin
//		if(cmd->s_var[0] == EMPTY_STR)
//			beg = cmd->i_var[0];
//		else {
//			pTemp = manVars.getVar(cmd->s_var[0]);
//			if (!pTemp)
//			{
//				OnProcedureProcessError(std_string(CT("Нет переменной начала цикла FOR")), \
//					tc->signature.value, true);
//				break;
//			}
//			beg = pIv->custom(pTemp);
//		}
	
//		// end
//		if(cmd->s_var[1] == EMPTY_STR)
//			end = cmd->i_var[1];
//		else {
//			pTemp = manVars.getVar(cmd->s_var[1]);
//			if (!pTemp)
//			{
//				OnProcedureProcessError(std_string(CT("Нет переменной конца цикла FOR")), \
//					tc->signature.value, true);
//				break;
//			}
//			end =pIv->custom(pTemp);
//		}

//		// step
//		if(cmd->s_var[2] == EMPTY_STR)
//			step = cmd->i_var[2];
//		else {
//			pTemp = manVars.getVar(cmd->s_var[2]);
//			if (!pTemp)
//			{
//				OnProcedureProcessError(std_string(CT("Нет переменной шага цикла FOR")), \
//					tc->signature.value, true);
//				break;
//			}
//			step = pIv->custom(pTemp);
//		}
	
//		//
//		pTemp = manVars.getVar(tc->namePack);
//		if (!pTemp || pTemp->type() != VAR_INT)
//		{
//			OnProcedureProcessError(std_string(CT("Переменная цикла FOR должна быть типа INT")), \
//				tc->signature.value, true);
//			break;
//		}
//		// исчисление переходов
//		if(pOrder_->CurrentIsActive()) {
//			if(!pTemp) {
//				pIv->rename(tc->namePack);
//				pTemp = pIv->clone();
//				manVars.declare(pTemp);
//			}
//			((N2VariableINT*)pTemp)->set(beg);
//			pOrder_->ResetActivityOfCurrent();
//		}
//		else
//			{
//			if (!pTemp)
//			{
//				OnProcedureProcessError(std_string(CT("Переменная цикла FOR удалена или не существует")), \
//					tc->signature.value, true);
//				break;
//			}
//			int curv;
//			curv = *((N2VariableINT*)pTemp)->get();
//			if(cmd->dec ? ((curv - step) < end) : ((curv + step) > end))
//				{
//				//vars.Delete(tc->namePack);
//				pOrder_->SetActivityOfCurrent();
//				pOrder_->JumpWithCurrent();
//				return false;
//				}
//			else
//				{
//				int temp = cmd->dec ? (curv - step) : (curv + step);
//				((N2VariableINT*)pTemp)->set(temp);
//				}
//			}
//		} break;

    case 33: // INSTRUCTION_PROFILER
        {
        #ifdef INSTRUCTION_PROFILER
            N2Register::self()->log()->ProfilerStop();
        #endif
        ResetProcessor();
        queue_empty = true;
        return false;
        } break;

    case CMD_ELSE: // команда ELSE
        {
        // Включено в логику IF
        } break;

//	///////////////////////////////////////////////////////////
//	case CMD_COMPARE:  // COMPARE
//		{
//		N2BFC1* cmd = (N2BFC1*) tc->pCmd;
//		N2BaseVariable* op1 = manVars.getVar(cmd->nameVariable1);
//		N2BaseVariable* op2 = manVars.getVar(cmd->nameVariable2);
//		if(!op1) {
//			OnProcedureProcessError(std_string(CT("Нет переменной op1")), tc->signature.value, true);
//			break;
//		}
//		if (!op2) {
//			if(cmd->nameVariable2 == EMPTY_STR) {
//				OnProcedureProcessError(std_string(CT("Нет переменной op2")), tc->signature.value, true);
//				break;
//			}
//			N2BaseVariable* temp = maker.createSimplex(VAR_STRING);
//			op2 = maker.createSimplex(op1->type());
//			if (temp!=0 && op2!=0)
//			{
//				((N2VariableSTR*)temp)->set(cmd->nameVariable2);
//				op2->set(temp);
//			}
//		}
//		N2BaseVariable* pTemp = manVars.getVar(tc->namePack);
//		if(!pTemp) {
//			OnProcedureProcessError(std_string(CT("Нет переменной для сохранения результата")), \
//				tc->signature.value, true);
//			return false;
//		}
//		if(pTemp->type() != VAR_BOOL) {
//			OnProcedureProcessError(std_string(CT("Переменная для сохранения результата не типа BOOL")), \
//				tc->signature.value, true);
//			return false;
//		}
//		bool res = false;
//		switch(op1->type()) {
//		case VAR_INT:
//			res = ((N2VariableINT*)op1)->compare(cmd->codeCompare, op2);
//			break;
//		case VAR_FLOAT:
//			res = ((N2VariableFLOAT*)op1)->compare(cmd->codeCompare, op2);
//			break;
//		case VAR_LONG:
//			((N2VariableLONG*)op1)->compare(cmd->codeCompare, op2);
//			break;
//		case VAR_STRING:
//			res = ((N2VariableSTR*)op1)->compare(cmd->codeCompare, op2);
//			break;
//		case VAR_BOOL:
//			res = ((N2VariableBOOL*)op1)->compare(cmd->codeCompare, op2);
//			break;
//		case VAR_TERNAR:
//			res = ((N2VariableTO*)op1)->compare(cmd->codeCompare, op2);
//			break;

//		}
		
//		//res = op1->compare(cmd->codeCompare, op2);

//		if(pTemp->type() == VAR_BOOL)
//			((N2VariableBOOL*) pTemp)->set(res);

//		}break;
//	///////////////////////////////////////////////////////////////
//	//case 36:
//	//	{


    ///**/
    case CMD_BREAK : // BREAK
        {
        pOrder_->JumpWithCurrent();
        unsigned int cp = pOrder_->GetCIP();
        pOrder_->DecCIP();
        pOrder_->JumpWithCurrent();
        pOrder_->SetActivityOfCurrent();
        pOrder_->SetCIP(cp);
        } return false;
		
//	case CMD_EXECUTE: // EXECUTE
//		{
//		int ret = 0;
//		N2BFC2* cmd = (N2BFC2*) tc->pCmd;
//		N2BaseVariable* pTemp = manVars.getVar(cmd->s_var[2]);
//		if(!pTemp ||
//			pTemp->type() != VAR_INT ||
//			pTemp->type() != VAR_LONG) {
//				OnProcedureProcessError(std_string(CT("Необъявленная переменная или неверный тип")), \
//					tc->signature.value, true);
//				return false;
//		}
//		ret = system((cmd->s_var[0] + CT(" ") + cmd->s_var[1]).c_str());
//		if(pTemp->type() == VAR_INT)
//			((N2VariableINT*) pTemp)->set(ret);
//		if(pTemp->type() == VAR_LONG)
//			((N2VariableLONG*) pTemp)->set((long&)ret);
//		} break;

    case CMD_EXIT: // EXIT
        {
        consoleMessage(std_string("команда EXIT: ") + tc->namePack, CMD_PROCESSOR_EVENT);
        ResetProcessor();
        queue_empty = true;
        } return false;
		
    case CMD_TIMER: // TIMER
        {
        N2BFC2* cmd = (N2BFC2*) tc->pCmd;
        if(cmd->i_var[0] > 10)
                return true;
        INT_N2 numTimer = cmd->i_var[0];
        switch(cmd->i_var[1])
            {
            case 0: // INIT
                Timers[numTimer].use = true;
                Timers[numTimer].resol = cmd->i_var[2];
                Timers[numTimer].time_begin = clock();
                break;
            case 1: // GET
                {
                int val = 0;
                int res = (Timers[numTimer].resol == 0)? 1000 : 1;
                val = ((clock() - Timers[numTimer].time_begin) * res)/ CLOCKS_PER_SEC;
                //vars.SetValue(tc->namePack, val); ???
                }
                break;
            case 2: // RESOLUTION
                Timers[numTimer].resol = cmd->i_var[2];
                break;
            case 3: // STOP
                Timers[numTimer].use = false;
                break;
            case 4: // WAIT
                {
                int val = 0;
                int res = (Timers[numTimer].resol == 0)? 1000 : 1;
                int end = cmd->i_var[2];
                while(1)
                    {
                    val = ((clock() - Timers[numTimer].time_begin) * res)/ CLOCKS_PER_SEC;
                    if(val >= end)
                            break;
                    }
                }
                break;
            case 5: //START
                {
                Timers[numTimer].time_begin = clock();
                }
                break;
            }
		
        } break;
				
//	case CMD_WHILE: // WHILE
//		{
//		int v = 0;
//		N2BFC3* cmd = (N2BFC3*) tc->pCmd;
//		N2BaseVariable* pTemp = manVars.getVar(cmd->var);
//		N2VariableCreator creator;
//		if(!pTemp) {
//				OnProcedureProcessError(std_string(CT("Необъявленная переменная цикла WHILE")), \
//				tc->signature.value, true);
//			return false;
//		}
//		if(pTemp->type() != VAR_BOOL &&
//			pTemp->type() != VAR_INT) {
//			OnProcedureProcessError(std_string(CT("Неверный тип переменной цикла WHILE")), \
//				tc->signature.value, true);
//			return false;
//		}
//		else {
//			v = creator.getIntFromSimplexVar(pTemp);
//		}
//		if(!v)
//			{
//			pOrder_->JumpWithCurrent();
//			return false;
//			}
//		} break;
////
//	case CMD_FORMAT_CONST: // FORMAT_CONST
//		{
//		std_string nw = tc->namePack;
//		N2BFC_ARRAY_STRING* cmd = (N2BFC_ARRAY_STRING*) tc->pCmd;
//		if(!cmd)
//			break;
//		std_string pre = cmd->get(0);
//		std_string post = cmd->get(2);
//		std_string var = cmd->get(1);
//		std_string sym = cmd->get(3);
//		N2BaseVariable* pNew = manVars.getVar(nw);
//		N2BaseVariable* pVar = manVars.getVar(var);
//		if(!pNew || !pVar) {
//			OnProcedureProcessError(head + "не найдена переменная ", tc->signature.value, false);
//			break;
//		}
//		if(pNew->type() != VAR_STRING) {
//			OnProcedureProcessError(head + "new-переменная не типа STRING!  ", tc->signature.value, false);
//			break;
//		}
//		// записываем префикс
//		N2BaseVariable* pTv = manVars.getVar(pre);
//		if(pTv)
//			pNew->set(pTv);
//		else
//			((N2VariableSTR*)pNew)->set(pre);
//		// format var
//		N2VariableCreator creator;
//		N2VariableSTR* sVar = (N2VariableSTR*)creator.createSimplex(VAR_STRING);
//		if (!sVar)
//			return false;
//		sVar->set(sVar->custom(pVar));

//		if(!sym.empty()) {
//			#define MAX_STRING_BUFFER_SIZE 512
//			CHAR_N2 buf[MAX_STRING_BUFFER_SIZE];
//			if(pVar->type() == VAR_INT) {
//				std_snprintf(buf, MAX_STRING_BUFFER_SIZE, sym.c_str(), ((N2VariableINT*)pVar)->getValue());
//				sVar->set(std_string(buf));
//			}
//		}
//		// преобразуем значение переменной var в строку
//		// добавляем postfix
//		N2VariableSTR* sPost = (N2VariableSTR*)creator.createSimplex(VAR_STRING);
//		if (!sPost)
//			return false;
//		pTv = manVars.getVar(post);
//		if(pTv)
//			sPost->set(pTv);
//		else
//			sPost->set(post);
//		// добавляем в переменную
//		pNew->operation(N2OC_PLUS, sVar);
//		pNew->operation(N2OC_PLUS, sPost);

//		}
//		break;

////	case 59: // LOG
////		{
////		std_string os;
////		switch(vars.Type(tc->namePack))
////			{
////			case VAR_STRING:
////					vars.GetValue(tc->namePack, os);
////					N2Register::self()->log()->Write(os);
////					break;
////			default:
////					OnProcedureProcessError("LOG: не найдена переменная типа STRING для записи в журнал!  ", 0, false);
////			}
////		}
////		break;
////
////	case 60:
////		{
////		vars.ClearCache();
////		}
////		break;
////
////	case 62: // PRAGMA
////		{
////		switch(tc->pblock[0])
////			{
////			case PRAGMA_ERROR_REDECLARE:
////				vars.ErrorOnRedeclare(!!tc->pblock[1]);
////				break;
////			}
////		}
////		break;
////
//	case CMD_CAST: // CAST
//		{
//			N2BFC3* cmd = (N2BFC3*) tc->pCmd;
//			N2BaseVariable* op1 = manVars.getVar(tc->namePack);
//			N2BaseVariable* op2 = manVars.getVar(cmd->var);
//			if(!op1 || !op2) {
//				OnProcedureProcessError("Переменная не найдена!", tc->signature.value, true);
//				break;
//			}
//			op1->set(op2);
//		}
//		break;
//////
////
//	case CMD_OPEN_DEVICE: // OPEN_DEVICE
//		{
//			int id = 0;
//			N2BFC2* cmd = (N2BFC2*) tc->pCmd;
//			HANDLE_NAME hndl;
//			PHelper helper;
//			bool obligative = !!cmd->i_var[0];
//			hndl.nameHandle = cmd->s_var[0];
//			FINDER_DEVICE findCondition = (FINDER_DEVICE) cmd->i_var[1];
//			if(findCondition == FD_MANUAL)
//				hndl.numberDevice = cmd->i_var[2] & 0xFF;
//			else
//				hndl.numberDevice = N2_ACTIVE_DEVICE;

//			SIGN signature = helper.StoI(cmd->s_var[2], RC_HEX);
			
//			N2ListModules* pListTable = pModsMan_->getListTable();
//			N2Module* pModule  = pListTable->find(signature);

//			if(!pModule) {
//				if(obligative)
//					OnProcedureProcessError("Модуль обработки обязательного устройства не найден!", \
//					tc->signature.value, true);
//				break;
//			}

//			hndl.pModule = pModule;

//			N2VariableBOOL* ok = (N2VariableBOOL*)maker.createSimplex(VAR_BOOL, cmd->s_var[1]);
//			if (!ok)
//				return false;
//			bool bok = true;
//			hndl.pModule = pModule;
//			pModule->setCallBackFunc((void*)this, N2Processor::WrapperCallBack);
//			//pModule->alive(hndl.numberDevice);
//			bok = pModule->open(hndl.numberDevice);
//			ok->set(bok);
//			N2BaseVariable *pVar = manVars.getVar(cmd->s_var[1]);
//			if(pVar)
//				pVar->set(ok);
//			else
//				manVars.declare(ok->clone());
			
//			if(bok)
//				vecHands.push_back(hndl);
//		}
//		break;

    case CMD_CLOSE_DEVICE: // CLOSE_DEVICE
        {
            bool error = true;
            vector<HANDLE_NAME>::iterator it;
            for(it=vecHands.begin(); it!=vecHands.end(); it++)
                if((*it).nameHandle == tc->namePack) {
                    error = false;
                    pModsMan_->deleteModule((*it).pModule);
                    vecHands.erase(it);
                    break;
                }

            if(error)
                OnProcedureProcessError("Устройство не закрыто!", tc->signature.value, false);
        }
        break;

    case CMD_DEVICE: // DEVICE
        {
            bool error = true;
            vector<HANDLE_NAME>::iterator it;
            for(it=vecHands.begin(); it!=vecHands.end(); it++)
                if((*it).nameHandle == tc->namePack) {
                    error = false;
                    stackHands.push(*it);
                    break;
                }

            if(error)
                OnProcedureProcessError("Устройство не найдено!", tc->signature.value, false);
		
        }
        break;
//
    case CMD_DEVICE_END: //  </DEVICE>
        {
            if(!stackHands.empty())
                stackHands.pop();
        }
        break;

    case CMD_MARK: //  <MARK />
        {}
        break;

    case CMD_GOTO: //  <GOTO />
        {
            pOrder_->SetCIP(tc->ret_value);
            return false; // не прокручивать указатель команд
        }
        break;

//	case CMD_USE_GLOBAL: //  <USE_GLOBAL>
//		{
//			N2Environment* pEnv = N2Register::self()->getEnvironment();
//			if(pEnv) {
//				const N2BaseVariable* pVar = pEnv->get(tc->namePack);
//				if(pVar) {
//					manVars.declare(((N2BaseVariable* )pVar)->clone());
//					break;
//				}
//			}
//			OnProcedureProcessError(std_string(CT("Глобальная переменная ")) + tc->namePack + \
//				std_string(CT(" не найдена!")), tc->signature.value, false);
//		}
//		break;

    case CMD_MACRO : //
        {
            // пока пустая команда
        }
        break;
	
    case CMD_EMPTY : //
        {
            // пустая команда
        }
        break;

//	case CMD_TABLE : //
//		{
//			if(!tc->pCmd || tc->pCmd->label != N2_BFCDECL2) {
//				OnProcedureProcessError(head + (CT("Ошибка создания таблицы - ")) + tc->namePack, \
//					tc->signature.value, false);
//				break;
//			}
//			N2DeclareBFC2* pCmd = (N2DeclareBFC2*)tc->pCmd;
//			int row = 0, column = 0;
//			/// получаем число строк
//			if(pCmd->s_row == EMPTY_STR)
//				row = pCmd->row;
//			else {
//				N2BaseVariable *pVar = manVars.getVar(pCmd->s_row);
//				if(!pVar) {
//					OnProcedureProcessError(std_string(CT("Ошибка создания таблицы - ")) + tc->namePack  \
//						+ CT(" (row) !"), tc->signature.value, false);
//					break;
//				}
//				row = maker.getIntFromSimplexVar(pVar);
//			}
//			/// получаем число столбцов
//			if(pCmd->s_column == EMPTY_STR)
//				column = pCmd->column;
//			else {
//				N2BaseVariable *pVar = manVars.getVar(pCmd->s_column);
//				if(!pVar) {
//					OnProcedureProcessError(std_string(CT("Ошибка создания таблицы - ")) + tc->namePack  \
//						+ CT(" (column) !"), tc->signature.value, false);
//					break;
//				}
//			column = maker.getIntFromSimplexVar(pVar);
//			}
//			///
//			N2BaseVariableTable* crVar = (N2BaseVariableTable*)maker.createTable(pCmd->type, tc->namePack, row, column);
//			if (!crVar) {
//					OnProcedureProcessError(std_string(CT("Ошибка создания таблицы - ")) + tc->namePack  \
//						+ CT(" (недопустимый размер) !"), tc->signature.value, false);
//					break;
//			}
//			N2BaseVariable *pV2 = manVars.getVar(pCmd->s_value);
//			if (pV2)
//				crVar->fill(pV2);
//			else
//				OnProcedureProcessError(std_string(CT("Ошибка инициализации таблицы - нет переменной с именем ")) + pCmd->s_value, \
//				tc->signature.value, false);
//			manVars.declare(crVar);
//		}
//		break;

//	case CMD_TABULAR : //
//		{
//			if(!tc->pCmd || tc->pCmd->label != N2_BFC_ARRAY_STRING) {
//				OnProcedureProcessError(head + (CT("ошибка создания таблицы - ")) + tc->namePack, \
//					tc->signature.value, false);
//				break;
//			}

//			N2BFC_ARRAY_STRING* pCmd = (N2BFC_ARRAY_STRING*) tc->pCmd;
//			std_string table = pCmd->get(0);
//			std_string var = pCmd->get(1);
//			std_string row = pCmd->get(2);
//			std_string column = pCmd->get(3);
//			std_string code = pCmd->get(4);

//			N2BaseVariableTable* pTable = (N2BaseVariableTable*)manVars.getVar(table);
//			if(!pTable) {
//				OnProcedureProcessError(head + (CT("нет таблицы с именем - ")) + table, \
//					tc->signature.value, false);
//				break;
//			}
//			// operation
//			PHelper hlp;
//			hlp.AddFirst("GET_CELL", N2TOC_GET_CELL);
//			hlp.Add("SET_CELL", N2TOC_SET_CELL);
//			if(hlp.WhatIs(code) != AHE_TOKEN) {
//				OnProcedureProcessError(head + (CT("неверный код операции - ")) + code, \
//					tc->signature.value, false);
//				break;
//			}
//			N2_TABLE_OPERATING_CODE tCode = (N2_TABLE_OPERATING_CODE) hlp.GetValue();
//			// value
//			N2BaseVariable* pVar = manVars.getVar(var);
//			if (!pVar) {
//				if ((tCode == N2_Defines::N2TOC_SET_CELL) && (pVar = manVars.creator.createSimplex(VAR_STRING, "%temp1")))
//						((N2VariableSTR*)pVar)->set(var);
//				else {
//					OnProcedureProcessError(head + (CT("нет переменной с именем - ")) + var, \
//						tc->signature.value, false);
//					break;
//				}
//			}
//			// row
//			int i_row = 0;
//			hlp.Reset();
//			switch(hlp.WhatIs(row)) {
//				case AHE_DIGIT:
//					i_row = hlp.GetValue();
//					break;
//				case AHE_VARIABLE:
//					i_row = maker.getIntFromSimplexVar(manVars.getVar(row));
//					break;
//				default: ;
//			}
//			// column
//			int i_column = 0;
//			hlp.Reset();
//			switch(hlp.WhatIs(column)) {
//				case AHE_DIGIT:
//					i_column = hlp.GetValue();
//					break;
//				case AHE_VARIABLE:
//					i_column = maker.getIntFromSimplexVar(manVars.getVar(column));
//					break;
//				default: ;
//			}

//			switch (tCode)
//			{
//			case N2_Defines::N2TOC_SET_CELL:
//				pTable->moveVariableToCell(i_row, i_column, pVar);
//				break;
//			case N2_Defines::N2TOC_GET_CELL:
//				pTable->moveCellToVariable(i_row, i_column, pVar);
//				break;
//			default:
//				OnProcedureProcessError(head + (CT("неверный код операции - ")) + code, \
//					tc->signature.value, false);
//				break;
//			}

//		} break;

//	case CMD_GFA:
//		{
//			N2BFC_ARRAY_STRING* pNas =	(N2BFC_ARRAY_STRING*) tc->pCmd;
//			if(!pNas || (pNas->size()<3)) {
//				OnProcedureProcessError(head + (CT("пустое поле параметров pCmd")), \
//					tc->signature.value, false);
//				break;
//			}
//			std_string var = pNas->get(0);
//			std_string arr = pNas->get(1);
//			std_string index = pNas->get(2);
//			short indx = 0;

//			N2BaseVariable* pVar = manVars.getVar(var);
//			if(!pVar || (pVar->kind() != KT_SIMPLEX)) {
//				OnProcedureProcessError(head + (CT("недопустимая переменная атрибута var =")) + var, \
//					tc->signature.value, false);
//				break;
//			}
//			N2BaseVariable* pVarArr = manVars.getVar(arr);
//			if(!pVarArr || (pVarArr->kind() != KT_SIMPLEX)) {
//				OnProcedureProcessError(head + (CT("недопустимая переменная атрибута array =")) + arr, \
//					tc->signature.value, false);
//				break;
//			}
//			N2BaseVariable* pVi = manVars.getVar(index);
//			if(pVi)
//				indx = maker.getIntFromSimplexVar(pVi);
//			else {
//				PHelper hlp;
//				indx = hlp.StoI(index);
//			}

//			pVar->setVoid(pVarArr->getVoid(indx));

//		} break;

//	case CMD_SET_GLOBAL:
//		{
//			N2BFC_ARRAY_STRING* pNas =	(N2BFC_ARRAY_STRING*) tc->pCmd;
//			if(!pNas || (pNas->size()<3)) {
//				OnProcedureProcessError(head + (CT("пустое поле параметров pCmd")), \
//					tc->signature.value, false);
//				break;
//			}
//			std_string var = pNas->get(0);
//			std_string value = pNas->get(1);
//			std_string index = pNas->get(2);
//			short indx = 0;

//			N2Environment* pEnv = N2Register::self()->getEnvironment();
//			N2BaseVariable* pVar = pEnv->change(var);
//			if(!pVar || (pVar->kind() != KT_SIMPLEX)) {
//				OnProcedureProcessError(head + (CT("недопустимая переменная атрибута var =")) + var, \
//					tc->signature.value, false);
//				break;
//			}
//			// вытаскиваем индекс
//			N2BaseVariable* pIndx = manVars.getVar(index);
//			if(pIndx)
//				indx = maker.getIntFromSimplexVar(pIndx);
//			else {
//				PHelper hlp;
//				indx = hlp.StoI(index);
//			}
//			//
//			N2BaseVariable* pValue = manVars.getVar(value);
//			if(!pValue) {
//				N2VariableSTR* pSV = (N2VariableSTR*) maker.createSimplex(VAR_STRING);
//				if (!pSV)
//					return false;
//				pSV->set(value);
//				pValue = pSV;
//			}
//			// собственно установка значения
//			pVar->set(pValue, indx);

//		} break;

//	case CMD_SET_GLOBAL_TABLE:
//		{


//		} break;

//	case CMD_STA: // SET_TO_ARRAY
//		{
//			N2BFC_ARRAY_DUX* pNas =	(N2BFC_ARRAY_DUX*) tc->pCmd;
//			if(!pNas || (pNas->size()<3)) {
//				OnProcedureProcessError(head + (CT("пустое поле параметров pCmd")), \
//					tc->signature.value, false);
//				break;
//			}
//			N2BFC_ARRAY_DUX::VAL* pV;
//			std_string arr = pNas->getStr(0);
//			N2BaseVariable* pVar = manVars.getVar(arr);
//			if(!pVar) {
//				OnProcedureProcessError(head + (CT("нет массива с именем ")) + arr, \
//					tc->signature.value, false);
//				break;
//			}
//			short index = 0;
//			pV = pNas->get(1);
//			if(pV->sval != EMPTY_STR) {
//				N2BaseVariable* pVi = manVars.getVar(pV->sval);
//				if(!pVi) {
//					OnProcedureProcessError(head + (CT("нет переменной индекса с именем ")) + pV->sval, \
//						tc->signature.value, false);
//					break;
//				}
//				if (pVi->type() != VAR_INT) {
//					OnProcedureProcessError(head + (CT("переменная индекса должна быть INT ")) + pV->sval, \
//					tc->signature.value, false);
//				break;
//				}
//				index = ((N2VariableINT*)pVi)->getValue();
//			}
//			else
//				index = pV->ival;
			
//			std_string value = pNas->getStr(2);
//			N2BaseVariable* pValue = manVars.getVar(value);
//			if(!pValue) {
//				N2VariableSTR* pSV = (N2VariableSTR*) maker.createSimplex(VAR_STRING);
//				if (!pSV)
//					return false;
//				pSV->set(value);
//				pValue = (N2BaseVariable*)pSV;
//			}
			
//			pVar->set(pValue, index);

//		} break;

//	case CMD_RIBBON_TO_ARRAY: // RIBBON_TO_ARRAY
//		{
//			N2BFC_ARRAY_STRING* pNas =	(N2BFC_ARRAY_STRING*) tc->pCmd;
//			if(!pNas) {
//				OnProcedureProcessError(head + (CT("пустое поле параметров pCmd")), \
//					tc->signature.value, false);
//				break;
//			}
//			N2BaseVariable* pVar = manVars.getVar(tc->namePack);
//			if(!pVar) {
//				OnProcedureProcessError(head + (CT("нет массива с именем ")) + tc->namePack, \
//					tc->signature.value, false);
//				break;
//			}
//			N2VariableSTR* pSV = (N2VariableSTR*) maker.createSimplex(VAR_STRING);
//			if (!pSV)
//				return false;
//			for(size_t i=0; i<pNas->size() && i<pVar->dimension(); i++) {
//				pSV->set(pNas->get(i));
//				pVar->set(pSV, i);
//			}

//		} break;

    ///	На удаление vvvvvvvvvvvv
    case 100:
        {
        std_string str;
        char mtc[512];
        sprintf_s(mtc, "Произошла ошибка: %s\nРабота остановлена!", tc->namePack.c_str());
        str = mtc;
        //MessageBox(NULL, str.c_str(), "Ошибка синтаксиса тестов (Загрузчик тестов)", MB_ICONERROR);
        //display->Write(std_string("(!) Произошла ошибка (Загрузчик) : ") + tc->namePack.c_str());
        queue_empty = true;
        } return false;
    }

    return true;
}




bool N2Processor::FatalError()
{
	return fatal_error;
}




bool N2Processor::EmptyQueue()
{
	return queue_empty;
}




void N2Processor::ResetProcessor()
{
	#ifdef INSTRUCTION_PROFILER
		N2Register::self()->log()->ProfilerStop();
	#endif		
	queue_empty = false;
	fatal_error = false;
	manVars.clear();
	vecHands.clear();
	//pOrder_->Reset();
	//vars.Clear();	
}



bool N2Processor::Initial(N2ModulesManager *pMM, N2Order *pOrder)
{
	pOrder_ = pOrder;
	pModsMan_ = pMM;

	initial = ((pOrder_ != NULL) && (pModsMan_ != NULL));

	queue_empty = false;
	
	return (pOrder_ && pModsMan_);
}



/*****************************************************************************/
void N2Processor::OnProcedureProcessError(std_string message, SIGN sign, bool fatal)
{
	std_string sch, code;
	char buff[128];

	sprintf_s(buff, "(sign = 0x%8.8X) ", sign);
	code = buff;

	std_string out ; //("<ВМ-ПРОЦЕССОР:> ");
	out += code;
	out += message;
	
	if(fatal) {
		ResetProcessor();
		queue_empty = true;
		fatal_error = true;
		consoleMessage(out, CMD_CON_PROCESSOR_ERROR_FATAL);
	}
	else 
		consoleMessage(out, CMD_CON_PROCESSOR_WARNING);

}


int 
N2Processor::callBack(DataPack& data)
{
	int retVal = 0;
	
	switch(data.signature.img1.code)
	{
		case CMD_SP_GET_VARIABLE: {
			N2BaseVariable* pVar = manVars.getVar(data.namePack);
			if(!pVar) {
				data.pCmd = NULL;
				data.ret_value = retVal = ERR_VARIABLE_DSNT_EXIST;
				break;
			}
			N2DeclareBFC* pCmd = N2Register::self()->getMemoryAllocator()->create<N2DeclareBFC>("CMD_SP_GET_VARIABLE");
			data.pCmd = (N2DeclareBFC*) pCmd;
            pCmd->type = pVar->getType();
			data.ret_value = ERR_NOTHING;
			data.buffer = pVar; //->clone(); // переписать, или изменить саму команду
		} break;

		case CMD_SP_SET_VARIABLE: {
		
		} break;
		//case CMD_SP_GET_ENVIRONMENT_VAR: {
		//
		//} break;

		case CMD_SP_ROUTE: {
			/*if(!data.pCmd)
				break;
			N2Order* oldOrder = pOrder_;
			N2Order order;
			VectorCommand vecCom;
			vecCom.push_back(*(DataPack*)data.buffer);
			order.AddCommandsInOrder(&vecCom);
			pOrder_ = &order;
			tick();
			order.Reset();
			pOrder_ = oldOrder;*/
			inject((DataPack*)data.buffer);
		} break;

	}

	return retVal;
}


int 
N2Processor::WrapperCallBack(void* pFmc, DataPack& data)
{
	if(!pFmc)
		return 1;
	N2Processor* self = (N2Processor*) pFmc;
	return self->callBack(data);
}



void 
N2Processor::consoleMessage(std_string msg, UINT_N2 typeMsg)
{
	N2ListModules* pList = pModsMan_->getListTable();
	N2Console* errCons = NULL;
	
	if (pList)
		errCons = dynamic_cast<N2Console*>(pList->find(SIGN(N2_CONSOLE)));
	
	if (!errCons)
		return;

	DataPack pack;
	pack.signature.value = MAKE_CODE(typeMsg, N2_CONSOLE);

	switch(typeMsg) {
	case CMD_CON_WRITE:
		//pack.nameTag = CT("CONSOLE_WRITE");
		pack.namePack = msg;
		break;
	case CMD_CON_LOG:
		break;
	case CMD_PROCESSOR_EVENT:
		{
		//pack.nameTag = CT("PROCESSOR_EVENT");
		pack.namePack = msg;
		errCons->command(&pack);
		}
		break;
	case CMD_CON_PROCESSOR_ERROR_FATAL:
	case CMD_CON_SYNTAX_ERROR:
	case CMD_CON_PROCESSOR_WARNING:
	case CMD_CON_PROCESSOR_MODULE_ERROR:
		{		
		//pack.nameTag = CT("PROCESSOR_ERROR");
		/*N2ErrorBFC* pBFC = new N2ErrorBFC();
		pack.pCmd = pBFC;
		pBFC->descriptionError = msg;*/
		pack.namePack = msg;
		errCons->command(&pack);
		/*delete pack.pCmd;*/
		}
		break;
	default:
		//
		;
	}

}


void 
N2Processor::onErrorHappened(DataPack* pPack, Response& resp)
{
	switch (resp.err_) 
	{
	case ERR: 
	case THROW_EXCEPTION: 
	case CMD_HANDLER_NOT_FOUND: 
		consoleMessage(pPack->errorDescription, CMD_CON_PROCESSOR_MODULE_ERROR);
		break;
	case FATAL_ERR: 
		consoleMessage(pPack->errorDescription, CMD_CON_PROCESSOR_ERROR_FATAL);
		break;	
	case WARNING:	
		consoleMessage(pPack->errorDescription, CMD_CON_PROCESSOR_WARNING);
		break;
	default:
		break;
	}
}
