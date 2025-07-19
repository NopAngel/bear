#include "usb_driver.h"
#include "bear/printk.h"

int main() {
    // Inicializa el controlador USB
    usb_init();

    // Simula la conexión de un dispositivo en el puerto 1
    usb_ports[1] = USB_STATE_CONNECTED;

    // Detecta un dispositivo en el puerto 1
    if (usb_detect_device(1) == USB_STATE_CONNECTED) {
        k_printf("Dispositivo conectado en el puerto 1.\n", 17, 0x0F); // Línea 17
    }

    // Envía datos al dispositivo conectado
    uint8_t data_to_send[] = {0x01, 0x02, 0x03, 0x04};
    usb_send_data(1, data_to_send, 4);

    // Recibe datos desde el dispositivo conectado
    uint8_t data_received[4];
    usb_receive_data(1, data_received, 4);

    return 0;
}
