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

void SCH_Init(void)
{
	SCH_count = 0;
}

void SCH_Update(void)
{
	if (SCH_count == 0)
		return;

	if (SCH_tasks_G[0].Delay > 0)
		SCH_tasks_G[0].Delay--;

	if (SCH_tasks_G[0].Delay == 0)
		SCH_tasks_G[0].RunMe = 1;
}

void SCH_Dispatch_Tasks(void)
{
	while (SCH_count > 0 && SCH_tasks_G[0].RunMe)
	{
		sTask dpTask =  SCH_tasks_G[0];
		dpTask.pTask();

		if(SCH_Delete_Task(dpTask.TaskID) && dpTask.Period > 0)
		{
			dpTask.Delay = dpTask.Period;
			dpTask.RunMe = 0;
			Insert(&dpTask);
		}
	}
}

