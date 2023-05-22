###############################################################################
#							  Makefile do projektu							  #
#							   Semafory Zadanie 6							  #
#																			  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run6, clean, tar

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -std=c99 -pedantic -pthread -D_POSIX_SOURCE
Lflags = -Wall -std=c99 -pedantic -c -g
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))

#==============================================================================
# ZMIENNE:

R = incementation.x
PROCNUM = 
CRITNUM = 


#==============================================================================
# ZALEZNOSCI:

semaphore.o: semaphore.h semaphore.c
	$(CO) $(Lflags) semaphore.c

incrementation.x: incrementation.c semaphore.o
	$(CO) $(Cflags) -o $@ $^
	
multiplier.x: multiplier.c semaphore.o incrementation.x
	$(CO) $(Cflags) -o $@ multiplier.c semaphore.o


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: multiplier.x incrementation.x semaphore.o


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run6
run6: multiplier.x
	./multiplier.x $(R) $(PROCNUM) $(CRITNUM)
	rm numer.txt


#==============================================================================
# Czyszczenie

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
