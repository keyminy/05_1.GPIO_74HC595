/*
 * data_shift.h
 *
 *  Created on: May 30, 2024
 *      Author: HARMAN-27
 */

#ifndef DATA_SHIFT_H_
#define DATA_SHIFT_H_
#include "main.h"

void shift_clock(void);
void latch_clock(void);
void data_shift(uint8_t data);
int shift_main(void);


#endif /* DATA_SHIFT_H_ */
