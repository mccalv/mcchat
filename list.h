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