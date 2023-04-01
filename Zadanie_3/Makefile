#
# make: all, clean, tar
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad3_a
NAME2 = zad3_b
NAME3 = zad3_c
NAME4 = help
#----------------------
EXEC1 = $(NAME1)
EXEX1 = $(NAME1).x
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#----------------------
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o
#----------------------
EXEX4 = $(NAME4).x
OBJS4 = $(NAME4).o
#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
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
all: $(EXEX1) $(EXEC1) $(EXEC2) $(EXEC3) $(EXEX4)
#############################
$(EXEX1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
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
$(EXEX4): $(OBJS4)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: runa
runa: $(EXEC1)
	./$(EXEC1) $(signal) $(action) & pkill -n $(EXEC1) --signal $(signal)
#############################
.PHONY: runb
runb: $(EXEC2) $(EXEX1)
	./$(EXEC2) $(signal) $(action)
#############################
.PHONY: runc
runc: $(EXEC3) $(EXEX1)
	./$(EXEC3) $(signal) $(action)
#############################
.PHONY: clean
# Porzadki
EXECS = $(EXEC1) $(EXEX1) $(EXEC2) $(EXEC3)
clean:
	rm -f *.o *.x *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
