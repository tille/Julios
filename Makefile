
CXXFLAGS=-g
LDFLAGS=-lyaml-cpp

INVOICE_OBJECTS=src/sysctrl.o src/state.o

init:
	mkdir bin

compile:
	$(CXX) -w -c src/sysctrl.cpp -o src/sysctrl.o
	$(CXX) -I/usr/local/include -w -c src/state.cpp -o src/state.o
	$(CXX) -o bin/test $(INVOICE_OBJECTS) $(LDFLAGS)

clean:
	rm -f src/*.o src/*~ *.o *~ *.yaml 
	rm -rf bin

run:
	bin/test

run-all:
	rm -rf bin
	mkdir bin
	$(CXX) -w -c src/sysctrl.cpp -o src/sysctrl.o
	$(CXX) -o bin/test $(INVOICE_OBJECTS) $(LDFLAGS)
	bin/test
	rm -f src/*.o src/*~ *.o *~ *.yaml 
	rm -rf bin
