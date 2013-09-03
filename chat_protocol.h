/**
 University of Torvergata 
 Student Mirko Calvaresi 
 Professore Francesco Lo Presti 
 A simple client server CHAT based
 
 */ 

#ifndef COMMAND_SEEN
#define COMMAND_SEEN





#include "list.h"
#include "echo_io.h"


struct command_t {
    char command[10];
    char value[10];
    
    
};


struct command_t  *parseCommand(char *msg);


void notifyToAllRoomMembers(struct node_t *client, struct node_t   *head,  char *message);



void sendPrivateMsg(struct node_t *head, struct node_t *from, char *nickname,const char *message);


//*Return the list of the chat members to the node asking the command
void printchatMembers(struct node_t *HEAD, struct node_t *node, char *room);



int checkNick(struct node_t *client, const char *nickname);


int checkRoom(struct node_t *client, const char *room);
#endif