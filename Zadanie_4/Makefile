#
# make: all, clean, tar
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad4
FNAME1 = text.txt
FNAME2 = text_copy.txt
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: run
run: $(EXEC1)
	./$(EXEC1)
	wait
	diff -s $(FNAME1) $(FNAME2)
#############################
.PHONY: clean tar
# Porzadki
EXECS = $(EXEC1)
clean:
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
