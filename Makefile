CC = g++
CFLAGS = -c -Wall

all: main
test: tester
main: main.o qe_solver.o qe_solver_interactive.o comparators.o format_complex.o
	$(CC) main.o qe_solver.o qe_solver_interactive.o comparators.o format_complex.o -o main.exe

tester: tester.o qe_solver.o comparators.o qe_solver_tester.o format_complex.o
	$(CC) tester.o qe_solver.o comparators.o qe_solver_tester.o format_complex.o -o tester.exe
format_complex.o: format_complex.cpp
	$(CC) $(CFLAGS) format_complex.cpp
tester.o: tester.cpp
	$(CC) $(CFLAGS) tester.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
qe_solver_tester.o: qe_solver_tester.cpp
	$(CC) $(CFLAGS) qe_solver_tester.cpp
qe_solver.o: qe_solver.cpp
	$(CC) $(CFLAGS) qe_solver.cpp
qe_solver_interactive: qe_solver_interactive.cpp
	$(CC) $(CFLAGS) qe_solver_interactive.cpp
comparators.o: comparators.cpp
	$(CC) $(CFLAGS) comparators.cpp
clean:
	rm -rf *.o main


