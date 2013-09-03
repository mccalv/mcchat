CC = gcc
CFLAGS = -Wall -W
SRC =echo_io.o list.o file_reader.o chat_client.o chat_server.o echo_io.o chat_protocol.o
OBJ = $(SRC:.c=.o)

all: $(OBJ) 
		
	${CC} chat_client.o list.o file_reader.o echo_io.o chat_protocol.o -o chat_client
	${CC} chat_server.o list.o file_reader.o echo_io.o chat_protocol.o -o chat_server
#	${CC} chat.o -o chat


echo_io.o: echo_io.h
list.o: list.h
file_reader.o: file_reader.h
echo_io.o: echo_io.h 
chat_client.o: file_reader.h
chat_protocol.o: chat_protocol.h
clean:
	rm -f *.o chat_client chat_server 
