CC = g++
CFLAGS = -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: main
test: tester
main: main.o qe_solver.o qe_solver_interactive.o comparators.o format_complex.o make_logs.o
	$(CC) main.o qe_solver.o qe_solver_interactive.o comparators.o format_complex.o make_logs.o -o main.exe

tester: tester.o qe_solver.o comparators.o qe_solver_tester.o format_complex.o
	$(CC) tester.o qe_solver.o comparators.o qe_solver_tester.o format_complex.o -o tester.exe
format_complex.o: format_complex.cpp
	$(CC) $(CFLAGS) format_complex.cpp
make_logs.o: make_logs.cpp
	$(CC) $(CFLAGS) make_logs.cpp
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


