/*
################

Jeremi Toroj, zadanie 6

################
*/

#ifndef SEMAPHORE_H

#define SEMAPHORE_H

sem_t *init_semaph(const char *name);
sem_t *open_semaph(const char *name);
int semaph_get_val(sem_t *sem);
void semaph_up(sem_t *sem);
void semaph_down(sem_t *sem);
void close_semaph(sem_t *sem);
void delete_semaph(const char *name);

#endif
