#ifndef COMPILER_H
#define COMPILER_H

#define COMPILER_ERROR 0x0C
#define COMPILER_WARNING 0x0E
#define COMPILER_SUCCESS 0x0A
#define COMPILER_INFO 0x0B

typedef struct {
    char name[32];
    int value;
    int type;
} Variable;

typedef struct {
    char name[32];
    int return_type;
    int param_count;
    int param_types[10];
    char code[1024];
} Function;

typedef struct {
    Variable variables[100];
    int var_count;
    
    Function functions[50];
    int func_count;
    
    char output[2048];
    int output_index;
    
    int current_line;
    int return_value;
    int should_return;
} CompilerState;

void init_compiler(CompilerState* state);
int compile_file(CompilerState* state, const char* filename);
int compile_code(CompilerState* state, const char* code);
void execute_compiled_code(CompilerState* state);

#endif