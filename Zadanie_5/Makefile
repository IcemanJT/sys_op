#
# make: all, clean, tar
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
FIFO = /tmp/myfifo
#------------------------
NAME1 = zad5_a
NAME2 = prod
NAME3 = cons
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2)
EXEX2 = $(NAME2).x
OBJS2 = $(NAME2).o

EXEC3 = $(NAME3)
EXEX3 = $(NAME3).x
OBJS3 = $(NAME3).o
#----------------------
#############################
COFLAGS = -Wall
LDFLAGS = -Wall
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
%.x: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEX2) $(EXEX3)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEX2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEX3): $(OBJS3)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: runa
runa: $(EXEC1)
	./$(EXEC1) $(src) $(tgt)
	wait
	diff -s $(src) $(tgt)

#############################
.PHONY: clean tar
# Porzadki
EXECS := $(EXEC1) $(EXEC2) $(EXEC3) $(EXEX2) $(EXEX3)
clean:
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
