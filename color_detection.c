#include <stdlib.h>

#include "lcd.h"
#include "util.h"
#include "open_interface.h"

void main( void ) {
	oi_t *sensor = oi_alloc();
	oi_init(sensor);
	lcd_init();
	while(1) {
		oi_update(sensor);
		int left_cliff = sensor->cliff_left;
		int right_cliff = sensor->cliff_right;
		int left_signal = sensor->cliff_left_signal;
		int right_signal = sensor->cliff_right_signal;
		
		lprintf("Left: %d\nSignal: %d\nRight: %d\nSignal: %d", left_cliff, left_signal, right_cliff, right_signal);
	}
}