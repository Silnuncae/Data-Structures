CC = gcc
#CC = clang
PUB = /lab/theory/pub
SERVER = 3.36.207.61

addr1: addr1.c backend1.o backend1.h
	${CC} -o addr1 addr1.c backend1.o

backend1.o: backend1.c backend1.h
	${CC} -c backend1.c

addr1_demo: addr1.c backend1_demo.o
	${CC} -o addr1_demo addr1.c backend1_demo.o

backend1_demo.o: backend1_demo.c backend1.h
	${CC} -c backend1_demo.c

hw1.zip: README.pdf addr1.c backend1.c backend1.h Makefile check addr1_demo
	chmod 744 addr1_demo
	zip hw1.zip README.pdf addr1.c backend1.c backend1.h Makefile addr1_demo test1.in ch_test1.out

README.pdf: README.tex
	pdflatex README.tex

pub: hw1.zip
#	rsync hw1.zip linux2.ce.hongik.ac.kr:../pub/ds_hws/hw1.zip
	cp hw1.zip ${PUB}/ds_hws/hw1.zip
	chmod 644 ${PUB}/ds_hws/hw1.zip

sync:
#	rsync -rtv . linux2.ce.hongik.ac.kr:hw/hw1/ #timestamp preserving
	rsync -rtv . ${SERVER}:hw/hw1/ #timestamp preserving

test: addr1 test1.in
	./addr1 < test1.in > test1.out
	diff ch_test1.out test1.out

check: addr1_demo test1.in
	./addr1_demo < test1.in > ch_test1.out

clean:
	rm addr1 addr1_demo *.o *.out *.aux *.log *.zip
