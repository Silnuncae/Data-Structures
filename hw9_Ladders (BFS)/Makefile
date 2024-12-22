CC = gcc
PUB = /lab/theory/pub
HW = hw9
SERVER = 3.36.207.61
#include ../vars.mk

ladders: ladders.c backend.o backend.h path.o path.h
	${CC} -g -o ladders ladders.c backend.o path.o

backend.o: backend.c backend.h
	${CC} -g -c backend.c

path.o: path.c backend.h
	${CC} -g -c path.c

ladders_demo: ladders.c backend.o backend.h path_demo.o path.h
	${CC} -g -o ladders_demo ladders.c backend.o path_demo.o

path_demo.o: path_demo.c backend.h
	${CC} -g -c path_demo.c


${HW}.zip: README.pdf ladders.c backend.c backend.h path.c path.h Makefile words.dat ladders_demo test.in check
	zip ${HW}.zip README.pdf ladders.c backend.c backend.h path.c path.h Makefile words.dat ladders_demo test.in ch_test.out

pub: ${HW}.zip 
	cp ${HW}.zip ${PUB}/ds_hws/${HW}.zip
	chmod 644 ${PUB}/ds_hws/${HW}.zip

sync:
	rsync -rtv --delete . ${SERVER}:hw/${HW}/ #timestamp preserving

README.pdf: README.tex
	pdflatex README.tex

check: ladders_demo test.in 
	./ladders_demo < test.in > ch_test.out

test: ladders
	./ladders < test.in > test.out
	diff ch_test.out test.out

clean: 
	rm ladders ladders_demo *.o ch_*.out *.aux *.log *.zip

