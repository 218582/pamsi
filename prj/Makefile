G = g++
GFLAGS = -Wall -pedantic -g -std=c++11 -Iinc
ALLFILES = obj/tabl.o obj/run.o src/main.cpp inc/tabl.hh inc/main.hh inc/run.hh inc/stoper.hh \
	obj/stoper.o inc/except.hh obj/except.o inc/lista.hh obj/lista.o inc/stos.hh obj/stos.o \
	inc/kolejka.hh obj/kolejka.o inc/hash.hh obj/hash.o inc/asoc.hh obj/asoc.o inc/tree.hh obj/tree.o inc/graph.hh obj/graph.o

tabl: obj $(ALLFILES)
	$(G) $(GFLAGS) ./obj/tabl.o ./obj/run.o ./obj/stoper.o ./obj/except.o obj/lista.o obj/stos.o obj/kolejka.o obj/hash.o obj/asoc.o obj/tree.o obj/graph.o ./src/main.cpp -o tabl

obj:
	mkdir obj

obj/except.o: src/except.cpp inc/except.hh
	$(G) $(GFLAGS) -c ./src/except.cpp -o ./obj/except.o
	
obj/run.o: src/run.cpp inc/run.hh src/tabl.cpp inc/tabl.hh src/lista.cpp inc/lista.hh src/stos.cpp inc/stos.hh src/kolejka.cpp inc/kolejka.hh
	$(G) $(GFLAGS) -c ./src/run.cpp -o ./obj/run.o
	
obj/tabl.o: src/tabl.cpp inc/tabl.hh inc/main.hh inc/except.hh
	$(G) $(GFLAGS) -c ./src/tabl.cpp -o ./obj/tabl.o
	
obj/stoper.o: src/stoper.cpp inc/stoper.hh
	$(G) $(GFLAGS) -c ./src/stoper.cpp -o ./obj/stoper.o
	
obj/lista.o: src/lista.cpp inc/lista.hh inc/tabl.hh inc/main.hh inc/except.hh
	$(G) $(GFLAGS) -c ./src/lista.cpp -o ./obj/lista.o
	
obj/stos.o: src/stos.cpp inc/stos.hh inc/tabl.hh inc/except.hh
	$(G) $(GFLAGS) -c ./src/stos.cpp -o ./obj/stos.o

obj/kolejka.o: src/kolejka.cpp inc/kolejka.hh inc/tabl.hh inc/except.hh
	$(G) $(GFLAGS) -c ./src/kolejka.cpp -o ./obj/kolejka.o
	
obj/hash.o: src/hash.cpp inc/hash.hh inc/tabl.hh inc/except.hh
	$(G) $(GFLAGS) -c ./src/hash.cpp -o ./obj/hash.o
	
obj/asoc.o: src/asoc.cpp inc/asoc.hh inc/hash.hh inc/tabl.hh inc/except.hh
	$(G) $(GFLAGS) -c ./src/asoc.cpp -o ./obj/asoc.o
	
obj/tree.o: src/tree.cpp inc/tree.hh inc/tabl.hh inc/except.hh
	$(G) $(GFLAGS) -c ./src/tree.cpp -o ./obj/tree.o
	
obj/graph.o: src/graph.cpp inc/graph.hh inc/tabl.hh inc/lista.hh inc/stos.hh inc/kolejka.hh
	$(G) $(GFLAGS) -c ./src/graph.cpp -o ./obj/graph.o

	
clean:
	rm -fr ./obj/*.o tabl
	
start:
	./tabl
	
remake:
	rm -fr ./obj/*.o tabl
	make
