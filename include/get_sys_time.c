unsigned int get_system_time() {
    
    static unsigned int time_counter = 0;
    return time_counter++;  
}
