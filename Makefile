
CXXFLAGS=-g
LDFLAGS=-lyaml-cpp

INVOICE_OBJECTS=src/invoiceYaml.o src/invoice.o

init:
	mkdir bin

compile:
	$(CXX) -c src/invoice.C -o src/invoice.o
	$(CXX) -c src/invoiceYaml.C -o src/invoiceYaml.o
	$(CXX) -o bin/test $(INVOICE_OBJECTS) $(LDFLAGS)

clean:
	rm -f src/*.o src/*~ *.o *~ *.yaml 
	rm -rf bin

run:
	bin/test invoices.yaml

run-all:
	mkdir bin
	$(CXX) -c src/invoice.C -o src/invoice.o
	$(CXX) -c src/invoiceYaml.C -o src/invoiceYaml.o
	$(CXX) -o bin/test $(INVOICE_OBJECTS) $(LDFLAGS)
	bin/test examples/invoices.yaml
	rm -f src/*.o src/*~ *.o *~ *.yaml 
	rm -rf bin
