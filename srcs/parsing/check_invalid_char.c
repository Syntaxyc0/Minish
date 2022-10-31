#include "minishell.h"

int check_invalid_char(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '\\')
            return (error_redisplay_line("'\\'", ERR_INVALID, 1));
        else if (input[i] == ';')
            return (error_redisplay_line("';'", ERR_INVALID, 1));
        i++;
    }
    return (0);
}