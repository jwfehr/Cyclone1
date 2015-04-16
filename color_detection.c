
#include <stdlib.h>

#include "lcd.h"
#include "util.h"
#include "open_interface.h"
#include "movement.h"

int main(void) {
	oi_t *sensor = oi_alloc();
	oi_init(sensor);
	lcd_init();
	
	moveForwardWithSensors(sensor,50);
	while(1) {
		oi_update(sensor);
		int left_cliff = sensor->cliff_left_signal;
		int right_cliff = sensor->cliff_frontleft_signal;
		int left_signal = sensor->cliff_frontright_signal;
		int right_signal = sensor->cliff_right_signal;
		
		lprintf("Left: %d\nFront Left: %d\nFront Right: %d\nRight: %d", left_cliff, right_cliff, left_signal, right_signal);
	}
}