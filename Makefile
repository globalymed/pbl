CC=gcc
CFLAGS=-Wall -Wextra -std=c99
OBJS=main.o question.o quiz.o result.o

quiz_system: $(OBJS)
	$(CC) $(CFLAGS) -o quiz_system $(OBJS)

main.o: main.c quiz.h
	$(CC) $(CFLAGS) -c main.c

question.o: question.c quiz.h
	$(CC) $(CFLAGS) -c question.c

quiz.o: quiz.c quiz.h
	$(CC) $(CFLAGS) -c quiz.c

result.o: result.c quiz.h
	$(CC) $(CFLAGS) -c result.c

clean:
	rm -f *.o quiz_system 