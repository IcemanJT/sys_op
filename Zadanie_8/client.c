/*
################

Jeremi Toroj, zadanie 8

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <mqueue.h>

#include "queue.h"

#define MAX_AMOUNT 10
#define MAX_LENGHT 30
#define QUEUE_NAME "/my_queue"

mqd_t serv;

void exit_func()
{
	close_queue (serv);
}

void exit_signal_handler()
{
	printf ("\nClosing queue thru SIGINT.\n");
	exit(EXIT_SUCCESS);
}

void print_attributes(struct mq_attr a)
{
    printf ("mq_flags: %ld\n", a.mq_flags);
    printf ("mq_maxmsg: %ld\n", a.mq_maxmsg);
    printf ("mq_msgsize: %ld\n", a.mq_msgsize);
    printf ("mq_curmsgs: %ld\n\n", a.mq_curmsgs);
}

int main()
{

	char queue_process_pid[10];
	mqd_t answer_queue;
	char msg[MAX_LENGHT];
	char buffor[MAX_LENGHT+10];


	sprintf (queue_process_pid, "/%d", getpid());


	sleep (1);

	serv = open_queue(QUEUE_NAME, O_WRONLY);

	{
		struct mq_attr attributes = queue_attributes (serv);
        printf ("Queue name: %s, descriptor: %d\n", QUEUE_NAME, serv);
        print_attributes(attributes);
	}

	if (atexit (exit_func) != 0)
    {
		perror("atexit error.\n");
		_exit(EXIT_FAILURE);
	}

	if (signal (SIGINT,exit_signal_handler) == SIG_ERR)
    {
		perror("signal error.\n");
		exit(EXIT_FAILURE);
	}

    // waiting for server
	sleep(1);

	while (1)
    {

		printf ("Math operation: ");
		if (scanf ("%s", msg) == EOF)
        {
			printf ("\nClient exit handler(EOF).\nExiting...\n");
			exit(EXIT_SUCCESS);
		}

		sprintf(buffor, "%d %s", getpid(), msg);

		queue_send(serv, buffor, 1);
		printf ("\nSent massage: %s\n", buffor);

		answer_queue = init_queue(queue_process_pid, O_RDONLY);

		printf ("Waiting for server answer...\n");
		queue_receive(answer_queue, buffor, NULL);
		printf ("Server answer: %s\n", buffor);

		close_queue(answer_queue);
		delete_queue(queue_process_pid);

        sleep(1);
	}

	close_queue (serv);

	printf ("Client end.\n");

	return 0;
}
