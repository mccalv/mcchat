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
#include "basic.h"

/**
 Parses a command coming from a client and return a command_t struct
 The string representing the command should be provided in the following format 
 [/command] '[value]'
 The value in particular must be delimited by ' or "" in order to allow spaces and multiple words (for example for private message)
 */
struct command_t  *parseCommand(char *msg){
    
    
    
    int  l  = strlen(msg);
    
    int i =0;
    int cs=-1;//posizione of '/comman
    
    int vs=-1;//posizione of 'value'
    int ve = -1; //posizione of 'endvalue
    
    for (;;){
        
        // printf ("%c %d %d\n", *msg, i, l);
        if ((*msg) =='/'){
            //printf("Starting a command value\n");
            cs =i;
        }
        if(
           
           
           (cs>=0 &&vs==-1 && (*msg=='"'||*msg=='\n'))
           
           ){
            vs =i;
        }
        
        if(
           (vs>0 &&ve==-1&&i>vs && (*msg=='"'))
           //|| *msg=='\0'
           ){
            ve =i;
        }
        
         // printf("Posizione dei commandi cs vs ve l %d %d %d %d [%s]\n ", cs,vs,ve,l,  msg);
        
        if (i==l)break;
        msg++;
        i++;
        
    }
    
    struct command_t  *c= malloc (sizeof(struct command_t));
    
    c->command[0] = '\0';
    c->command[0] = '\0';
    
    
    msg = msg -l;
    if (vs==-1|| ve==-1){
        vs = l;
    }
    if (cs==-1){
        
        return c;
    }
    
    //printf("Posizione dei commandi cs vs ve l %d %d %d %d [%s]\n ", cs,vs,ve,l,  msg);
    
    int k;
    msg = msg +cs+1;
    int command_l=0;int value_l = 0;
    
    int end_command = (vs==l)?l-2:(vs-cs-2);
    for (k=0;k<end_command;k++){
        c->command[k] = *msg;
        //printf(" %d %c\n", k,*msg);
        
        command_l++;
        
        msg++;
        
    }
    c->command[command_l++]='\0';
    msg++;
    msg++;
    for (k=0;k<(ve-vs-1);k++){
        
        c->value[k] = *msg;
        
        value_l++;
        //}
        msg++;
        
    }
    c->value[value_l++]='\0';
    
    
    msg = msg -l;
    *msg  = '\0';
    *msg = '\n';
    
   
   
    return c;
    
} 

/**
 A simle wrapper to handle eventual errors
 */ 
void writeToSocket(int sockd,const char *message){
    
    int n =  writen(sockd,message,strlen(message));
    if (n==-1){
        fprintf(stderr, "Error writing message %s to client \n", message);
        exit(EXIT_FAILURE);
    }
    
}
void notifyToAllRoomMembers(struct node_t *client, struct node_t   *head, char *message){
    
    
    
    struct node_t *p;
    for (p = head; p != NULL; p = p->next){
        if (client !=NULL){
        //Notify a msg only if the room member is the same 
        if (strcmp(client->room, p->room)==0)
        {
            //DO NOT NOTIFY TO THE ORIGINAL CLIENT
            if(client->fd!=p->fd){
                writeToSocket(p->fd,message);
            }
            }
        }else{
            writeToSocket(p->fd,message);

        }
    }
    
}

/**
 Populates the list of the chat members and write it to the chat
 */
void printchatMembers(struct node_t *head, struct node_t *client, char *room){
    char *message;

    if (strcmp(room,"ALL")==0){
               print_list(head,&message, NULL);
        writeToSocket(client->fd,message);
    }
    else{
        
        
        
        
        print_list(head,&message, room);
        writeToSocket(client->fd,message);
      
    }
    
    
}



void sendPrivateMsg(struct node_t *head, struct node_t *from, char *nickname,  const char *message){
    
    
    
    char private_msg[100];
    sprintf(private_msg, "[%s (PRIVATE)]>%s\n",from->nickname, message); 
    
    
    struct node_t *to = getNodeByNickName(nickname, head);
    
    if (to!=NULL){
        
        writeToSocket(to->fd,private_msg);    
    }else{
        
        
        writeToSocket(from->fd, "[SYSTEM]>Command invalid or nickname not present! \n");   
        
        
    }
    
    
    
    
    
}

/**
 A token is valid is DOES NOT have whitespaces in it
 */
int isValidToken(const char *string){
    int isValid = 1;
    int i=0;
    int l = strlen(string);
    for(;;){
        if(*string==' '){
            isValid = 0;
            return isValid;
        }
        string++;
        i++;
        if (i==l)break;
    }
        
    
    return isValid;
    };



int checkNick(struct node_t *client, const char *nickname){    
    
    int isVT = isValidToken(nickname);
    char message[100];
        if(!isVT){
               sprintf(message, "[SYSTEM]>Space are not allowed in nickname ['%s']\n", nickname); 
         }else{
             
    
             sprintf(message, "[SYSTEM]>Your new nick is %s\n", nickname); 
             
   
    }
     writeToSocket(client->fd, message);
    return isVT;
}


int checkRoom(struct node_t *client, const char *room){
    int isVT = isValidToken(room);
    if(!    isVT){
            writeToSocket(client->fd, "[SYSTEM]>Spaces are not allowes in room name \n");
        }else{
            writeToSocket(client->fd, "[SYSTEM]>Your room has changed\n");
    }
    
    return isVT;
}




