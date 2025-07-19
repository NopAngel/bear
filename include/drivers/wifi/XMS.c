#include "wifi_driver.h"

int main() {
    // Inicializa el controlador Wi-Fi
    wifi_init();

    // Configuración de la red Wi-Fi
    WiFiConfig config = {
        .ssid = "BearOS_Network",
        .password = "password123"
    };

    // Conecta a la red
    wifi_connect(&config);

    // Envía datos
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    wifi_send(data, 4);

    // Recibe datos
    uint8_t buffer[4];
    wifi_receive(buffer, 4);

    // Desconecta de la red
    wifi_disconnect();

    return 0;
}
