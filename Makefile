
CXXFLAGS=-g
LDFLAGS=-lyaml-cpp

INVOICE_OBJECTS=examples/src-cpp/invoiceYaml.o examples/src-cpp/invoice.o

init:
	mkdir bin

compile:
	g++ -c examples/src-cpp/invoice.C -o examples/src-cpp/invoice.o
	g++ -c examples/src-cpp/invoiceYaml.C -o examples/src-cpp/invoiceYaml.o
	g++ -o examples/bin/test $(INVOICE_OBJECTS) $(LDFLAGS)

clean:
	rm -f src/*.o src/*~ src/sisctrl *.o *~ examples/src-cpp/*.o *.o test *.yaml 
	rm -f examples/bin/test
	rm -rf bin

run:
	./examples/bin/test examples/invoices.yaml

run-all:
	mkdir bin
	g++ -c examples/src-cpp/invoice.C -o examples/src-cpp/invoice.o
	g++ -c examples/src-cpp/invoiceYaml.C -o examples/src-cpp/invoiceYaml.o
	g++ -o examples/bin/test $(INVOICE_OBJECTS) $(LDFLAGS)
	./examples/bin/test examples/invoices.yaml
	rm -f src/*.o src/*~ src/sisctrl *.o *~ examples/src-cpp/*.o *.o test *.yaml 
	rm -f examples/bin/test
	rm -rf bin