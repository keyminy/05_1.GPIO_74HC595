#include "dotmatrix.h"
#include <string.h>

extern SPI_HandleTypeDef hspi2;
void dotmatrix_main_test();
int dotmatrix_main(void);
int make_dot(char* word);
extern pc_command_processing();

uint8_t allon[] = {			// allon 문자 정의
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111
};

uint8_t smile[] = {			// 스마일 문자 정의
	0b00111100,
	0b01000010,
	0b10010101,
	0b10100001,
	0b10100001,
	0b10010101,
	0b01000010,
	0b00111100 };

uint8_t hart[] = {		// hart
	0b00000000,    // hart
	0b01100110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100,
	0b00011000
};


uint8_t col[4]={0,0,0,0};

//copyed
uint8_t number_data[20][10] =
{
	{
		0b01110000,	//0
		0b10001000,
		0b10011000,
		0b10101000,
		0b11001000,
		0b10001000,
		0b01110000,
	    0b00000000
	},
	{
		0b01000000,	//1
		0b11000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b11100000,
	    6   // 점 0b00000110
	},
	{
		0b01110000,	//2
		0b10001000,
		0b00001000,
		0b00010000,
		0b00100000,
		0b01000000,
		0b11111000,
	    6
	},
	{
		0b11111000,	//3
	    0b00010000,
		0b00100000,
		0b00010000,
		0b00001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b00010000,	//4
		0b00110000,
		0b01010000,
		0b10010000,
		0b11111000,
		0b00010000,
		0b00010000,
	    6
	},
	{
		0b11111000,	//5
		0b10000000,
		0b11110000,
		0b00001000,
		0b00001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b00110000,	//6
		0b01000000,
		0b10000000,
		0b11110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b11111000,	//7
		0b10001000,
		0b00001000,
		0b00010000,
		0b00100000,
		0b00100000,
		0b00100000,
	    6
	},
	{
		0b01110000,	//8
		0b10001000,
		0b10001000,
		0b01110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b01110000,	//9
		0b10001000,
		0b10001000,
		0b01111000,
		0b00001000,
		0b00010000,
		0b01100000,
	    6
	},
	{
		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
	}
};

// Binary dot-matrix patterns for the letters 'A' through 'Z'
uint8_t alphabet[26][8] = {
    {0b00011000, 0b00100100, 0b01000010, 0b01000010, 0b01111110, 0b01000010, 0b01000010, 0b00000000}, // A
    {0b01111100, 0b01000010, 0b01000010, 0b01111100, 0b01000010, 0b01000010, 0b01111100, 0b00000000}, // B
    {0b00111100, 0b01000010, 0b01000000, 0b01000000, 0b01000000, 0b01000010, 0b00111100, 0b00000000}, // C
    {0b01111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01111100, 0b00000000}, // D
    {0b01111110, 0b01000000, 0b01000000, 0b01111100, 0b01000000, 0b01000000, 0b01111110, 0b00000000}, // E
    {0b01111110, 0b01000000, 0b01000000, 0b01111100, 0b01000000, 0b01000000, 0b01000000, 0b00000000}, // F
    {0b00111100, 0b01000010, 0b01000000, 0b01001110, 0b01000010, 0b01000010, 0b00111100, 0b00000000}, // G
    {0b01000010, 0b01000010, 0b01000010, 0b01111110, 0b01000010, 0b01000010, 0b01000010, 0b00000000}, // H
    {0b01111110, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b01111110, 0b00000000}, // I
    {0b00011110, 0b00000100, 0b00000100, 0b00000100, 0b01000100, 0b01000100, 0b00111000, 0b00000000}, // J
    {0b01000010, 0b01000100, 0b01001000, 0b01110000, 0b01001000, 0b01000100, 0b01000010, 0b00000000}, // K
    {0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01111110, 0b00000000}, // L
    {0b01000010, 0b01100110, 0b01011010, 0b01011010, 0b01000010, 0b01000010, 0b01000010, 0b00000000}, // M
    {0b01000010, 0b01100010, 0b01110010, 0b01011010, 0b01001110, 0b01000110, 0b01000010, 0b00000000}, // N
    {0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00111100, 0b00000000}, // O
    {0b01111100, 0b01000010, 0b01000010, 0b01111100, 0b01000000, 0b01000000, 0b01000000, 0b00000000}, // P
    {0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b01001010, 0b01000110, 0b00111010, 0b00000000}, // Q
    {0b01111100, 0b01000010, 0b01000010, 0b01111100, 0b01001000, 0b01000100, 0b01000010, 0b00000000}, // R
    {0b00111100, 0b01000010, 0b01000000, 0b00111100, 0b00000010, 0b01000010, 0b00111100, 0b00000000}, // S
    {0b01111110, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00000000}, // T
    {0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00111100, 0b00000000}, // U
    {0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b00100100, 0b00100100, 0b00011000, 0b00000000}, // V
    {0b01000010, 0b01000010, 0b01000010, 0b01011010, 0b01011010, 0b01100110, 0b01000010, 0b00000000}, // W
    {0b01000010, 0b01000010, 0b00100100, 0b00011000, 0b00100100, 0b01000010, 0b01000010, 0b00000000}, // X
    {0b01000010, 0b01000010, 0b00100100, 0b00011000, 0b00010000, 0b00010000, 0b00010000, 0b00000000}, // Y
    {0b01111110, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01111110, 0b00000000}  // Z
};



unsigned char display_data[8];  // 최종 8x8 출력할 데이터
unsigned char scroll_buffer[50][8] = {0};  // 스코롤할 데이타가 들어있는 버퍼
int number_of_character = 11;  // 출력할 문자 갯수

// 초기화 작업
// 1. display_data에 number_data[0]에 있는 내용 복사
// 2. number_data를 scroll_buffer에 복사
// 3. dotmatrix의 led를 off
void init_dotmatrix(void)
{
	for (int i=0; i < 8; i++)
	{
		display_data[i] = number_data[i][0];
	}
	for (int i=1; i < number_of_character+1; i++)
	{
		for (int j=0; j < 8; j++) // scroll_buffer[0] = blank
		{
			scroll_buffer[i][j] = number_data[i-1][j];
			// i 는 1~11번(10번), j는 0~7번(8번 반복)
		}
	}

}

#if 1
// scroll 문자 출력 프로그램
int dotmatrix_main(void)
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장

	init_dotmatrix();

	while(1)
	{
		// 1ms인 한 틱을 읽는다.
		uint32_t now = HAL_GetTick();  // 1ms
		// pc_command_processing(); // UART input comes in (word parameter corresponding to parameter)
		// 틱값을 읽으면서 현재 몇 ms가 됬는지 안됬는지 check함
		// 500ms마다 한 칸 씩 shift하면서 돌리겠다.
		// 1.처음시작시 past_time=0; now: 500 --> past_time=500
		if (now - past_time >= 500) // 500ms scroll
		{
			past_time = now;
			for (int i=0; i < 8; i++)
			{
				display_data[i] = (scroll_buffer[index][i] >> count) |
						(scroll_buffer[index+1][i] << 8 - count);
			}
			if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
			{
				count =0;
				index++;  // 다음 scroll_buffer로 이동
				if (index == number_of_character+1) index=0;
				// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
			}
		}
		//display_data를 여기서 찍어보기
//		for(int i=0; i< 8;i++){
//			printf("%u\n",display_data[i]);
//		}
		for (int i=0; i < 8; i++)
		{
			// 공통 양극 방식
			// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
			// for문 행 8행 돈다
			col[0] = ~(1 << i); // 0000_0001 -->(one's complement 1111_1110)
			col[1] = display_data[i];
			HAL_SPI_Transmit(&hspi2, col, 2, 1); // 2byte전송 timeout은 1ms
			GPIOB->ODR &= ~GPIO_PIN_15;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_15;   // latch핀을 pull-up
			HAL_Delay(1); // 잔상효과 없애기위해 1ms
		}
	}
	return 0;
}
#endif

int make_dot(char* word){
	// word = XVAS가리킴
	int len = strlen(word);
	number_of_character = len;

	// Reset the scroll_buffer
	memset(scroll_buffer, 0, sizeof(scroll_buffer));
	memset(display_data, 0, sizeof(display_data));

	// Fill scroll_buffer with the dot matrix patterns of the input word
	for (int i = 0; i < len; i++) {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			// only alphabet word!!
			int index = word[i] - 'A'; //23 // Get index in alphabet array
			for (int j = 0; j < 8; j++) {
				scroll_buffer[i][j] = alphabet[index][j];
				// scroll_buffer[i][j](i : XVAS의 길이) =  alphabet[23][j]
			}
		}
	}
	return 0;
}

#if 0
// 고정문자 출력 demo program

#endif


void dotmatrix_main_test()
{
	dotmatrix_main();
  while (1)
  {
        for (int i=0; i < 8; i++)
        {
        	// for문 행 8행 돈다
			col[0] = ~(1 << i); // 0000_0001 -->(one's complement 1111_1110)
			col[1] = allon[i];
			HAL_SPI_Transmit(&hspi2, col, 2, 1); // 2byte전송 timeout은 1ms
			GPIOB->ODR &= ~GPIO_PIN_15;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_15;   // latch핀을 pull-up
			HAL_Delay(1); // 잔상효과 없애기위해 1ms
        }
  }
}
