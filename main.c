//int main()
//{
//	UART0_Init(115200);
//	//PIT_Init();
//	Switch_Init();
//	RGBLed_Init();
//	for(;;) {}
//}

#include "gpio.h"
#include "Pit.h"
#include "MKL25Z4.h"
#include "Uart.h"

extern uint32_t timer_value;

char suport_text1[] = "\rIntroduceti timpul dorit (sec): ";

extern uint8_t c;
extern uint8_t end;
extern uint8_t numar1[100];

extern uint8_t write1, read1;
extern uint8_t write2, read2;

extern uint8_t complet1,complet2;

void put_string(char* data) {
	while(*data) {
				
		UART0->D = *data;
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));
				
		++data;
	}
}

int main()
{
	
	uint16_t i;

	UART0_Init(115200);
	complet1 = 0;
	while (1) 
	{
		if(complet1 == 0){ // Afisare sir premergator citirii primului numar
			put_string(suport_text1);
			complet1 = 1;
		}

		if(read1!=write1 && complet1!=2){ // Afisarea primului numar pe parcursul citirii caracterelor
			UART0_Transmit(numar1[read1]);
			read1++;
			read1= read1 % 100;
		}

		
		if(complet1 == 2){
			
			write1 = read1 = complet1 = 0;
			write2 = read2 = complet2 = 0;
		}
		
		if(end){
			put_string(suport_text1);
			break;
		}
		
	}
	
	return 0;
	
}