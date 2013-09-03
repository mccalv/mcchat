/**
 University of Torvergata 
 Student Mirko Calvaresi 
 Professore Francesco Lo Presti 
 A simple client server CHAT based
 
 */ 



#ifndef LIST_SEEN
#define LIST_SEEN


struct node_t {
    int fd;
    char * room;
    char * nickname;
    struct node_t *next;
};

struct node_t *alloc_node(void);
void free_node(struct node_t *d);
void remove_node(int identifier, struct node_t **phead);
void changeRoom( struct node_t **p, const char *room);

void changeNickname(struct node_t **node,const char *nickname);

void insert_after_node(struct  node_t *new, struct node_t **pnext);
void remove_after_node(struct node_t **ppos);
void print_list(struct node_t *h, char **string, void *arg);
void insert_sorted_list(struct node_t *new, struct node_t **pp);
void insert_value(int v,const char * identifier,  struct node_t **phead);

struct node_t *getNodeById(int v, struct node_t *h);


struct node_t *getNodeByNickName(char *nickname, struct node_t *h);

#endif