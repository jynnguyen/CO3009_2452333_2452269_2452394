/*
 * scheduler.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0u

typedef struct
{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

void SCH_Init();
void SCH_Update(); // called in timer ISR
void SCH_Dispatch_Tasks(); // called in while(1)
uint32_t SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID); // 1 = deleted

#endif /* INC_SCHEDULER_H_ */
