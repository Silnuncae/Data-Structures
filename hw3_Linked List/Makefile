CC = gcc
PUB = /lab/theory/pub
SERVER = 3.36.207.61

addr: addr.o backend.o memory.o
	${CC} -o addr addr.o backend.o memory.o

addr.o: addr.c backend.h
	${CC} -c addr.c

backend.o: backend.c backend.h memory.h memory.o # instead of memory.c
	${CC} -c backend.c

memory.o: # memory.c memory.h
	${CC} -c memory.c

addr_demo: addr.o backend_demo.o memory.o
	${CC} -o addr_demo addr.o backend_demo.o memory.o

backend_demo.o: backend_demo.c
	${CC} -c backend_demo.c

# hide backend_demo.c and memory.c but provide memory.o
hw3.zip: README.pdf addr.c backend.c backend.h memory.o memory.h Makefile check addr_demo
	chmod 744 addr_demo
	zip hw3.zip README.pdf addr.c backend.c backend.h memory.h memory.o Makefile test1.in ch_test1.out addr_demo

test: addr
	./addr < test1.in > test1.out
	diff ch_test1.out test1.out

README.pdf: README.tex
	pdflatex README.tex

pub: hw3.zip
	cp hw3.zip ${PUB}/ds_hws/hw3.zip
	chmod 644 ${PUB}/ds_hws/hw3.zip

sync:
#	rsync -rtv --delete . linux2.ce.hongik.ac.kr:hw/hw3/ #timestamp preserving
	rsync -rtv . ${SERVER}:hw/hw3/ #timestamp preserving

check: addr_demo test1.in
	./addr_demo < test1.in > ch_test1.out

clean:
	rm addr addr_demo *.o ch_*.out *.log *.zip
