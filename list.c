/**
 University of Torvergata 
 Student Mirko Calvaresi 
 Professore Francesco Lo Presti 
 A simple client server CHAT based
 
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



struct node_t {
    int fd;
    char * room;
    char * nickname;
 
    struct node_t *next;
};


struct node_t *alloc_node(void)
{
    struct node_t *p;
    p = malloc(sizeof(struct node_t));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

void free_node(struct node_t *d)
{   
    free(d);
}

void insert_after_node(struct node_t *new, struct node_t **pnext)
{
    new->next = *pnext;
    *pnext = new;
}

void remove_after_node(struct node_t **ppos)
{
    struct node_t *d = *ppos;
     *ppos = d->next;
    
}

void changeRoom( struct node_t **node,const char *room)
{ 
    
    strcpy(
           (*node)->room,room);;
    
    
}


void changeNickname(struct node_t **node,const char *nickname){
    //struct node_t *n = *node;
    strcpy(
    (*node)->nickname,nickname);
}



void remove_node(int fd, struct node_t **pp){
  struct node_t *p ;
    for (p = *pp; p != NULL; pp = &p->next, p = p->next)
        if (p->fd ==fd ) {
            remove_after_node(pp);
            return;
        }
        
    
}

void print_list(struct node_t *h, char **string, void *arg)
{
    *string = malloc(2048 *sizeof(char));    
if (string==NULL){
        fprintf(stderr, "Error trying to print node list \n");
        exit(EXIT_FAILURE);
        }
    char *room = arg;
    strcat (*string, " ******** HOST CONNECTED ********\n");
            
   
    struct node_t *p;
    for (p = h; p != NULL; p = p->next){
        
        if(room==NULL){
            char temp[80];
            sprintf(temp,"Client[%d] [%s] [room]:%s\n", p->fd,p->nickname, p->room);
            strcat(*string,temp);

       
            
        }else{
            if(strcmp(room, p->room)==0){
                char temp[80];
                sprintf(temp,"Client[%d] [%s] [room]:%s\n", p->fd,p->nickname, p->room);
                strcat(*string,temp);
                
            }
        
        }
    }
     
   // strcat (*string , "************************");
}

void insert_sorted_list(struct node_t *new, struct node_t **pp)
{
    struct node_t *p;
    for (p = *pp; p != NULL; pp = &p->next, p = p->next)
        if (p->fd > new->fd) {
            insert_after_node(new, pp);
            return;
        }
    insert_after_node(new, pp);
}

void insert_value(int v, const char *nickname, struct node_t **phead)
{
    struct node_t *new;
    
    new = alloc_node();
    new->fd = v;
    new->room = "PUBLIC";
    new->nickname =malloc (strlen(nickname));
    
    strcpy(new->nickname,nickname);
    
    
    insert_sorted_list(new, phead);
}
struct node_t *getNodeById(int v, struct node_t *h){
    
    struct node_t *p;
    for (p = h; p != NULL; p = p->next){
        if(p->fd ==v){
            return p;
        }
    }
    return NULL;
    
}


struct node_t *getNodeByNickName(char *nickname, struct node_t *h){

    struct node_t *p;
    for (p = h; p != NULL; p = p->next){
    
        if(strcmp(p->nickname,nickname)==0){
            return p;
        }
    }
    return NULL;

}



//Use for testing
/*
int main(){
    struct node_t *HEAD = NULL;
    insert_value(1,"pippo1",20222, &HEAD);
    insert_value(2,"pippo2",20222, &HEAD);
    insert_value(3,"pippo3",20222, &HEAD);
    insert_value(4,"pippo4",20222, &HEAD);
    insert_value(5,"pippo5",20222, &HEAD);
    remove_node(5,&HEAD);
    //print_list(HEAD);

    remove_node(2,&HEAD);
    changeRoom(1,&HEAD, "pippo");
    char *prova;
    print_list(HEAD,&prova);
    printf ("Stampa %s\n",prova);
    
    struct node_t *pippo1 = getNodeById(1,HEAD);
    changeNickname(&pippo1, "ciao");
    print_list(HEAD,&prova);
    printf ("Stampa %s\n",prova);
    
    return 0;
    
}
*/

