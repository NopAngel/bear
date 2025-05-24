#ifndef UDP_H
#define UDP_H

#define MAX_UDP_DATA 512  // 🔥 Tamaño máximo de datos en un paquete UDP

typedef struct {
    unsigned short source_port;   // Puerto de origen
    unsigned short dest_port;     // Puerto de destino
    unsigned short length;        // Tamaño total del paquete
    unsigned short checksum;      // Verificación de datos (opcional)
    char data[MAX_UDP_DATA];      // 🔥 Datos enviados
} UDP_Packet;

// **Funciones UDP**
void send_udp_packet(unsigned short src_port, unsigned short dest_port, const char *msg);
void receive_udp_packet(char *buffer, unsigned int buffer_size);
void custom_strcpy1(char *dest, const char *src);
void send_packet_to_network(const char *packet, unsigned int size);

#endif


