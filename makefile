SIMOBJS = printJobType.o printerType.o printerListType.o printJobQueueType.o main.o 
SIMHDRS = printJobType.h printerType.h printerListType.h printJobQueueType.h 

make: $(SIMOBJS)
	g++ -Wall -g *.o -lm -o make
$(SIMOBJS): $(SIMHDRS) makefile
main.o: main.cpp 
	g++ -Wall -c -g main.cpp

printJobType.o: printJobType.cpp printJobType.h
	g++ -Wall -c -g printJobType.cpp 

printerType.o: printerType.cpp printerType.h
	g++ -Wall -c -g printerType.cpp

printerListType.o: printerListType.cpp printerListType.h
	g++ -Wall -c -g printerListType.cpp

printJobQueueType.o: printJobQueueType.cpp printJobQueueType.h
	g++ -Wall -c -g printJobQueueType.cpp

clean:
	rm *.o make 
