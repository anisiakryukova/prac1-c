CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = cmdcalc
OBJS = main.o calc.o
 
.PHONY: all clean run
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
 
main.o: main.c calc.h
	$(CC) $(CFLAGS) -c main.c -o main.o
 
calc.o: calc.c calc.h
	$(CC) $(CFLAGS) -c calc.c -o calc.o
 
clean:
	rm -f $(OBJS) $(TARGET)
 
run: $(TARGET)
	./$(TARGET) 41 + 33 111 - 8 22 '*' 5 221 % 111 100 + 13 -k 2

