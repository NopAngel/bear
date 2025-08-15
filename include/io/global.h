#ifndef GLOBAL_H
#define GLOBAL_H

int strlen(const char *str);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, unsigned int n);
int custom_strcmp(const char *str1, const char *str2);
char* find_char(char* str, char c);
char *custom_strcpy(char *dest, const char *src);
char *strcpy(char *dest, const char *src);

#endif // GLOBAL_H