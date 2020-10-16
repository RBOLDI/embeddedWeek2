#ifndef _RUNTIME_HPP_
#define _RUNTIME_HPP_

#include <bcm2835.h>

#define BUTTON1 RPI_GPIO_P1_05
#define BUTTON2 RPI_GPIO_P1_13
#define BUTTON3 RPI_GPIO_P1_26
#define BUTTON4 RPI_GPIO_P1_24

#define LED1 RPI_GPIO_P1_11
#define LED2 RPI_GPIO_P1_13
#define LED3 RPI_GPIO_P1_15

class RUNTIME_CLASS {
	public:
		int initBcm(void);
		int closeBcm(void);
		int setLed(char led, int state);
		int pollLed(char led);
		int pollButton(char button);
		
	private:

};

#endif