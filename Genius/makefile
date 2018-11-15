
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -pipe saves the files in a temporary location
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall

default: genius


genius:  genius.o character.o
	$(CC) $(CFLAGS) -o genius genius.o 


genius.o:  Genius.cpp scanner.h character.h 
	$(CC) $(CFLAGS) -c Genius.cpp

character.o: character.cpp character.h
	$(CC) $(CFLAGS) -c character.cpp

scanner.o: scanner.cpp scanner.h
	$(CC) $(CFLAGS) -c scanner.cpp


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~