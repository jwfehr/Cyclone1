unsigned int pulse_period = 43000; // 21.5 ms
unsigned int initialLocation = 1000; //location initially centered 90 degrees calibrated for robot 3 0 = 1000 and 180 = 4500; 90 = 2750

void init_servo()
{
	OCR3A = pulse_period - 1; //sets period to 21.5ms
	OCR3B = initialLocation - 1; //sets initial rotation to midpoint 90 degrees
	TCCR3A = 0x23;	//Configures Control register A
	TCCR3B = 0x1A; //configues control register b
	DDRE |= 0x10; //set pe4 as output
}

void moveServo(int degrees)
{
	OCR3B = (degrees * 3500 / 180) - 1;
}