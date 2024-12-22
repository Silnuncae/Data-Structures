CC = gcc
PUB = /lab/theory/pub
HW = hw5
SERVER = 3.36.207.61

addr: addr.c backend-bst.o memory.o
	${CC} -o addr addr.c backend-bst.o memory.o

backend-bst.o: backend-bst.c backend-bst.h memory.h
	${CC} -c backend-bst.c 

memory.o: memory.c memory.h
	${CC} -c memory.c

addr_demo: addr.c backend-bst_demo.o backend-bst.h
	${CC} -o addr_demo addr.c backend-bst_demo.o

addr-bst-ex: addr-bst-ex.c backend-bst_demo.c backend-bst.h
	${CC} -o addr-bst-ex addr-bst-ex.c backend-bst_demo.c

backend-bst_demo.o: backend-bst_demo.c
	${CC} -c backend-bst_demo.c

${HW}.zip: README.pdf addr.c backend-bst.c backend-bst.h memory.c memory.h Makefile check addr_demo test1.in test2.in 
	chmod 755 addr_demo
	zip ${HW}.zip README.pdf addr.c backend-bst.c backend-bst.h memory.c memory.h Makefile test1.in ch_test1.out test2.in ch_test2.out addr_demo

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

check: addr_demo test1.in test2.in
	./addr_demo < test1.in > ch_test1.out
	./addr_demo < test2.in > ch_test2.out

clean: 
	rm addr addr_demo *.o ch_*.out *.aux *.log *.zip
