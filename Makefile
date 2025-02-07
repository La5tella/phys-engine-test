INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm

all: sim
sim: main.o display.o physics.o input.o 
	cc -g -o sim main.o display.o input.o physics.o $(LDFLAGS)

clean:
	rm -f *.o sim
main.o: src/main.c src/sim.h
	cc -g -c src/main.c -I ~/include
display.o: src/display.c src/sim.h
	cc -g -c src/display.c -I ~/include
input.o: src/input.c src/sim.h
	cc -g -c src/input.c -I ~/include
physics.o: src/physics.c src/sim.h
	cc -g -c src/physics.c -I ~/include

run:
	make all
	./sim

gitpush:
	git add src/main.c src/display.c src/input.c src/physics.c config.h src/sim.h
	git commit
	git push

debug: 
	make all
	gdb -q -tui ./sim
refresh:
	make clean
	make run
