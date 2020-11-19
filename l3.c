#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void k_c()
{
	int status;
	wait(&status);
}

void si_pr(int signo)
{
	printf("signal: %d\n", signo);
}

int main(int argc, char *argv[])
{
	int status;
	signal(SIGCHLD, k_c);
	signal(SIGINT, si_pr);
	signal(SIGSTOP, si_pr);
	signal(SIGTTOU, si_pr);
	signal(SIGQUIT, si_pr);
	signal(SIGILL, si_pr);

	if (argc == 1)
	{
		printf("?\ntry\n./l2 -h\n./l2 --help\n");
		exit(1);
	}

	int c = 0;

	char *opt = argv[1];

	pid_t p;

	if (opt[1] == '-')
		opt[1] = 'h';
	if (strcmp(opt, "-hhelp") && (opt[2] != NULL))
	{
		printf("?\ntry\n./l2 -h\n./l2 --help\n");
		exit(1);
	}
	switch (opt[1])
	{
	default:
		printf("?\ntry\n./l2 -h\n./l2 --help\n");
		break;
	case 'h':
		printf("Авторы: Солдатов Даниил\n\tКустов Даниил\n\tКлепцов Дмитрий\n\nВсе доступные аргументы:\n\t-c - Строка ввода команд для вызова проекта из лабораторной 2\n");
		printf("\t-p - Порождение процесса по его имени и возврат в строку команд после завершения дочернего процесса\n");
		printf("\t-s - Перевод процесса в фоновый режим\n\t-k - Тест обработки сигналов\n\t-t - Запускает процесс в фоне\n");
		printf("\nКраткое описание проекта:\n\tПроект позволяет работать с процессами в ОС Linux\n\n");
		printf("Примеры запуска:\n\t./l3 -c <путь к файлу> <аргументы>\n\t./l3 -t <путь к файлу>\n");
		printf("\t./l3 -p <путь к файлу> <аргументы>\n\t./l3 -t <name>\n\t./l3 -s <PID>\n");
		break;
	case 'c':
		execl(argv[2], argv[2], argv[3], argv[4], argv[5], NULL);
		break;
	case 'p':
		switch (p = fork())
		{
		case -1:
			perror("fork");
			exit(-1);
			break;
		case 0:
			printf("child: child-process\n");
			printf("child: PID -- %d\n", getpid());
			printf("child: PID parent -- %d\n", getppid());
			execl(argv[2], argv[2], argv[3], argv[4], argv[5], NULL);
			wait(&status);
			break;
		default:
			printf("parent: parent-process!\n");
			printf("parent: PID -- %d\n", getpid());
			printf("parent: PID child %d\n", p);
			wait(&status);
			break;
		}
		break;
	case 's':
		if (atoi(argv[2]) > 0)
			kill(atoi(argv[2]), SIGTSTP);
		break;
	case 't':
		switch (p = fork())
		{
		case -1:
			perror("fork");
			exit(-1);
			break;
		case 0:
			printf("child: child-process\n");
			printf("child: PID -- %d\n", getpid());
			// kill(getppid(), 9);
			close(stdin);
			close(stdout);
			close(stderr);
			if (setsid() == -1)
				printf("failed to create a deamon");
			char *arg = {"&"};
			printf("child: PID parent -- %d\n", getppid());
			execl(argv[2], argv[2], arg, NULL);
			wait(&status);
			break;
		default:
			printf("parent: parent-process!\n");
			printf("parent: PID -- %d\n", getpid());
			int t = p;
			printf("parent: PID child %d\n", p);
			wait(&status);
			break;
		}
		for (int i = 0; i < 5; i++)
		{
			printf("%d\n", (5 - i));
			usleep(100000);
		}
		break;
	case 'k':
		for (int i = 0; i < 5; i++)
		{
			printf("%d\n", (5 - i));
			usleep(500000);
		}
		break;
	}
}
