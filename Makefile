
CXXFLAGS=-g
LDFLAGS=-lyaml-cpp

INVOICE_OBJECTS=src/sysctrl.o src/state.o src/parser.o

init:
	mkdir bin

compile:
	$(CXX) -I/usr/local/include -w -c src/state/state.cpp -o src/state.o
	$(CXX) -I/usr/local/include -w -c src/parser/parser.cpp -o src/parser.o
	$(CXX) -w -c src/sysctrl.cpp -o src/sysctrl.o
	$(CXX) -o bin/test $(INVOICE_OBJECTS) $(LDFLAGS)

runPy:
	python src/srcPy/Main.py

clean:	
	rm -f src/*.o src/*~ *.o *~ *.yaml src/parser/*.o src/state/*.o
	rm -rf bin

run:
	bin/test examples/1.yaml

run-all:
	rm -rf bin
	mkdir bin
	$(CXX) -I/usr/local/include -w -c src/state/state.cpp -o src/state.o
	$(CXX) -I/usr/local/include -w -c src/parser/parser.cpp -o src/parser.o
	$(CXX) -w -c src/sysctrl.cpp -o src/sysctrl.o
	$(CXX) -o bin/test $(INVOICE_OBJECTS) $(LDFLAGS)
	bin/test examples/1.yaml
	rm -f src/*.o src/*~ *.o *~ *.yaml src/parser/*.o src/state/*.o
	rm -rf bin
