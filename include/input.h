#ifndef INPUT_H
#define INPUT_H

void flush_input_buffer(FILE* input);
int read_string_and_check_size(char *str, int str_len, FILE* input);

#endif