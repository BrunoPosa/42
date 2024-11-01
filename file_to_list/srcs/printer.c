#include "../inc/file_to_list.h"

void	ft_list_print(t_list **l)
{
	int i;
	t_list *tmp;

	i = 0;
	tmp = *l;
	while (tmp)
	{
		printf("--- Node %d ---\n", i);

	printf("s = %s\n", l->s);
	printf("type = %d\n", l->type);
	printf("alr = %f\n", l->alr);
	printf("rgb - r = %d", l->rgb->r);
	printf("rgb - g = %d", l->rgb->g);
	printf("rgb - b = %d", l->rgb->b);
	printf("xyz - x = %f", l->xyz->x);
	printf("xyz - y = %f", l->xyz->y);
	printf("xyz - z = %f", l->xyz->z);
	printf("xyz_3d - x = %f", l->xyz_3d->x);
	printf("xyz_3d - x = %f", l->xyz_3d->y);
	printf("xyz_3d - x = %f", l->xyz_3d->z);
	printf("fov = %d\n", l->fov;
	printf("lbr %f\n", l->lbr;
	printf("sd %f\n", l->sd;
	printf("cd %f\n", l->cd;
	printf("ch %f\n", l->ch;
	printf("next %x\n", l->next;





		printf("%s", tmp->content);
	
		if(!tmp->next)
			printf("\n");

		printf("%s", tmp->content2);

		if(!tmp->next)
			printf("\n");

		printf("%s\n", tmp->content3);
		printf("%d\n", tmp->pos);
		i++;
			if(!tmp->next)
			printf("\n");
		printf("--- Node end ---\n\n");
		tmp = tmp->next;
	}
}


// void	ft_tuple_print(t_tuple *t)
// {
// 	if (!t)
// 	{
// 		printf("%sError: tuple is NULL%s\n", RED, ENDCLR);
// 		return ;
// 	}
// 	printf("x: %.3f | y: %.3f | z: %.3f | w: %.1f %s\n",
// 			t->x, t->y, t->z, t->w,
// 			t->w == 0 ? "(VECTOR)" : t->w == 1 ? "(POINT)" : "(neither)");
// }

// void	ft_print_line(char c)
// {
// 	int i;

// 	i = 0;
// 	while (i < 62)
// 	{
// 		write(1, &c, 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

//  void	print_y(char *s)
//  {
// 	printf("%s%s%s", YELLOW, s, ENDCLR);
//  }

//   void	print_r(char *s)
//  {
// 	printf("%s%s%s", RED, s, ENDCLR);
//  }

//  void	print_g(char *s)
//  {
// 	printf("%s%s%s", GREEN, s, ENDCLR);
//  }


// void	ft_colour_printer(t_colour *c)
// {
// 		if (!c)
// 	{
// 		printf("%sError: colour tuple is NULL%s\n", RED, ENDCLR);
// 		return ;
// 	}
// 	printf("r: %.3f | g: %.3f | b: %.3f\n", c->r, c->g, c->b);
// }