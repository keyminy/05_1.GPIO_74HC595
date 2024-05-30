#include "data_shift.h"

void shift_clock(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
}

void latch_clock(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
}

void data_shift(uint8_t data)
{
	for(uint8_t i = 0; i <8; i++)
	{
		if(data & 0b10000000)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
		}
		else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);

		shift_clock();
		data = data << 1;
	}
	latch_clock();
}

int shift_main(void)
{
	static uint8_t index = 0;
	uint8_t pattern;

	pattern = 1 << index;
	index = (index + 1) % 8;

	data_shift(pattern);

	return;
}
