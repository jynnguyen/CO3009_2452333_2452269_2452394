/*
 * scheduler.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

// Scheduler O(1)
#include "main.h"
#include "scheduler.h"
#include "sch_port.h"

static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint8_t SCH_count = 0;
static uint8_t task_id = 1;

static uint32_t Insert(const sTask* newTask)
{
	uint32_t m = SCH_Lock();
	if(SCH_count >= SCH_MAX_TASKS)
	{
		SCH_Unlock(m);
		return NO_TASK_ID;
	}

	uint8_t currID = 0;
	uint32_t sumDelay = 0;

	for(currID = 0; currID < SCH_count; currID++)
	{
		if(sumDelay + SCH_tasks_G[currID].Delay <= newTask->Delay)
			sumDelay += SCH_tasks_G[currID].Delay;
		else
			break;
	}

	for (uint8_t i = SCH_count; i > currID; i--)
		SCH_tasks_G[i] = SCH_tasks_G[i - 1];

	sTask *t = &SCH_tasks_G[currID];
	*t = *newTask;
	t->Delay = newTask->Delay - sumDelay;
	t->RunMe = (currID == 0 && t->Delay == 0);

	if (currID < SCH_count)
		SCH_tasks_G[currID + 1].Delay -= t->Delay;

	SCH_count++;
	SCH_Unlock(m);
	return t->TaskID;
}