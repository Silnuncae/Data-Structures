CC = gcc
PUB = /lab/theory/pub
SERVER = 3.36.207.61

addr2: addr2.c backend2.o backend2.h
	${CC} -o addr2 addr2.c backend2.o

backend2.o: backend2.c backend2.h
	${CC} -c backend2.c

backend2_demo.o: backend2_demo.c backend2.h
	${CC} -c backend2_demo.c

hw2.zip: README.pdf addr2.c backend2.c backend2.h addr2_demo Makefile check
	chmod 744 addr2_demo
	zip hw2.zip README.pdf addr2_demo addr2.c backend2.c backend2.h Makefile test1.in ch_test1.out

addr2_demo: addr2_demo.c backend2_demo.o
	${CC} -o addr2_demo addr2_demo.c backend2_demo.o

README.pdf: README.tex
	pdflatex README.tex

pub: hw2.zip
#	rsync hw2.zip linux2.ce.hongik.ac.kr:../pub/ds_hws/hw2.zip
	cp hw2.zip ${PUB}/ds_hws/hw2.zip
	chmod 644 ${PUB}/ds_hws/hw2.zip

sync:
#	rsync -rtv . linux2.ce.hongik.ac.kr:hw/hw2/ #timestamp preserving
	rsync -rtv . ${SERVER}:hw/hw2/ #timestamp preserving

test: addr2 test1.in
	./addr2 < test1.in > test1.out
	diff ch_test1.out test1.out

check: addr2_demo test1.in
	./addr2_demo < test1.in > ch_test1.out

clean:
	rm addr2 addr2_demo *.o *.out *.aux *.log *.zip
