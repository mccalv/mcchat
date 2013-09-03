/**
 University of Torvergata 
 Student Mirko Calvaresi 
 Professore Francesco Lo Presti 
 A simple client server CHAT based
 
 */ 

#include "basic.h"



/** Base client code */
int main (int argc, char *argv[]){
      int port;
    int fd;
    char msg[MSG_SIZE + 1];     
    char kb_msg[MSG_SIZE + 10]; 
    
    
    
    int sockfd;
    int result;
    char hostname[MSG_SIZE];
    struct hostent *hostinfo;
    struct sockaddr_in address;
   
    fd_set  testfds, clientfds;
    
    if(argc==2 || argc==4){
        if(!strcmp("-p",argv[1])){
            if(argc==2){
                printf("USAGE: chat [-p PORT] HOSTNAME\n");
                exit(0);
            }else{
                sscanf(argv[2],"%i",&port);
                strcpy(hostname,argv[3]);
            }
        }else{
            port=SERVER_PORT;
            strcpy(hostname,argv[1]);
        }
        printf("\n*** Client program starting (enter \"quit\" to stop, /help for available command): \n");
        fflush(stdout);
        
        /* CREATE THE SOCKET  */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
        /* NAME THE SOCKET */
        hostinfo = gethostbyname(hostname);  /* look for host's name */
        address.sin_addr = *(struct in_addr *)*hostinfo -> h_addr_list;
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        
        /* Connect the socket to the server's socket */
        if(connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0){
            perror("Problem connecting....");
            exit(EXIT_FAILURE);
        }
        
        fflush(stdout);
        
        FD_ZERO(&clientfds);
        FD_SET(sockfd,&clientfds);
        FD_SET(0,&clientfds);//stdin
        
        /*  Now wait for messages from the server */
        while (1) {
            testfds=clientfds;
            select(FD_SETSIZE,&testfds,NULL,NULL,NULL);
            
            for(fd=0;fd<FD_SETSIZE;fd++){
                if(FD_ISSET(fd,&testfds)){
                    if(fd==sockfd){   /*Accept data from open socket */
                        
                        //printf("Accepting data from socked %d\n",fd);
                        //read data from open socket
                        result = read(sockfd, msg, MSG_SIZE);
                        msg[result] = '\0';  /* Terminate string with null */
                        printf("%s", msg);
                        
                        if (msg[0] == 'X') {                   
                            close(sockfd);
                            exit(EXIT_FAILURE);
                        }                             
                    }
                    else if(fd == 0){ /*CONSOLE INPUT */
                        
                        
                        fgets(kb_msg, MSG_SIZE, stdin);
                        //printf("%s\n",kb_msg);
                        if (strcmp(kb_msg, "quit\n")==0) {
                            sprintf(msg, "Client is leaving the chat[shutting down].\n");
                            
                            writen(sockfd, msg, strlen(msg));
                            close(sockfd); //close the current client
                            exit(EXIT_FAILURE); //end program
                        }
                        else if (strcmp(kb_msg, "/help\n")==0) {
                            
                              //Print the file help and guide to the client
                              printf("%s",fileContentToString("help"));
                        }
                        
                        else {
                          
                            
                            sprintf(msg, "%s", kb_msg);
                            writen(sockfd, msg, strlen(msg));
                        }                                                 
                    }          
                }
            }      
        }
    }// end client code
    
    exit(EXIT_SUCCESS);
}
