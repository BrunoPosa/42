#include "../inc/file_to_list.h"

/*
// fov - [0-180]
int
*/

int process_fov(t_list *current)
{
    printf("process fov\n");

    int i;
    int atoi_overflow;
    char *sub_string;

    atoi_overflow = 0;
// find len until space
    i = len_until_space(current->s);
// printf("LEN UNITL SPACE = %d\n", i);

// iscolate argument
    sub_string = ft_substr(current->s, 0, i);
    if (sub_string == NULL)
		return (ret_error(E_MALLOC, current));
    printf("substring = %s\n", sub_string);

// check if only legal chars
    if(!only_legal_chars(sub_string, LEGAL_CHARS6))
        return (free(sub_string), ret_error(E_UINT_CHARS, current));

// convert argument to int
    current->fov = ft_atoi(sub_string, &atoi_overflow);
    if (atoi_overflow
        || current->fov < 0
        || current->fov > 180)
        return (free(sub_string), ret_error(E_FOV_RANGE, current));
printf("-----------------fov = %d\n", current->fov);
// // check within range 0-180
//     if (!current->fov < 0 || !current->fov > 180)
//         return (ret_error(E_FOV_RANGE, current));

// move pointner past argument
    current->s = current->s + i;

// move pointer to next argument
    current->s = skip_space(current->s);
    // printf("data = %s\n", current->s);
free(sub_string);

return (E_SUCCESS);
}