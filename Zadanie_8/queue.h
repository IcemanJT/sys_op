/*
################

Jeremi Toroj, zadanie 8

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#ifndef QUEUE_H
#define QUEUE_H


mqd_t init_queue (const char *name, int oflag);
mqd_t open_queue (const char *name, int oflag);
void queue_send (mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio);
void queue_receive (mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio);
void close_queue (mqd_t mq_des);
void delete_queue (const char *name);
struct mq_attr queue_attributes (mqd_t mq_des);

#endif
