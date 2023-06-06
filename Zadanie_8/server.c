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

void exit_func()
{
	delete_queue(QUEUE_NAME);
}

void exit_signal_handler()
{
	printf ("\nClosing server thru SIGINT.\n");
	exit(EXIT_SUCCESS);
}

void print_attributes(struct mq_attr a)
{
    printf ("mq_flags: %ld\n", a.mq_flags);
    printf ("mq_maxmsg: %ld\n", a.mq_maxmsg);
    printf ("mq_msgsize: %ld\n", a.mq_msgsize);
    printf ("mq_curmsgs: %ld\n\n", a.mq_curmsgs);
}

int main () {

	int client_PID;
	char buffor[MAX_LENGHT];
	int num1, num2, result;
	char operation;
	char result_buffor[MAX_LENGHT];
	mqd_t msq_desc;
	mqd_t answer_q;


	msq_desc = init_queue (QUEUE_NAME, O_RDONLY);

	{
		struct mq_attr attributes = queue_attributes(msq_desc);
		printf ("Queue created: %s, descriptor: %d\n", QUEUE_NAME, msq_desc);
		print_attributes(attributes);
	}

	if (atexit (exit_func) != 0)
    {
		perror("atexit error.\n");
		exit(EXIT_FAILURE);
	}

	if (signal (SIGINT,exit_signal_handler) == SIG_ERR)
    {
		perror("signal error.\n");
		exit(EXIT_FAILURE);
	}


	while (1)
    {

		queue_receive (msq_desc, buffor, NULL);

		sscanf(buffor, "%d %d%c%d", &client_PID, &num1, &operation, &num2);

		printf ("Operation from %d --- operation: %d%c%d\n", client_PID, num1, operation, num2);

		if (operation == '+')
        {
			result = num1 + num2;
			sprintf (result_buffor, "%d", result);
		}
        else if (operation == '-')
        {
            result = num1 - num2;
			sprintf (result_buffor, "%d", result);
		}
        else if (operation == '*')
        {
            result = num1 * num2;
			sprintf (result_buffor, "%d", result);
		}
        else if (operation == '/')
        {
            result = num1 / num2;
			sprintf (result_buffor, "%d", result);
		}
        else
        {
			sprintf (result_buffor, "Unknown operation.");
		}

		sleep(1);

		sprintf (buffor, "/%d", client_PID);
		answer_q = open_queue (buffor, O_WRONLY);

		printf ("Sending answer: %s to process: %d\n", result_buffor, client_PID);
		queue_send (answer_q, result_buffor, 1);
		close_queue (answer_q);
	}

	delete_queue (QUEUE_NAME);

	printf ("Server end.\n");

	return 0;
}
