/*
################

Jeremi Toroj, zadanie 8

################
*/

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define FAILURE -1

#define MAX_AMOUNT 10
#define MAX_LENGHT 30
#define QUEUE_NAME "/my_queue"

mqd_t init_queue (const char *name, int oflag)
{
	struct mq_attr attr;
	attr.mq_maxmsg = MAX_AMOUNT;
	attr.mq_msgsize = MAX_LENGHT;
	mqd_t mqd;
	if ((mqd = mq_open(name, O_CREAT | O_EXCL | oflag, 0644, &attr)) == FAILURE)
    {
		perror ("mq_open - creating error.\n");
		exit (EXIT_FAILURE);
	}
	return mqd;
}

mqd_t open_queue (const char *name, int oflag)
{
	mqd_t mqd;
	if ((mqd = mq_open(name, oflag)) == FAILURE)
    {
		perror ("mq_open - opening error.\n");
		exit (EXIT_FAILURE);
	}
	return mqd;
}

void queue_send (mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio)
{
	if (mq_send(mq_des, msg_ptr, MAX_LENGHT, msg_prio) == FAILURE)
    {
		perror ("mq_send error.\n");
		exit (EXIT_FAILURE);
	}
}

void queue_receive (mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio)
{
	if (mq_receive(mq_des, msg_ptr, MAX_LENGHT, msg_prio) == FAILURE)
    {
		perror ("mq_receive error.\n");
		exit (EXIT_FAILURE);
	}
}

void close_queue (mqd_t mq_des)
{
	if (mq_close(mq_des) == FAILURE)
    {
		perror ("mq_close error.\n");
		exit (EXIT_FAILURE);
	}
}

void delete_queue (const char *name)
{
	if (mq_unlink(name) == FAILURE)
    {
		perror ("mq_unlink error.\n");
		exit (EXIT_FAILURE);
	}
}

struct mq_attr queue_attributes (mqd_t mq_des)
{
	struct mq_attr attributes;
	if (mq_getattr(mq_des, &attributes) == FAILURE)
    {
		perror ("mq_getattr error.\n");
		exit (EXIT_FAILURE);
	}
	return attributes;
}
