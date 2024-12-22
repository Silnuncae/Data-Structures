CC = gcc
PUB = /lab/theory/pub
HW = hw8
SERVER = 3.36.207.61

ladders: ladders.c backend.o backend.h
	${CC} -g -o ladders ladders.c backend.o

backend.o: backend.c
	${CC} -g -c backend.c

ladders_demo: ladders.c backend_demo.o backend.h
	${CC} -g -o ladders_demo ladders.c backend_demo.o

backend_demo.o: backend_demo.c
	${CC} -g -c backend_demo.c


${HW}.zip: README.pdf ladders.c backend.c backend.h Makefile words.dat
	zip ${HW}.zip README.pdf ladders.c backend.c backend.h Makefile words.dat

README.pdf: README.tex
	pdflatex README.tex

sync:
	rsync -rtv --delete . ${SERVER}:hw/${HW}/ #timestamp preserving

pub: ${HW}.zip
	cp ${HW}.zip ${PUB}/ds_hws/${HW}.zip
	chmod 644 ${PUB}/ds_hws/${HW}.zip

clean:
	rm ladders ladders_demo *.o *.aux *.log *.zip
