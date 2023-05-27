/*
################

Jeremi Toroj, zadanie 7

################
*/

#ifndef SHARED_H
#define SHARED_H

int creat_sm(const char *name);
int open_sm(const char *name);
void sm_setlenght(int fd, off_t length);
void close_sm(int fd);
void delete_sm(const char *name);
void *map_sm(int fd, size_t length);
void delete_map(void *address, size_t length);

#endif
