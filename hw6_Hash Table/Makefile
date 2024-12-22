CC = gcc
PUB = /lab/theory/pub
HW = hw6
SERVER = 3.36.207.61

addr: addr.c backend-hash.o backend-hash.h
	${CC} -o addr addr.c backend-hash.o

backend-hash.o: backend-hash.c
	${CC} -c backend-hash.c

addr_demo: addr.c backend-hash_demo.o backend-hash.h
	${CC} -o addr_demo addr.c backend-hash_demo.o

backend-hash_demo.o: backend-hash_demo.c
	${CC} -c backend-hash_demo.c

${HW}.zip: README.pdf addr.c backend-hash.c backend-hash.h Makefile check addr_demo
	chmod 755 addr_demo
	zip ${HW}.zip README.pdf addr.c backend-hash.c backend-hash.h Makefile test1.in ch_test1.out addr_demo

pub: ${HW}.zip
	cp ${HW}.zip ${PUB}/ds_hws/${HW}.zip
	chmod 644 ${PUB}/ds_hws/${HW}.zip

sync:
	rsync -rtv --delete . ${SERVER}:hw/${HW}/ #timestamp preservingsync:

test1: addr
	./addr < test1.in > test1.out
	diff ch_test1.out test1.out

test2: addr
	./addr < test2.in > test2.out
	diff ch_test2.out test2.out

README.pdf: README.tex
	pdflatex README.tex

check: addr_demo test1.in
	./addr_demo < test1.in > ch_test1.out
	./addr_demo < test2.in > ch_test2.out

clean: 
	rm addr addr_demo *.o ch_*.out *.aux *.log *.zip
