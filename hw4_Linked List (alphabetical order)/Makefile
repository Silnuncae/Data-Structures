CC = gcc
PUB = /lab/theory/pub
HW = hw4
SERVER = 3.36.207.61

addr: addr.o backend.o backend.h memory.o memory.h
	${CC} -o addr addr.o backend.o memory.o

addr.o: addr.c backend.h
	${CC} -c addr.c

backend.o: backend.c backend.h memory.o memory.h
	${CC} -c backend.c

memory.o: memory.c memory.h
	${CC} -c memory.c

addr_demo: addr.o backend_demo.o memory_demo.o 
	${CC} -o addr_demo addr.o backend_demo.o memory_demo.o

backend_demo.o: backend_demo.c backend.h memory_demo.o memory.h
	${CC} -c backend_demo.c

memory_demo.o: memory_demo.c memory.h
	${CC} -c memory_demo.c

# hide backend_demo.c 
${HW}.zip: README.pdf addr.c backend.c backend.h memory.c memory.h Makefile check addr_demo
	chmod 744 addr_demo
	zip ${HW}.zip README.pdf addr.c backend.c backend.h memory.c memory.h Makefile test1.in ch_test1.out addr_demo

test: addr
	./addr < test1.in > test1.out
	diff ch_test1.out test1.out

README.pdf: README.tex
	pdflatex README.tex

pub: ${HW}.zip
	cp ${HW}.zip ${PUB}/ds_hws/${HW}.zip
	chmod 644 ${PUB}/ds_hws/${HW}.zip

sync:
#	rsync -rtv --delete . linux2.ce.hongik.ac.kr:hw/${HW}/ #timestamp preserving
	rsync -rtv . ${SERVER}:hw/${HW}/ #timestamp preserving

check: addr_demo test1.in
	./addr_demo < test1.in > ch_test1.out

clean: 
	rm addr addr_demo *.o ch_*.out *.log *.zip
