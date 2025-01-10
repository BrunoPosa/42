#include "../inc/file_to_list.h"


// int	check_filename(char *filename)
// {
// 	check len.
// 	last three chars == .rt
// }


int	file_to_list(char *filename, t_list **l)
{
	int fd;
	char *line;
	t_list *tmp;
	// tmp = NULL;
	// init_node(&tmp);
	// if(check_filename(filename))
	// 	return(??)

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		// handle blank line. break?
		if ((line[0] == '\n' || line[0] == '\0') && ft_strlen(line) == 1)
		{
			free(line);
			line = get_next_line(fd);
		}
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			printf("Error: malloc failed\n");
			return (-1);
		}
		ft_lstadd_back(l, tmp);
		line = get_next_line(fd);	
	}
	close(fd);
	return (0);
}