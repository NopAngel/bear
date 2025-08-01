typedef struct {
    unsigned short source_port;
    unsigned short dest_port;
    unsigned short length;
    unsigned short checksum;
    char data[512]; 
} UDP_Packet;

void send_packet_to_network(const char *packet, unsigned int size) {
    k_printf("Simulating UDP packet send...\n", 0, YELLOW_TXT);
}

void send_udp_packet(unsigned short src_port, unsigned short dest_port, const char *msg) {
    UDP_Packet packet;

    packet.source_port = src_port;
    packet.dest_port = dest_port;
    packet.length = sizeof(UDP_Packet);
    packet.checksum = 0;  
    custom_strcpy(packet.data, msg); 

    send_packet_to_network((char *)&packet, sizeof(UDP_Packet));  
}

void custom_strcpy1(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';  
}

