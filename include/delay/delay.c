void delay(int time) {
	volatile long count = 1000000 * time;
	while(count--); 
}