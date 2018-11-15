#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -pipe saves the files in a temporary location
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: genius

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
genius:  genius.o character.o
	$(CC) $(CFLAGS) -o genius genius.o 

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
genius.o:  Genius.cpp character.h
	$(CC) $(CFLAGS) -c Genius.cpp

character.o: character.cpp character.h
	$(CC) $(CFLAGS) -c character.cpp

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
#board.o:  board.cpp board.h 
#	$(CC) $(CFLAGS) -c board.cpp

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
#scanner.o:  scanner.c scanner.h 
#	$(CC) $(CFLAGS) -c scanner.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~