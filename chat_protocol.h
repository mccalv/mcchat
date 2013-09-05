/*
 * Copyright 2009-2013 Mirko Calvaresi.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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