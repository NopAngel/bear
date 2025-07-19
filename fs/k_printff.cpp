class VideoMemory {
private:
    static constexpr unsigned int VIDEO_MEMORY_ADDRESS = 0xb8000;

public:
    static unsigned int print(const char* message, unsigned int line, unsigned int color) {
        char* vidmem = reinterpret_cast<char*>(VIDEO_MEMORY_ADDRESS);
        unsigned int i = line * 80 * 2;

        while (*message != 0) {
            if (*message == '\n') { 
                line++;
                i = line * 80 * 2;
                message++;
            } else {
                vidmem[i] = *message;
                i++;
                vidmem[i] = color;
                i++;
                message++;
            }
        }

        return 1;
    }
};
