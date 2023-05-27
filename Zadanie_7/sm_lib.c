/*
################

Jeremi Toroj, zadanie 7

################
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "sm_lib.h"

#define FAILURE -1

int creat_sm(const char *name)
{
	int fd = shm_open(name, O_EXCL | O_RDWR | O_CREAT, 0644);
	if(fd == FAILURE)
    {
		perror("smh_open -creat error.\n");
		exit(EXIT_FAILURE);
	}
    else
    {
		return fd;
	}
}

int open_sm(const char *name)
{
	int fd = shm_open(name, O_RDWR, 0644);
	if(fd == FAILURE)
    {
		perror("smh_open -open error.\n");
		exit(EXIT_FAILURE);
	}
    else
    {
		return fd;
	}
}

void sm_setlenght(int fd, off_t length)
{
	if(ftruncate(fd, length) == FAILURE)
    {
		perror("ftruncate error.\n");
		exit(EXIT_FAILURE);
	}
}

void close_sm(int fd)
{
	if(close(fd) == FAILURE)
    {
		perror("close - for shm error.\n");
		exit(EXIT_FAILURE);
	}
}

void delete_sm(const char *name)
{
	if(shm_unlink(name) == FAILURE)
    {
		perror("smh_unlink error.\n");
		exit(EXIT_FAILURE);
	}
}

void *map_sm(int fd, size_t length)
{
	void *address = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(address == MAP_FAILED)
    {
		perror("mmap error.\n");
		exit(EXIT_FAILURE);
	}
    else
    {
		return address;
	}
}

void delete_map(void *address, size_t length)
{
	if(munmap(address, length) == FAILURE)
    {
		perror("munmap error.\n");
		exit(EXIT_FAILURE);
	}
}
