#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

/*###################################
###### Learning about threads #######
###################################*/

pthread_t	rotina[2];

struct	s_f2
{
	char	*texto;
	int		valor;
};

void	*rotina_f1(void *p_param)
{
	int	x;
	int	i;

	x = (int *) p_param;
	printf("parametro : %d\n", x);
	i = -1;
	while (++i < 5)
	{
		printf("numero %d id thread: %d\n", i, pthread_self());
		sleep(1);
	}
	pthread_exit(0);
}

void	*rotina_f2(void *p_param)
{
	struct s_f2	*f2;
	int	i;

	i = -1;
	f2 = (struct s_f2 *) p_param;
	while (++i < 5)
	{
		printf("texto %s, valor %d id thread: %lu\n\n",
		f2->texto,
		f2->valor,
		pthread_self());
		sleep(1);
	}
	pthread_exit(NULL);
}

int main()
{
	long unsigned	rc;
	int				parametro;
	struct			 s_f2	*f2;

	system("clear");
	printf("INICIANDO...\n\n");
	f2 = malloc(1 * sizeof(struct s_f2 *));
	f2->texto = strdup("texto");
	f2->valor = 5;
	parametro = 1;
	pthread_create(&rotina[0], NULL, rotina_f1, &parametro);
	pthread_create(&rotina[1], NULL, rotina_f2, &f2);
	printf("id da thread 1: %lu\n\n", rotina[0]);
	printf("id da thread 2: %lu\n\n", rotina[1]);
	rc = (long unsigned) pthread_join(rotina[0], NULL);
	rc = (long unsigned) pthread_join(rotina[1], NULL);
	printf("finalizado com rc %lu\n", rc);
}
