/*
 * sch_port.h
 *
 *  Created on: Nov 5, 2026
 *      Author: jynng
 */

#ifndef INC_SCH_PORT_H_
#define INC_SCH_PORT_H_

#include "main.h"

static inline uint32_t SCH_Lock(void)
{
	uint32_t primask = __get_PRIMASK();
	__disable_irq();
	return primask;
}

static inline void SCH_Unlock(uint32_t primask)
{
	__set_PRIMASK(primask);
}


#endif /* INC_SCH_PORT_H_ */
