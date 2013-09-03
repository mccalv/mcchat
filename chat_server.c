/**
 University of Torvergata 
 Student Mirko Calvaresi 
 Professore Francesco Lo Presti 
 A simple client server CHAT based
 
 */ 
#include "basic.h"

/*
 typedef void Sigfunc(int);
 
 Sigfunc* signal(int signum, Sigfunc *handler);
 
 void sig_chld_handler(int signum);
 */

void clientLeave(int fd, fd_set *readfds, char fd_array[], int *num_clients, struct node_t **head){
    int i;
    
    close(fd);
    FD_CLR(fd, readfds); //clear the leaving client from the set
    for (i = 0; i < (*num_clients) - 1; i++)
        if (fd_array[i] == fd)
            break;          
    for (; i < (*num_clients) - 1; i++)
        (fd_array[i]) = (fd_array[i + 1]);
    (*num_clients)--;
        remove_node(fd ,head );
   // char msg[80];
   // sprintf(msg, Client 
   // notifyToAllRoomMembers(NULL, *head, "A client left the chat");
}




int main(int argc, char *argv[]){
    int i=0;
    
    
    
    
    int port;
    
    int num_clients = 0;
    int server_sockfd, client_sockfd;
    struct sockaddr_in server_address;
    int addresslen = sizeof(struct sockaddr_in);
    int fd;
    char fd_array[MAX_CLIENTS];
    fd_set readfds, testfds;
    char msg[MSG_SIZE + 1];     
    char kb_msg[MSG_SIZE + 10]; 
    int result;
    
    //INIZIALIZE A LIST OF NODES 
    struct node_t *HEAD = NULL;
    
    
    
    if(argc==1 || argc == 3){
        if(argc==3){
            if(!strcmp("-p",argv[1])){
                sscanf(argv[2],"%i",&port);
            }else{
                printf("Invalid parameter.\nUsage: ./%s [-p PORT] \n", argv[0]);
                exit(0);
            }
        }else port=SERVER_PORT;
        
        printf("\n*** Server program starting on port %d (enter \"quit\" to stop): \n",port);
        fflush(stdout);
        
        /* CREATE A SOCKET FOR THE SERVER  */
        server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(port);
        bind(server_sockfd, (struct sockaddr *)&server_address, addresslen);
        
        /* Create a connection queue and initialize a file descriptor set */
        listen(server_sockfd, 1);
        FD_ZERO(&readfds);
        FD_SET(server_sockfd, &readfds);
        FD_SET(0, &readfds);  /* Add keyboard to file descriptor set */
        
     
        
        /*  Now wait for clients and requests */
        while (1) {
            testfds = readfds;
            
            /*            
             
             sigaddset(&blockset, SIGINT);
             sigprocmask(SIG_BLOCK, &blockset, NULL);
             
             sa.sa_handler = sig_chld_handler;                   sa.sa_flags = 0;
             sigemptyset(&sa.sa_mask);
             
             sigaction(SIGTERM, &sa, NULL);	sigaddset(&blockset, SIGTERM);
             sigaction(SIGINT, &sa, NULL);	sigaddset(&blockset, SIGINT);
             sigaction(SIGHUP, &sa, NULL);	sigaddset(&blockset, SIGHUP);
             sigaction(SIGALRM, &sa, NULL);	sigaddset(&blockset, SIGALRM);
             sigaction(SIGSTOP, &sa, NULL);	sigaddset(&blockset, SIGSTOP);
             
             sigemptyset(&emptyset);
             
             */
            
            struct timeval tv;
            /* Wait up to 10 seconds. */
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            
            int select_v =  select(FD_SETSIZE, &testfds, NULL, NULL, &tv);
            
            /* FD_ISSET get the descriptor in activity */
            for (fd = 0; fd < FD_SETSIZE; fd++) {
                if (FD_ISSET(fd, &testfds)) {
                    
                    
                    if (fd == server_sockfd) { /* a new client connection is accepted */
                        client_sockfd = accept(server_sockfd, NULL, NULL);
                        /*printf("client_sockfd: %d\n",client_sockfd);*/
                        
                        if(client_sockfd<0){
                            perror("Error accepting a new client\n");
                            exit(EXIT_FAILURE);
                        }
                        
                        
                        
                        
                        if (num_clients < MAX_CLIENTS) {
                            FD_SET(client_sockfd, &readfds);
                            fd_array[num_clients]=client_sockfd;
                            
                            
                            
                            /*Populate the list with the incoming client */
                            char temp[10];
                            sprintf(temp, "host%d", client_sockfd);
                          
                            insert_value(client_sockfd, temp, &HEAD);
                            
                            
                            /*Client ID*/
                            
                            
                            num_clients++;
                            printf("Client %d joined\n",num_clients);
                            notifyToAllRoomMembers(getNodeById(client_sockfd,HEAD), HEAD, "[SYSTEM]>A new client has joined the chat\n");
                            fflush(stdout);
                            
                           // sprintf(msg,"M%2d",client_sockfd);
                            /*write 2 byte clientID */
                            //send(client_sockfd,msg,strlen(msg),0);
                        }
                        else {
                            sprintf(msg, "XSorry, too many clients.  Try again later.\n");
                            write(client_sockfd, msg, strlen(msg));
                            close(client_sockfd);
                        }
                    }
                    else if (fd == 0)  {  /* Process keyboard activity */                 
                        fgets(kb_msg, MSG_SIZE , stdin);
                        //printf("%s\n",kb_msg);
                        if (strcmp(kb_msg, "quit\n")==0) {
                            sprintf(msg, "XServer is shutting down.\n");
                            for (i = 0; i < num_clients ; i++) {
                                write(fd_array[i], msg, strlen(msg));
                                close(fd_array[i]);
                            }
                            close(server_sockfd);
                            exit(0);
                        }

                        else {
                            sprintf(msg, "[Server]>%s", kb_msg);
                            for (i = 0; i < num_clients ; i++)
                                writen(fd_array[i], msg, strlen(msg));
                        }
                    }
                    else if(fd) { 
                        
                        if(select_v==0){
                            printf("client %d is idle\n", fd);
                            
                            
                        }
                        if(select_v==-1){
                            printf("client %d disonnect\n", fd);
                            
                            
                        }
                        
                        /*Process Client specific activity*/
                        //printf("server - read\n");
                        //read data from open so_acket
                        result = readline(fd, msg, MSG_SIZE);
                        
                        
                        if(result==-1) perror("read()");
                        
                        
                        if (result ==0){
                            clientLeave(fd,&readfds, fd_array,&num_clients, &HEAD);
                        }
                        else if(result>0){
                            /*read 2 bytes client id*/
                            sprintf(kb_msg,"[Client%2d]::",fd);
                            
                            
                            
                            
                            
                            /** CHECK CLIENT SPECIFIC COMMAND */ 
                            struct node_t *currentClient;
                            currentClient= getNodeById(fd, HEAD);
                            struct command_t *com = parseCommand(msg);
                            
                            //Un comment to print the current command and value received 
                            //printf("Command and value [%s][%s]\n",com->command, com->value); 
                            
                            int isAnyCommand = 0;
                            
                            
                            
                            //*** CHECK CLIENT SPECIFIC COMMAND */
                            msg[result]='\0';
                            
                            
                            if(strcmp(com->command, "nickname")==0){
                                /*Check if the nick is valid */                                                          
                                if(checkNick(currentClient,com->value)){
                                    currentClient->nickname=com->value;
                                    char chnick[80];
                                    sprintf(chnick, "[SYSTEM]>Client %d new nickname is '%s'\n",currentClient->fd,currentClient->nickname);
                                    notifyToAllRoomMembers(currentClient, HEAD, chnick);
                                    

                                }
                                isAnyCommand  = 1;
                                continue;
                            };
                            
                            
                            
                            if(strcmp(com->command, "list")==0){
                                printchatMembers(HEAD, currentClient, com->value);
                                isAnyCommand  = 1;
                                continue;
                                
                            };
                            
                            if(strcmp(com->command, "room")==0){
                                if(checkRoom(currentClient,com->value)){
                                    currentClient->room = com->value;
                                    char chroom[80];
                                    sprintf(chroom, "[SYSTEM]>'%s' has entered the room '%s'\n",currentClient->nickname,currentClient->room);
                                    notifyToAllRoomMembers(currentClient, HEAD, chroom);
                                }
                                isAnyCommand  = 1;
                                continue;
                                
                            }
                            
                            
                            if(strlen(com->command)>0&&!isAnyCommand){
                                sendPrivateMsg(HEAD,currentClient, com->command, com->value); 
                                continue;
                            }
                            
                            
                            
                            
                            /*concatinate the client id with the client's message*/
                            char messageToBeSent[256];
                            
                            sprintf (messageToBeSent,"[%s]>%s",currentClient->nickname, msg );
                            //strcat(kb_msg,msg+1);                                        
                            
                            /*print to other clients*/
                            
                            notifyToAllRoomMembers(currentClient,HEAD,messageToBeSent);
                                                     
                            /*print to server*/
                            printf("%s",messageToBeSent);
                            
                            /*Exit Client*/
                            if(msg[0] == 'X'){
                                clientLeave(fd,&readfds, fd_array,&num_clients, &HEAD);
                            }   
                        }                                   
                    }                  
                    else {  /* A client is leaving */
                        clientLeave(fd,&readfds, fd_array,&num_clients, &HEAD);
                    }//if
                }//if
            }//for
        }//while
    }//end 
    exit(EXIT_SUCCESS);
    
}

/*
 Sigfunc *signal(int signum, Sigfunc *func)
 {
 struct sigaction	act, oact;
 
 act.sa_handler = func;
 sigemptyset(&act.sa_mask);	
 act.sa_flags = 0;
 if (signum != SIGALRM) 
 act.sa_flags |= SA_RESTART;  
 if (sigaction(signum, &act, &oact) < 0)
 return(SIG_ERR);
 return(oact.sa_handler);
 }
 
 
 void sig_chld_handler(int signum)
 {  
 got_SIGCHLD = signum;
 printf("Reveived signal %d\n", signum);
 exit(EXIT_SUCCESS);
 int	status;
 
 return;
 }*/
