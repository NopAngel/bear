static inline void outw(unsigned short port, unsigned short data);

unsigned char scancode; // Declaración
// Convierte un número entero a una cadena (base 10)
void int_to_string(int number, char *buffer, int buffer_size) {
    int index = buffer_size - 2; // Última posición utilizable
    buffer[buffer_size - 1] = '\0'; // Termina la cadena con un null terminator

    // Si el número es negativo
    if (number < 0) {
        number = -number; // Convierte a positivo
        while (number > 0 && index >= 0) {
            buffer[index--] = '0' + (number % 10);
            number /= 10;
        }
        if (index >= 0) buffer[index--] = '-'; // Añade el signo negativo
    } else {
        // Para números positivos
        while (number > 0 && index >= 0) {
            buffer[index--] = '0' + (number % 10);
            number /= 10;
        }
    }

    // Si el número es 0
    if (number == 0 && index >= 0) {
        buffer[index--] = '0';
    }

    // Desplazar el resultado al principio del buffer
    for (int i = 0; i < buffer_size - index - 2; i++) {
        buffer[i] = buffer[index + 1 + i];
    }
}


unsigned char read_scancoded();


void display_game_over_space_invaders();

void draw_car();
void draw_road();


void move_car(int dx, int dy);

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line, unsigned int color);
unsigned int k_printf_no_newline(const char *message, unsigned int line, unsigned int color);
void handle_input_car(unsigned char scancode);


#include "colors.h"
#define KEYBOARD_PORT 0x60       // Puerto para leer el teclado
#define SCREEN_BUFFER ((unsigned char *)0xb8000) // Memoria de video
#define SCREEN_COLUMNS 80       // Columnas en modo texto
#define SCREEN_ROWS 25          // Filas en modo texto
#define INPUT_BUFFER_SIZE 256  
void generate_food_position();
void display_game_over();
void delay(int cycles);
void k_main();
void draw_score();
void handle_input(unsigned char scancode);


unsigned char readd_scancode();
void keyboard_handler();




int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

volatile unsigned char current_bg_color = WHITE_BG;




void set_background_color(const char *color_name) {
    // Determinar el color según el nombre
    if (strcmp(color_name, "white") == 0) {
        current_bg_color = WHITE_BG;
    } else {
        k_printf("Error: Color no reconocido.\n", 0, RED_TXT);
        return;
    }

    // Cambiar el color de fondo en toda la pantalla
    char *vidmem = (char *)0xb8000;
    for (int i = 0; i < SCREEN_ROWS * SCREEN_COLUMNS; i++) {
        vidmem[i * 2 + 1] = current_bg_color; // Cambia el atributo de color
    }
}



#define VIDEO_MEMORY 0xB8000
#define WIDTH 80
#define HEIGHT 25

void set_background_white() {
    unsigned short *video_memory = (unsigned short *)VIDEO_MEMORY;
    unsigned char white_background = 0x7; // Fondo blanco
    unsigned char black_text = 0x0;       // Texto negro

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Combinar colores: fondo blanco y texto negro
            unsigned char attribute = (white_background << 4) | black_text;
            video_memory[y * WIDTH + x] = (attribute << 8) | ' '; // Espacio visible
        }
    }
}

int W_MSG() {
     
    set_background_white();

}




int cursor_x = 0;      // Posición horizontal del cursor
int cursor_y = 0;      // Posición vertical del cursor
char input_buffer[INPUT_BUFFER_SIZE]; // Buffer de entrada de texto
int input_index = 0;            // Índice para el buffer de entrada

// Variable para evitar múltiples lecturas del mismo scancode
volatile unsigned char last_scancode = 0;

// Lee un carácter desde el puerto del teclado
unsigned char read_scancode() {
    unsigned char scancode;
    asm volatile ("inb %1, %0" : "=a"(scancode) : "Nd"(KEYBOARD_PORT));
    return scancode;
}

// Tabla simplificada de scancodes a ASCII
const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '/', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, ' ', 0, 0, 0,
};

void scroll_screen() {
    // Desplazar todas las líneas hacia arriba
    for (int i = 1; i < SCREEN_ROWS; i++) {
        for (int j = 0; j < SCREEN_COLUMNS * 2; j++) {
            SCREEN_BUFFER[(i - 1) * SCREEN_COLUMNS * 2 + j] =
                SCREEN_BUFFER[i * SCREEN_COLUMNS * 2 + j];
        }
    }

    // Limpiar la última línea
    for (int j = 0; j < SCREEN_COLUMNS * 2; j++) {
        SCREEN_BUFFER[(SCREEN_ROWS - 1) * SCREEN_COLUMNS * 2 + j] = 0;
    }

    cursor_y = SCREEN_ROWS - 1; // Ajustar el cursor a la última fila
    cursor_x = 0;               // Reiniciar el cursor al inicio de la línea
}


// Escribe un carácter en la pantalla
void put_char(char c) {
    int pos = (cursor_y * SCREEN_COLUMNS + cursor_x) * 2;

    SCREEN_BUFFER[pos] = c;          // Almacenar carácter
    SCREEN_BUFFER[pos + 1] = WHITE_BG;  // Atributo de color (blanco)

    // Actualizamos la posición del cursor
    cursor_x++;
    if (cursor_x >= SCREEN_COLUMNS) {
        cursor_x = 0;
        cursor_y++;
    }

    // Si alcanzamos el final de la pantalla, desplazamos
    if (cursor_y >= SCREEN_ROWS) {
        scroll_screen(); // Llama a la nueva función de desplazamiento
    }
}












#define VIDEO_MEMORY 0xB8000
#define WIDTH 80
#define HEIGHT 25

// Colores
#define LIGHT_BLUE_BG 0x1F  // Fondo azul claro


#define VIDEO_MEMORY 0xB8000
#define WIDTH 80
#define HEIGHT 25
#define PLAYER_SPEED_SNAKE 10000000 // Más lento


// Jugador
typedef struct {
    int x, y; // Posición del jugador
} Player;

Player player = { WIDTH / 2, HEIGHT / 2 }; // Inicio en el centro
Player previous_player;                   // Guarda la posición anterior
int score = 0;                             // Puntuación inicial

// Comida
typedef struct {
    int x, y;
} Food;

Food food = { 10, 10 }; // Posición inicial de la comida

// Limpia la pantalla completa con el fondo azul claro
void clear_screen() {
    char *video_memory = (char *)VIDEO_MEMORY;

    for (int i = 0; i < WIDTH * HEIGHT * 2; i += 2) {
        video_memory[i] = ' ';           // Espacio en blanco
        video_memory[i + 1] = LIGHT_BLUE_BG; // Atributo de color
    }
}

// Dibuja un carácter específico en una posición específica con color
void draw_character(int x, int y, char c, unsigned char color) {
    char *video_memory = (char *)VIDEO_MEMORY;
    int index = (y * WIDTH + x) * 2;

    video_memory[index] = c;        // Carácter
    video_memory[index + 1] = color; // Atributo de color
}

#define MAX_SNAKE_LENGTH 100 // Tamaño máximo de la serpiente

typedef struct {
    int x, y; // Posición en la pantalla
} Position;

// Serpiente
typedef struct {
    Position body[MAX_SNAKE_LENGTH]; // Partes del cuerpo
    int length;                      // Longitud actual
} Snake;

Snake snake; // La serpiente
void init_snake() {
    snake.length = 1; // Comienza con 1 segmento
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
}

void draw_snake() {
    // Dibuja cada segmento del cuerpo de la serpiente
    for (int i = 0; i < snake.length; i++) {
        draw_character(snake.body[i].x, snake.body[i].y, '*', SNAKE_BG);
    }
}

void delay(int cycles) {
    for (volatile int i = 0; i < cycles; i++) {
        // Bucle vacío para retraso
    }
}

void move_snake(int dx, int dy) {
    // Guarda la posición de la cola (último segmento)
    Position last = snake.body[snake.length - 1];

    // Mueve cada parte del cuerpo (de cola a cabeza)
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }

    // Mueve la cabeza
    snake.body[0].x += dx;
    snake.body[0].y += dy;

    // Limita la posición dentro del área de juego
    if (snake.body[0].x < 0) snake.body[0].x = 0;
    if (snake.body[0].x >= WIDTH) snake.body[0].x = WIDTH - 1;
    if (snake.body[0].y < 1) snake.body[0].y = 1; // Evita la fila de puntuación
    if (snake.body[0].y >= HEIGHT) snake.body[0].y = HEIGHT - 1;

    // Verifica si la cabeza toca la comida
    if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
        score++; // Incrementa la puntuación
        generate_food_position(); // Nueva posición para la comida

        // Aumenta la longitud de la serpiente (añade un segmento al final)
        if (snake.length < MAX_SNAKE_LENGTH) {
            snake.body[snake.length] = last; // Usa la posición de la cola
            snake.length++;
        }
    }

    // Verifica si la cabeza choca con el cuerpo
    for (int i = 1; i < snake.length; i++) {
    if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
        display_game_over(); // Muestra "GAME OVER!"
    }
}

}


void draw_score() {
    // Dibuja la puntuación en la parte superior de la pantalla
    char score_str[12];
    int temp_score = score;
    int pos = 0;

    for (int i = 0; i < 12; i++) score_str[i] = ' '; // Limpia el buffer
    score_str[pos++] = 'P';
    score_str[pos++] = 'u';
    score_str[pos++] = 'n';
    score_str[pos++] = 't';
    score_str[pos++] = 'o';
    score_str[pos++] = 's';
    score_str[pos++] = ':';
    score_str[pos++] = ' ';

    do {
        score_str[pos++] = '0' + (temp_score % 10);
        temp_score /= 10;
    } while (temp_score > 0);

    for (int i = 0; i < pos; i++) {
        draw_character(i, 0, score_str[i], LIGHT_BLUE_BG);
    }
}

void display_game_over() {
    clear_screen(); // Limpia la pantalla
    char *message = "GAME OVER!";
    for (int i = 0; message[i] != '\0'; i++) {
        draw_character((WIDTH / 2 - 5) + i, HEIGHT / 2, message[i], RED_TXT);
    }

    delay(5000000); // Pausa antes de volver al menú principal
    k_main();       // Regresa al menú principal
}

void handle_input(unsigned char scancode) {
    if (scancode == 0x11) move_snake(0, -1); // W (arriba)
    else if (scancode == 0x1F) move_snake(0, 1); // S (abajo)
    else if (scancode == 0x1E) move_snake(-1, 0); // A (izquierda)
    else if (scancode == 0x20) move_snake(1, 0); // D (derecha)
}

void generate_food_position() {
    do {
        food.x = (food.x + 7) % WIDTH;
        food.y = (food.y + 3) % HEIGHT;
    } while (food.y == 0); // Evita la fila de la puntuación
}

void draw_game() {
    clear_screen(); // Limpia solo los rastros antiguos
    draw_snake();   // Dibuja la serpiente
    draw_character(food.x, food.y, 'X', APPLE_BG); // Dibuja la comida
    draw_score();   // Dibuja la puntuación en la parte superior
}

void game_loop() {
    init_snake(); // Inicializa la serpiente al empezar
    generate_food_position(); // Genera la primera manzana

    while (1) {
        draw_game();               // Actualiza el estado del juego
        unsigned char scancode = read_scancode(); // Lee la entrada del teclado
        handle_input(scancode);   // Mueve al jugador
        delay(PLAYER_SPEED_SNAKE);      // Controla la velocidad del juego
    }
}




// Captura la entrada del teclado (supuesto que ya está implementada)
unsigned char readd_scancode() {
    unsigned char scancode;
    asm volatile ("inb %1, %0" : "=a"(scancode) : "Nd"(0x60)); // Lee desde el puerto del teclado
    return scancode;
}




// Asumiendo que `read_scancode` ya está implementado:

#define PLAYER_SPEED_CAR 7000000 // Velocidad del carrito
typedef struct {
    int x, y;     // Posición del obstáculo
    int width;    // Ancho del obstáculo
} Obstacle;

typedef struct {
    int x, y; // Posición del carrito
} Car;

Car car = { WIDTH / 2, HEIGHT - 5 }; // Posición inicial del carrito

#define MAX_OBSTACLES 5
Obstacle obstacles[MAX_OBSTACLES];

void init_obstacles() {
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        obstacles[i].x = 12 + (i * 10); // Posición dentro de la carretera
        obstacles[i].y = i * 4;         // Espaciados verticalmente
    }
}

void draw_obstacles() {
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        draw_character(obstacles[i].x, obstacles[i].y, '#', 0x04); // Color rojo
    }
}

void move_obstacles() {
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        obstacles[i].y += 1; // Mueve el obstáculo hacia abajo

        // Reinicia el obstáculo si sale de la pantalla
        if (obstacles[i].y >= HEIGHT) {
            obstacles[i].y = 0;                      // Vuelve a la parte superior
            obstacles[i].x = 12 + (i * 7) % (WIDTH - 24); // Recalcula su posición horizontal
        }
    }
}

int check_collision() {
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        // Verifica si el carrito está dentro del rango del obstáculo
        if ((car.x >= obstacles[i].x && car.x <= obstacles[i].x + 2) && car.y == obstacles[i].y) {
            return 1; // Colisión detectada
        }
    }
    return 0; // No hay colisiones
}


void draw_car() {
    draw_character(car.x, car.y, 'O', 0x0E);           // Rueda izquierda
    draw_character(car.x + 1, car.y, '|', 0x0E);       // Cuerpo central
    draw_character(car.x + 2, car.y, 'O', 0x0E);       // Rueda derecha
}


void draw_score_car(int score) {
    char score_str[12];
    int temp_score = score;
    int pos = 0;

    // Limpia el buffer antes de usarlo
    for (int i = 0; i < 12; i++) score_str[i] = ' ';
    score_str[pos++] = 'S';
    score_str[pos++] = 'c';
    score_str[pos++] = 'o';
    score_str[pos++] = 'r';
    score_str[pos++] = 'e';
    score_str[pos++] = ':';
    score_str[pos++] = ' ';

    // Convierte la puntuación a texto
    do {
        score_str[pos++] = '0' + (temp_score % 10);
        temp_score /= 10;
    } while (temp_score > 0);

    // Dibuja la puntuación en la parte superior izquierda
    for (int i = 0; i < pos; i++) {
        draw_character(i, 0, score_str[i], 0x07); // Texto blanco
    }
}

void handle_input_car(unsigned char scancode) {
    if (scancode == 0x11) move_car(0, -1); // W (arriba)
    else if (scancode == 0x1F) move_car(0, 1); // S (abajo)
    else if (scancode == 0x1E) move_car(-1, 0); // A (izquierda)
    else if (scancode == 0x20) move_car(1, 0); // D (derecha)
}
void move_car(int dx, int dy) {
    car.x += dx;
    car.y += dy;

    // Limitar al carrito dentro de los bordes
    if (car.x < 11) car.x = 11; // No pasa el borde izquierdo
    if (car.x > WIDTH - 13) car.x = WIDTH - 13; // No pasa el borde derecho
    if (car.y < 0) car.y = 0; // No sube más allá de la pantalla
    if (car.y > HEIGHT - 1) car.y = HEIGHT - 1; // No baja más allá de la pantalla
}



void display_game_over_car() {
    clear_screen(); // Limpia la pantalla
    char *message = "GAME OVER!";
    for (int i = 0; message[i] != '\0'; i++) {
        draw_character((WIDTH / 2 - 5) + i, HEIGHT / 2, message[i], 0x04); // Texto rojo
    }

    delay(5000000); // Pausa antes de reiniciar
    k_main();       // Regresa al menú principal
}

void draw_road() {
    for (int y = 0; y < HEIGHT; y++) {
        draw_character(10, y, '|', 0x07);              // Borde izquierdo
        draw_character(WIDTH - 10, y, '|', 0x07);      // Borde derecho
        if (y % 2 == 0) { // Línea discontinua en el centro
            draw_character(WIDTH / 2, y, '|', 0x07);
        }
    }
}



void game_loop_car() {
    int score = 0; // Inicializa la puntuación
    init_obstacles(); // Inicializa los obstáculos

    while (1) {
        clear_screen();          // Limpia la pantalla
        draw_road();             // Dibuja la carretera
        draw_car();              // Dibuja el carrito
        draw_obstacles();        // Dibuja los obstáculos
        draw_score_car(score);   // Dibuja la puntuación

        // Verifica colisiones
        if (check_collision()) {
            display_game_over_car();
        }

        // Mueve los obstáculos hacia abajo
        move_obstacles();

        // Lee y maneja la entrada del teclado
        unsigned char scancode = read_scancode();
        handle_input_car(scancode);

        // Incrementa la puntuación con el tiempo
        score++;

        // Controla la velocidad del juego
        delay(PLAYER_SPEED_CAR);
    }
}



























// Definiciones y constantes
#define MAX_INVADERS 10
#define MAX_MISSILES 5
#define WIDTH 80
#define HEIGHT 25
#define PLAYER_SPEED_SPACE_INVADERS 8000000

// Estructura para la nave
typedef struct {
    int x, y; // Posición de la nave espacial
} SpaceShip;

SpaceShip spaceship = { WIDTH / 2, HEIGHT - 2 }; // Posición inicial

// Estructura para los invasores
typedef struct {
    int x, y;  // Posición del invasor
    int alive; // Si el invasor está vivo
} Invader;

Invader invaders[MAX_INVADERS]; // Lista de invasores

// Estructura para los misiles enemigos
typedef struct {
    int x, y;   // Posición del misil
    int active; // Si el misil está activo
} Missile;

Missile missiles[MAX_MISSILES]; // Lista de misiles enemigos

// Semilla para el generador de números pseudoaleatorios
unsigned int seed = 12345;

// Prototipos de funciones
void clear_screen();
void render_character(int x, int y, char c, unsigned char color);
unsigned int random();
unsigned int random_range(int min, int max);
void init_invaders();
void draw_invaders();
void fire_missile(int invader_index);
void init_missiles();
void move_missiles();
void draw_missiles();
int check_missile_collision();
void display_message(int x, int y, char *message, unsigned char color);
void game_loop_space_invaders();
void delay(int cycles);

// Funciones auxiliares
void render_character(int x, int y, char c, unsigned char color) {
    char *video_memory = (char *)0xB8000;
    int index = (y * WIDTH + x) * 2;

    video_memory[index] = c;
    video_memory[index + 1] = color;
}

unsigned int random() {
    seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
    return seed;
}

unsigned int random_range(int min, int max) {
    return (random() % (max - min + 1)) + min;
}


void handle_input_space_invaders(unsigned char scancode) {
    if (scancode == 0x1E) { // A (izquierda)
        spaceship.x -= 1; // Mueve a la nave a la izquierda
        if (spaceship.x < 1) spaceship.x = 1; // Limita el borde izquierdo
    } else if (scancode == 0x20) { // D (derecha)
        spaceship.x += 1; // Mueve a la nave a la derecha
        if (spaceship.x > WIDTH - 2) spaceship.x = WIDTH - 2; // Limita el borde derecho
    }
}


// Inicializar los invasores
void init_invaders() {
    for (int i = 0; i < MAX_INVADERS; i++) {
        invaders[i].x = 5 + (i * 6);
        invaders[i].y = 2;
        invaders[i].alive = 1;
    }
}

void draw_invaders() {
    for (int i = 0; i < MAX_INVADERS; i++) {
        if (invaders[i].alive) {
            render_character(invaders[i].x, invaders[i].y, 'W', 0x0C); // Rojo
        }
    }
}

void fire_missile(int invader_index) {
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (!missiles[i].active) {
            missiles[i].x = invaders[invader_index].x;
            missiles[i].y = invaders[invader_index].y + 1;
            missiles[i].active = 1;
            break;
        }
    }
}

void init_missiles() {
    for (int i = 0; i < MAX_MISSILES; i++) {
        missiles[i].x = 0;
        missiles[i].y = 0;
        missiles[i].active = 0;
    }
}

void move_missiles() {
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (missiles[i].active) {
            missiles[i].y += 1;
            if (missiles[i].y >= HEIGHT) {
                missiles[i].active = 0; // Desactiva el misil
            }
        }
    }
}

void draw_missiles() {
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (missiles[i].active) {
            render_character(missiles[i].x, missiles[i].y, '|', 0x04); // Rojo
        }
    }
}

unsigned char read_scancoded() {
    unsigned char scancode;
    asm volatile ("inb %1, %0" : "=a"(scancode) : "Nd"(0x60)); // Lee el scancode del puerto 0x60
    return scancode;
}



int check_missile_collision() {
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (missiles[i].active && missiles[i].x == spaceship.x && missiles[i].y == spaceship.y) {
            return 1; // Colisión detectada
        }
    }
    return 0; // No hay colisiones
}

void display_message(int x, int y, char *message, unsigned char color) {
    for (int i = 0; message[i] != '\0'; i++) {
        render_character(x + i, y, message[i], color);
    }
}

// Bucle principal del juego Space Invaders
void game_loop_space_invaders() {
    init_invaders();
    init_missiles();
    unsigned char scancode;

    while (1) {
        clear_screen();
        scancode = read_scancode();
        handle_input_space_invaders(scancode);
        render_character(spaceship.x, spaceship.y, '^', 0x0A); // Dibuja la nave
        draw_invaders();
        draw_missiles();

        // Disparo de misiles enemigos
        if (random_range(0, 19) == 0) {
            int random_invader = random_range(0, MAX_INVADERS - 1);
            if (invaders[random_invader].alive) {
                fire_missile(random_invader);
            }
        }

        move_missiles();

        if (check_missile_collision()) {
            clear_screen();
            k_main();
            break;
        }

        delay(PLAYER_SPEED_SPACE_INVADERS);
    }
}





















#define MAP_WIDTH 20
#define MAP_HEIGHT 15

char map[MAP_HEIGHT][MAP_WIDTH] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#'},
    {'#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#'},
    {'#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

int check_win_condition() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == '.') {
                return 0; // Todavía quedan puntos
            }
        }
    }
    return 1; // Todos los puntos han sido recolectados
}



// Renderizar el Laberinto
void draw_map() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            render_character(x, y, map[y][x], 0x07); // Color blanco para paredes y puntos
        }
    }
}

typedef struct {
    int x, y; 
    int score; 
    int health; // Salud del jugador
} PacMan;

PacMan pacman = {1, 1, 0, 100}; // Empieza con 100 de vida

void draw_health() {
    char health_str[20];
    int_to_string(pacman.health, health_str, 20); // Convierte la salud a texto

    // Mostrar "Health: " seguido del valor de la salud
    char prefix[] = "Health: ";
    int i = 0;

    // Dibujar el prefijo "Health: "
    for (; i < 8; i++) {
        render_character(MAP_WIDTH + 1 + i, 0, prefix[i], 0x0A); // Texto verde
    }

    // Dibujar la salud en pantalla
    for (int j = 0; health_str[j] != '\0'; j++, i++) {
        render_character(MAP_WIDTH + 1 + i, 0, health_str[j], 0x0A);
    }
}



void move_pacman(int dx, int dy) {
    int new_x = pacman.x + dx;
    int new_y = pacman.y + dy;

    // Verificar colisiones con paredes
    if (map[new_y][new_x] != '#') {
        pacman.x = new_x;
        pacman.y = new_y;

        // Recolectar puntos
        if (map[new_y][new_x] == '.') {
            pacman.score++;
            map[new_y][new_x] = ' '; // Elimina el punto del mapa
        }
    }
}


void handle_input_pacman(unsigned char scancode) {
    if (scancode == 0x11) move_pacman(0, -1); // W (arriba)
    else if (scancode == 0x1F) move_pacman(0, 1); // S (abajo)
    else if (scancode == 0x1E) move_pacman(-1, 0); // A (izquierda)
    else if (scancode == 0x20) move_pacman(1, 0); // D (derecha)
}

void draw_pacman() {
    render_character(pacman.x, pacman.y, '@', 0x66); // Color verde para Pac-Man
}

#define MAX_GHOSTS 2

typedef struct {
    int x, y;
    int active;
} Ghost;

Ghost ghosts[MAX_GHOSTS] = {
    {5, 5, 1}, // Fantasma 1
    {10, 8, 1} // Fantasma 2
};

// Movimiento básico de los fantasmas
void move_ghosts() {
    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (ghosts[i].active) {
            // Movimiento básico
            int dx = random_range(-1, 1);
            int dy = random_range(-1, 1);

            int new_x = ghosts[i].x + dx;
            int new_y = ghosts[i].y + dy;

            if (map[new_y][new_x] != '#' && (new_x != pacman.x || new_y != pacman.y)) {
                ghosts[i].x = new_x;
                ghosts[i].y = new_y;
            }

            // Colisión con Pac-Man
            if (ghosts[i].x == pacman.x && ghosts[i].y == pacman.y) {
                pacman.health -= 10; // Reduce la salud
                if (pacman.health <= 0) {
                    clear_screen();
                    display_message(MAP_WIDTH / 2 - 5, MAP_HEIGHT / 2, "GAME OVER!", 0x04);
                    delay(5000000);
                    k_main();
                    return;
                }
            }
        }
    }
}


// Dibujar fantasmas
void draw_ghosts() {
    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (ghosts[i].active) {
            render_character(ghosts[i].x, ghosts[i].y, 'G', 0x0C); // Rojo para fantasmas
        }
    }
}

void game_loop_pacman() {
    unsigned char scancode;

    while (1) {
        clear_screen();

        // Manejo de entrada
        scancode = read_scancode();
        handle_input_pacman(scancode);

        // Actualizaciones
        move_ghosts();

        // Verificar condición de victoria
        if (check_win_condition()) {
            clear_screen();
            display_message(MAP_WIDTH / 2 - 5, MAP_HEIGHT / 2, "YOU WIN!", 0x0A);
            delay(5000000);
            return;
        }

        // Dibujar elementos
        draw_map();
        draw_pacman();
        draw_ghosts();
        draw_health();

        delay(PLAYER_SPEED_SPACE_INVADERS);
    }
}























// Procesar el contenido del buffer de entrada cuando se presiona Enter
void process_input() {
    input_buffer[input_index] = '\0'; // Termina la cadena con un carácter nulo

    // Verificar si el usuario ingresó "test"
    if (strcmp(input_buffer, "test") == 0) {
        k_printf("Hello, World!", cursor_y, GREEN_TXT); // Respuesta
        cursor_y++;
    } else if (strcmp(input_buffer, "snake") == 0) {
    	k_clear_screen();
        game_loop();
        cursor_y = 0;
    } else if (strcmp(input_buffer, "car") == 0) {
    	k_clear_screen();
        game_loop_car();
        cursor_y = 0;
    } else if (strcmp(input_buffer, "spaceinvaders") == 0) {
    	k_clear_screen();
        game_loop_space_invaders();
        cursor_y = 0;
    } else if (strcmp(input_buffer, "clear") == 0) {
    	k_clear_screen();
    	set_background_white();
        cursor_y = 0;
    } 

     else if (strcmp(input_buffer, "pacman") == 0) {
    	game_loop_pacman();
        cursor_y = 0;
    }


     else {
        k_printf("Comando no reconocido.", cursor_y++, RED_TXT); // Mensaje por defecto
    }

    // Después de cada línea, verificamos si el cursor ha llegado al límite
    if (cursor_y >= SCREEN_ROWS) {
        scroll_screen(); // Llama a la función de scroll
    }

    // Reiniciar el buffer de entrada
    input_index = 0;
    cursor_x = 0;
}


// Controlador de teclado con soporte para backspace, espacio y enter
void keyboard_handler() {
    unsigned char scancode = read_scancode();

    if (scancode == last_scancode) {
        return;
    }

    last_scancode = scancode;

    if (scancode < sizeof(scancode_to_ascii)) {
        char ascii = scancode_to_ascii[scancode];

        // Manejar teclas especiales
        if (ascii == '\b') { // Backspace
            if (input_index > 0) {
                input_index--; // Retroceder en el buffer
                if (cursor_x > 0) {
                    cursor_x--;
                } else if (cursor_y > 0) {
                    cursor_y--;
                    cursor_x = SCREEN_COLUMNS - 1;
                }

                int pos = (cursor_y * SCREEN_COLUMNS + cursor_x) * 2;
                SCREEN_BUFFER[pos] = ' ';
                SCREEN_BUFFER[pos + 1] = RED_TXT;
            }
        } else if (ascii == '\n') { // Enter
            process_input(); // Procesar el comando ingresado
        } else if (ascii) { // Otros caracteres
            if (input_index < INPUT_BUFFER_SIZE - 1) { // Evitar desbordamiento
                input_buffer[input_index++] = ascii;
                put_char(ascii);
            }
        }
    }
}



void k_main() 
{
    k_clear_screen();
    W_MSG();

    
    k_printf("                                    -BEARGAMES-                                    ", 0, BLUE_BG_WHITE);
    k_printf("    Author: NopAngel                                                               ", 1, BLUE_BG_WHITE);
    k_printf("    Repository: github.com/NopAngel/beargames                                   ", 2, BLUE_BG_WHITE);
    k_printf("1: 'pacman': Play the PAC-MAN                                                   ", 3, BLUE_BG_WHITE);
    k_printf("2: 'spaceinvaders': Play the Space Invaders                                     ", 4, BLUE_BG_WHITE);
    k_printf("3: 'car': Play the CAR RACE                                                     ", 5, BLUE_BG_WHITE);
    k_printf("4: 'snake': Play the SNAKE                                                      ", 6, BLUE_BG_WHITE);


    cursor_x = 0;
    cursor_y = 8; // Empieza en la fila 8 (debajo del mensaje de bienvenida)

    while (1) {
        keyboard_handler();
    }



};

void k_clear_screen()
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};



unsigned int k_printf(char *message, unsigned int line, unsigned int color)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // chec1k for a new line (upgrated)
		{
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=color;
			i++;
		};
	};

	return(1);
}
