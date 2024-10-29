CC = g++
CFLAGS = -wall

Program2: driver.o County.o
	$(CC) $(CFLAGS) -o driver.o County.o -o Program2 

driver.o: driver.cpp List.h County.h
	$(CC) $(CFLAGS) -c driver.cpp List.h County.h

County.o: County.cpp Count.h
	$(CC) $(CFLAGS) -c County.cpp County.h

