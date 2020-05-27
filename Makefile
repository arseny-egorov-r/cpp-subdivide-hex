CC=g++
CFLAGS=-std=c++11 -O2

all: executable

executable: gmesh_reader_writer.o hexahedron_algo.o main.o 
	$(CC) $(CFLAGS) main.o hexahedron_algo.o gmesh_reader_writer.o -o executable

hexahedron_algo.o: hexahedron_algo.cc
	$(CC) $(CFLAGS) -c hexahedron_algo.cc

gmesh_reader_writer.o: gmesh_reader_writer.cc
	$(CC) $(CFLAGS) -c gmesh_reader_writer.cc

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc

clean:
	rm -rf *.o executable
