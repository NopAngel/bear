// compiler.c
#include "compile.h"
#include "../../fs/k_printf.h"
#include "../../fs/k_printf_noline.h"
#include "../itoa.h"

#define NULL ((void*)0)  

#define WHITE_TXT 0x07
#define GRAY_TXT 0x08
#define AQUA_TXT 0x03
#define RED_TXT 0x04
#define BLUE_TXT 0x09
#define PURPLE_TXT 0x07
#define ORANGE_TXT 0x06
#define BLACK_TXT 0x00
#define PINK_TXT 0x05
#define GREEN_TXT 0x02
#define DARKBLUE_TXT 0x01
#define YELLOW_TXT 0x0E

#define RED_TXT_BG 0x44
#define AQUA_TXT_BG 0x33
#define WHITE_TXT_BG 0x77
#define BLUE_TXT_BG 0x99
#define GREEN_TXT_BG 0x22
#define PURPLE_TXT_BG 0x77
#define PINK_TXT_BG 0x55
#define SCREEN_ROWS 25 
#define CYAN_TXT 3  
int compiler_cursor_y;

int compiler_strlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') length++;
    return length;
}

void compiler_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void compiler_strncpy(char* dest, const char* src, int n) {
    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    if (i < n) dest[i] = '\0';
}

void compiler_strcat(char* dest, const char* src) {
    int dest_len = compiler_strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

int compiler_strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

int compiler_strncmp(const char* str1, const char* str2, int n) {
    while (n-- && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    if (n < 0) return 0;
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char* compiler_strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == c) return (char*)str;
        str++;
    }
    return NULL;
}

int compiler_atoi(const char* str) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

void init_compiler(CompilerState* state) {
    state->var_count = 0;
    state->func_count = 0;
    state->output_index = 0;
    state->output[0] = '\0';
    state->current_line = 0;
    state->return_value = 0;
    state->should_return = 0;
}

Variable* find_variable(CompilerState* state, const char* name) {
    for (int i = 0; i < state->var_count; i++) {
        if (compiler_strcmp(state->variables[i].name, name) == 0) {
            return &state->variables[i];
        }
    }
    return NULL;
}

Function* find_function(CompilerState* state, const char* name) {
    for (int i = 0; i < state->func_count; i++) {
        if (compiler_strcmp(state->functions[i].name, name) == 0) {
            return &state->functions[i];
        }
    }
    return NULL;
}

void add_variable(CompilerState* state, const char* name, int value, int type) {
    Variable* existing = find_variable(state, name);
    if (existing != NULL) {
        existing->value = value;
        existing->type = type;
        return;
    }
    
    if (state->var_count < 100) {
        compiler_strcpy(state->variables[state->var_count].name, name);
        state->variables[state->var_count].value = value;
        state->variables[state->var_count].type = type;
        state->var_count++;
    }
}

void add_function(CompilerState* state, const char* name, int return_type) {
    if (state->func_count < 50) {
        compiler_strcpy(state->functions[state->func_count].name, name);
        state->functions[state->func_count].return_type = return_type;
        state->functions[state->func_count].param_count = 0;
        state->functions[state->func_count].code[0] = '\0';
        state->func_count++;
    }
}

int get_color_code(const char* color_name) {
    if (compiler_strcmp(color_name, "red") == 0) return 0x0C;
    if (compiler_strcmp(color_name, "green") == 0) return 0x0A;
    if (compiler_strcmp(color_name, "blue") == 0) return 0x09;
    if (compiler_strcmp(color_name, "yellow") == 0) return 0x0E;
    if (compiler_strcmp(color_name, "cyan") == 0) return 0x0B;
    if (compiler_strcmp(color_name, "magenta") == 0) return 0x0D;
    if (compiler_strcmp(color_name, "white") == 0) return 0x0F;
    if (compiler_strcmp(color_name, "black") == 0) return 0x00;
    if (compiler_strcmp(color_name, "orange") == 0) return 0x0C;
    if (compiler_strcmp(color_name, "gray") == 0) return 0x08;
    return 0x0F;
}

int evaluate_condition(CompilerState* state, const char* condition) {
    char cond_copy[256];
    compiler_strcpy(cond_copy, condition);
    
    char* op = NULL;
    char* operators[] = {"==", "!=", ">", "<", ">=", "<="};
    
    for (int i = 0; i < 6; i++) {
        op = compiler_strchr(cond_copy, operators[i][0]);
        if (op && op[1] == operators[i][1]) {
            *op = '\0';
            char* left = cond_copy;
            char* right = op + 2;
            
            while (*left == ' ') left++;
            while (*right == ' ') right++;
            
            int left_val = 0;
            int right_val = 0;
            
            Variable* left_var = find_variable(state, left);
            Variable* right_var = find_variable(state, right);
            
            if (left_var) left_val = left_var->value;
            else left_val = compiler_atoi(left);
            
            if (right_var) right_val = right_var->value;
            else right_val = compiler_atoi(right);
            
            if (compiler_strcmp(operators[i], "==") == 0) return left_val == right_val;
            if (compiler_strcmp(operators[i], "!=") == 0) return left_val != right_val;
            if (compiler_strcmp(operators[i], ">") == 0) return left_val > right_val;
            if (compiler_strcmp(operators[i], "<") == 0) return left_val < right_val;
            if (compiler_strcmp(operators[i], ">=") == 0) return left_val >= right_val;
            if (compiler_strcmp(operators[i], "<=") == 0) return left_val <= right_val;
        }
    }
    
    return 0;
}

int compile_file(CompilerState* state, const char* filename) {
    char content[1024];
    int bytes = fs_read(filename, content, 1024);
    if (bytes <= 0) {
        k_printf("Error: File not found", compiler_cursor_y++, COMPILER_ERROR);
        return 0;
    }
    return compile_code(state, content);
}

int compile_code(CompilerState* state, const char* code) {
    char line[256];
    int pos = 0;
    int line_num = 1;
    int success = 1;
    
    init_compiler(state);
    
    while (*code != '\0') {
        pos = 0;
        while (*code != '\0' && *code != '\n' && pos < 255) {
            line[pos++] = *code++;
        }
        line[pos] = '\0';
        
        while (*code == '\n' || *code == '\r') code++;
        
        if (!compile_line(state, line, line_num)) success = 0;
        line_num++;
    }
    
    return success;
}

int compile_line(CompilerState* state, const char* line, int line_num) {
    while (*line == ' ' || *line == '\t') line++;
    if (*line == '\0' || *line == '#') return 1;
    
    if (compiler_strncmp(line, "print ", 6) == 0) return compile_print(state, line + 6, line_num);
    if (compiler_strncmp(line, "if ", 3) == 0) return compile_if(state, line + 3, line_num);
    if (compiler_strncmp(line, "elif ", 5) == 0) return compile_elif(state, line + 5, line_num);
    if (compiler_strncmp(line, "else", 4) == 0) return compile_else(state, line + 4, line_num);
    if (compiler_strncmp(line, "while ", 6) == 0) return compile_while(state, line + 6, line_num);
    if (compiler_strncmp(line, "for ", 4) == 0) return compile_for(state, line + 4, line_num);
    if (compiler_strncmp(line, "func ", 5) == 0) return compile_function(state, line + 5, line_num);
    if (compiler_strncmp(line, "return ", 7) == 0) return compile_return(state, line + 7, line_num);
    if (compiler_strncmp(line, "clear", 5) == 0) return compile_clear(state, line + 5, line_num);
    if (compiler_strncmp(line, "exit ", 5) == 0) return compile_exit(state, line + 5, line_num);
    
    if (is_variable_assignment(line)) return compile_variable_assignment(state, line, line_num);
    if (is_function_call(line)) return compile_function_call(state, line, line_num);
    
    k_printf("Error: Unknown command at line ", compiler_cursor_y++, COMPILER_ERROR);
    char line_str[10];
    itoa(line_num, line_str, 10);
    k_printf(line_str, compiler_cursor_y, COMPILER_ERROR);
    k_printf(": ", compiler_cursor_y, COMPILER_ERROR);
    k_printf(line, compiler_cursor_y++, COMPILER_ERROR);
    return 0;
}

int compile_print(CompilerState* state, const char* line, int line_num) {
    const char* text_start = compiler_strchr(line, '"');
    if (!text_start) return 0;
    const char* text_end = compiler_strchr(text_start + 1, '"');
    if (!text_end) return 0;
    
    int text_length = text_end - text_start - 1;
    char text[256];
    compiler_strncpy(text, text_start + 1, text_length);
    text[text_length] = '\0';
    
    const char* color_start = text_end + 1;
    while (*color_start == ' ' || *color_start == '\t') color_start++;
    
    char color[20];
    int color_pos = 0;
    while (*color_start != '\0' && *color_start != ' ' && color_pos < 19) {
        color[color_pos++] = *color_start++;
    }
    color[color_pos] = '\0';
    
    int color_code = get_color_code(color);
    
    char compiled[300];
    compiler_strcpy(compiled, "PRINT:");
    compiler_strcat(compiled, text);
    compiler_strcat(compiled, ":");
    
    char color_str[10];
    itoa(color_code, color_str, 10);
    compiler_strcat(compiled, color_str);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int compile_if(CompilerState* state, const char* line, int line_num) {
    const char* brace = compiler_strchr(line, '{');
    if (!brace) return 0;
    
    int cond_length = brace - line;
    char condition[256];
    compiler_strncpy(condition, line, cond_length);
    condition[cond_length] = '\0';
    
    char compiled[300];
    compiler_strcpy(compiled, "IF:");
    compiler_strcat(compiled, condition);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int compile_elif(CompilerState* state, const char* line, int line_num) {
    const char* brace = compiler_strchr(line, '{');
    if (!brace) return 0;
    
    int cond_length = brace - line;
    char condition[256];
    compiler_strncpy(condition, line, cond_length);
    condition[cond_length] = '\0';
    
    char compiled[300];
    compiler_strcpy(compiled, "ELIF:");
    compiler_strcat(compiled, condition);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int compile_else(CompilerState* state, const char* line, int line_num) {
    if (!compiler_strchr(line, '{')) return 0;
    compiler_strcat(state->output, "ELSE;");
    return 1;
}

int compile_while(CompilerState* state, const char* line, int line_num) {
    const char* brace = compiler_strchr(line, '{');
    if (!brace) return 0;
    
    int cond_length = brace - line;
    char condition[256];
    compiler_strncpy(condition, line, cond_length);
    condition[cond_length] = '\0';
    
    char compiled[300];
    compiler_strcpy(compiled, "WHILE:");
    compiler_strcat(compiled, condition);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int compile_for(CompilerState* state, const char* line, int line_num) {
    const char* brace = compiler_strchr(line, '{');
    if (!brace) return 0;
    
    int cond_length = brace - line;
    char condition[256];
    compiler_strncpy(condition, line, cond_length);
    condition[cond_length] = '\0';
    
    char compiled[300];
    compiler_strcpy(compiled, "FOR:");
    compiler_strcat(compiled, condition);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int compile_function(CompilerState* state, const char* line, int line_num) {
    char func_name[32];
    int name_pos = 0;
    
    while (*line != ' ' && *line != '(' && name_pos < 31) {
        func_name[name_pos++] = *line++;
    }
    func_name[name_pos] = '\0';
    
    add_function(state, func_name, 0);
    compiler_strcat(state->output, "FUNC:");
    compiler_strcat(state->output, func_name);
    compiler_strcat(state->output, ";");
    return 1;
}

int compile_return(CompilerState* state, const char* line, int line_num) {
    char value[64];
    int value_pos = 0;
    
    while (*line != '\0' && value_pos < 63) {
        value[value_pos++] = *line++;
    }
    value[value_pos] = '\0';
    
    char compiled[100];
    compiler_strcpy(compiled, "RETURN:");
    compiler_strcat(compiled, value);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int compile_clear(CompilerState* state, const char* line, int line_num) {
    compiler_strcat(state->output, "CLEAR;");
    return 1;
}

int compile_exit(CompilerState* state, const char* line, int line_num) {
    char code[10];
    int code_pos = 0;
    
    while (*line != '\0' && code_pos < 9) {
        code[code_pos++] = *line++;
    }
    code[code_pos] = '\0';
    
    char compiled[20];
    compiler_strcpy(compiled, "EXIT:");
    compiler_strcat(compiled, code);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int is_variable_assignment(const char* line) {
    return compiler_strchr(line, '=') != NULL;
}

int is_function_call(const char* line) {
    return compiler_strchr(line, '(') != NULL && compiler_strchr(line, ')') != NULL;
}

int compile_variable_assignment(CompilerState* state, const char* line, int line_num) {
    const char* equals = compiler_strchr(line, '=');
    if (!equals) return 0;
    
    char var_name[32];
    int name_pos = 0;
    const char* name_start = line;
    
    while (name_start < equals && *name_start == ' ') name_start++;
    while (name_start < equals && *name_start != ' ' && name_pos < 31) {
        var_name[name_pos++] = *name_start++;
    }
    var_name[name_pos] = '\0';
    
    const char* value_start = equals + 1;
    while (*value_start == ' ') value_start++;
    
    char value[64];
    int value_pos = 0;
    while (*value_start != '\0' && value_pos < 63) {
        value[value_pos++] = *value_start++;
    }
    value[value_pos] = '\0';
    
    int var_value = 0;
    if (value[0] == '"') {
        var_value = (int)value;
        add_variable(state, var_name, var_value, 1);
    } else if (compiler_strcmp(value, "true") == 0) {
        add_variable(state, var_name, 1, 2);
    } else if (compiler_strcmp(value, "false") == 0) {
        add_variable(state, var_name, 0, 2);
    } else {
        var_value = compiler_atoi(value);
        add_variable(state, var_name, var_value, 0);
    }
    
    char compiled[100];
    compiler_strcpy(compiled, "VAR:");
    compiler_strcat(compiled, var_name);
    compiler_strcat(compiled, "=");
    compiler_strcat(compiled, value);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

int compile_function_call(CompilerState* state, const char* line, int line_num) {
    char func_name[32];
    int name_pos = 0;
    const char* paren = compiler_strchr(line, '(');
    
    const char* name_start = line;
    while (name_start < paren && *name_start == ' ') name_start++;
    while (name_start < paren && *name_start != ' ' && name_pos < 31) {
        func_name[name_pos++] = *name_start++;
    }
    func_name[name_pos] = '\0';
    
    char compiled[100];
    compiler_strcpy(compiled, "CALL:");
    compiler_strcat(compiled, func_name);
    compiler_strcat(compiled, ";");
    
    compiler_strcat(state->output, compiled);
    return 1;
}

void execute_compiled_code(CompilerState* state) {
    int original_cursor_y = compiler_cursor_y;
    state->current_line = compiler_cursor_y + 1;
    state->should_return = 0;
    state->return_value = 0;
    
    char* code_ptr = state->output;
    int if_condition_failed = 0;
    int skip_until_else = 0;
    int while_start_pos = 0;
    char while_condition[256];
    
    while (*code_ptr != '\0' && !state->should_return) {
        if (compiler_cursor_y >= SCREEN_ROWS - 1) {
            scroll_screen();
            compiler_cursor_y = SCREEN_ROWS - 1;
        }
        
        char command[256];
        int i = 0;
        
        while (*code_ptr != '\0' && *code_ptr != ';' && i < 255) {
            command[i++] = *code_ptr++;
        }
        command[i] = '\0';
        if (*code_ptr == ';') code_ptr++;
        
        if (skip_until_else) {
            if (compiler_strncmp(command, "ELSE", 4) == 0) {
                skip_until_else = 0;
            }
            continue;
        }
        
        if (compiler_strncmp(command, "PRINT:", 6) == 0) {
            char* text = command + 6;
            char* color_pos = compiler_strchr(text, ':');
            if (color_pos) {
                *color_pos = '\0';
                int color = compiler_atoi(color_pos + 1);
                k_printf(text, compiler_cursor_y++, color);
            }
        }
        else if (compiler_strncmp(command, "VAR:", 4) == 0) {
        }
        else if (compiler_strncmp(command, "IF:", 3) == 0) {
            int result = evaluate_condition(state, command + 3);
            if (!result) {
                skip_until_else = 1;
            }
        }
        else if (compiler_strncmp(command, "ELIF:", 5) == 0) {
            if (skip_until_else) {
                int result = evaluate_condition(state, command + 5);
                if (result) {
                    skip_until_else = 0;
                }
            }
        }
        else if (compiler_strcmp(command, "ELSE") == 0) {
            skip_until_else = 0;
        }
        else if (compiler_strncmp(command, "RETURN:", 7) == 0) {
            state->return_value = compiler_atoi(command + 7);
            state->should_return = 1;
        }
        else if (compiler_strcmp(command, "CLEAR") == 0) {
            k_clear_screen();
            compiler_cursor_y = 0;
        }
        else if (compiler_strncmp(command, "EXIT:", 5) == 0) {
            state->should_return = 1;
        }
        
        state->current_line = compiler_cursor_y;
    }
    
    compiler_cursor_y = state->current_line;
}