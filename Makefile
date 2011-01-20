# Explicit rule
all: server client

server: server.o server_operations.o shared.o
	g++ -g -Wall -o server server_operations.o shared.o server.o -lcrypto

client: client.o client_operations.o shared.o
	g++ -g -Wall -o client client_operations.o shared.o client.o -lcrypto

clean:
	rm *.o client server

server.o: server.cc
client.o: client.cc
shared.o: shared.cc shared.h
server_operations.o: server_operations.cc server_operations.h
client_operations.o: client_operations.cc client_operations.h
