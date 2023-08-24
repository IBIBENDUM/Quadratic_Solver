CC = g++
CFLAGS = -c -Wall

all: main
test: tester
main: main.o quad_solver.o quad_solver_interactive.o comparators.o
	$(CC) main.o quad_solver.o quad_solver_interactive.o comparators.o -o main.exe

tester: tester.o quad_solver.o comparators.o quadratka_test.o
	$(CC) tester.o quad_solver.o comparators.o quadratka_test.o -o tester.exe
tester.o: tester.cpp
	$(CC) $(CFLAGS) tester.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
quadratka_test.o: quadratka_test.cpp
	$(CC) $(CFLAGS) quadratka_test.cpp
quad_solver.o: quad_solver.cpp
	$(CC) $(CFLAGS) quad_solver.cpp
quad_solver_interactive.o: quad_solver_interactive.cpp
	$(CC) $(CFLAGS) quad_solver_interactive.cpp
comparators.o: comparators.cpp
	$(CC) $(CFLAGS) comparators.cpp
clean:
	rm -rf *.o main


