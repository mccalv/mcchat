/**
 University of Torvergata 
 Student Mirko Calvaresi 
 Professore Francesco Lo Presti 
 A simple client server CHAT based
 
 */ 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "list.h"
#include "echo_io.h"
#include "file_reader.h"
#include "chat_protocol.h"



#define MSG_SIZE 2000
#define MAX_CLIENTS 20
#define SERVER_PORT 7400


