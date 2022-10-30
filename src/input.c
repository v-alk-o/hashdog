#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"


void flush_input_buffer(FILE* input)
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getc(input);
}


int read_string_and_check_size(char *str, int str_len, FILE* input)
{
    char *line_feed_pos = NULL;
    if(fgets(str, str_len, input) != NULL)
    {
        if((line_feed_pos = strchr(str, '\n')) != NULL)
        {
            *line_feed_pos = '\0';
            return 0;
        }
        else
        {
            flush_input_buffer(input);
            return 1;
        }
    }
    else
    {
        flush_input_buffer(input);
        return -1;
    }
}