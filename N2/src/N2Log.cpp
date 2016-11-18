// -*- mode:c++; coding:utf-8; -*-
///
/// \file		N2Log.cpp
///
///	\brief 		Файл журнала
/// \details	
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


#include "../export/common/N2Log.h"
#include <time.h>

N2Logbook::N2Logbook()
{
	write_interdiction = false;
	response = NULL;
	time_t tt = time(NULL);
	tm* t = localtime( &tt );
	Write("---------------------------------------------------------------------------\n");
	Write(string("Начало ведения журнала : ") + asctime(t));
	profile = NULL;
	pProfStruct = NULL;
	order_length = 0;
	//po = NULL;
}


N2Logbook::~N2Logbook()
{
	//Print("control.txt", false);
	log_error.clear();
}


void N2Logbook::Write(std::string record)
{
	if(write_interdiction)
			return;
	// запись в вектор определений
	LOGED l;
	l.module = "";
	l.error = 0;
	l.descr = record;
	log_error.push_back(l);
	if(response) 
		response(record);
}



bool N2Logbook::WriteError(std::string module, int error, std::string description)
{
	if(write_interdiction)
			return false;
	bool ret_val = false;	
	current_error = error;
	descr_error = description;
	// запись в вектор определений
	loged.module = module;
	loged.error = error;
	loged.descr = description;
	log_error.push_back(loged);
	std::string ns;
	char tc[512];
	sprintf_s(tc, "Модуль: %s  Ошибка № %d  \n   Описание: %s", module.c_str(), error, description.c_str());
	ns = tc;
	if(response) 
		response(ns);
	return ret_val;
}

int N2Logbook::GetLastError(std::string& description)
{
	description = descr_error;
	return current_error;
}

void N2Logbook::ResetError()
{
	current_error = 0;
	descr_error = "";
}

void N2Logbook::Print(std::string filename, bool add_over) //Запись в файл filename лога
{
	FILE *file;
	if ((file = fopen(filename.c_str(), add_over ? "a" : "w"))==NULL) 
			return;
	for(unsigned int i=0; i<log_error.size(); i++)
		{
		if(log_error[i].module == "" && log_error[i].error == 0)
				fprintf(file, " - %s \n", log_error[i].descr.c_str());
		else
				fprintf(file, "ERROR: %s  - #%d : %s \n", log_error[i].module.c_str(), log_error[i].error, \
					log_error[i].descr.c_str());
		}

	time_t tt = time(NULL);
	tm* t = localtime( &tt );
	fprintf(file, "Конец ведения журнала : %s", asctime(t));
	fclose(file);
}

void N2Logbook::SetResponse(void (*resp)(string))
{
	response = resp;
}

void N2Logbook::SetInterdiction(bool interd)
{
	write_interdiction = interd;
}

//void N2Logbook::ProfilerInit(N2Order* porder, unsigned int length)
//{
//	if(profile == NULL)
//		{
//		if ((profile = fopen("profiler.txt", "w")) == NULL) 
//				return;
//		time_t tt = ::time(NULL);
//		tm* t = localtime( &tt );
//		fprintf(profile, "Длительность выполнения команд от %s \n", asctime(t));				
//		fprintf(profile, "ЧП: - число повторений инструкции, Т: - суммарно тиков \n\n");				
//		}
//	else
//		return;
//		
//	order_length = length;	
//	po = porder;
//	
//	if(pProfStruct == NULL)
//		pProfStruct = new PROFILER_STRUCT[length]; 
//}
//
//void N2Logbook::Profiler(DataPack* ptc, unsigned int ip, int time)
//{
//	//if(ip >= order_length)
//	//	return;
//
//	//if(!pProfStruct[ip].init)
//	//	{
//	//	pProfStruct[ip].name =  ptc->debug_tag_name;
//	//	pProfStruct[ip].sign =  ptc->signature.value();
//	//	pProfStruct[ip].time = time;
//	//	pProfStruct[ip].init = true;
//	//	pProfStruct[ip].count = 1;
//	//	}
//	//else
//	//	{
//	//	pProfStruct[ip].time += time;
//	//	pProfStruct[ip].count ++;
//	//	}
//}
//
//void N2Logbook::ProfilerStop(void)
//{
//	if(profile)
//		{
//		for(int i=0; i<order_length; i++)
//			{
//			if(pProfStruct[i].init)
//				fprintf(profile, "%4d : %-20s  (SIGN:0x%8.8X,Code:%-3d) ЧП:%-d  Т:%-d\n",
//							 i, pProfStruct[i].name.c_str(), pProfStruct[i].sign, \
//							 pProfStruct[i].sign >> 24, pProfStruct[i].count, pProfStruct[i].time);
//			else
//				fprintf(profile, "%4d : %-20s    - ignore -\n",
//								i, po->GetAnyCommand(i)->namePack.c_str());				
//			}
//		fclose(profile);
//		}
//	
//	if(pProfStruct)
//		delete [] pProfStruct;
//		
//	profile = NULL;
//	pProfStruct = NULL;
//	order_length = 0;
//	po = NULL;
//}