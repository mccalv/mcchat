/**
 University of Torvergata 
 Student Mirko Calvaresi 
 Professore Francesco Lo Presti 
 A simple client server CHAT based
 
 */ 
#include "basic.h"






char  *parseInt(int input)


{
    static char parsedString[5];
    sprintf(parsedString, "%d", input);
    return parsedString;
    
};


char *fileContentToString(char *location){
    
    FILE *fp;
    static char string [128];
    
    fp = fopen(location,"r");
    if (fp==NULL){
        fprintf(stderr,"Impossible to open file from location '%s'\n",location);
        exit(EXIT_FAILURE);
        
    }
    
    while (fgets(string, sizeof(string), fp)!=NULL){
      puts(string);
      //reading string;
    }
    fclose(fp); /* close the file */
 
    return string;
}
/*
int main(){
    
    char pippo[5];
    sprintf(pippo, "%d", 12);
    printf ("Number %s \n",pippo);
    printf ("%s",fileContentToString("help"));
    char command [10];
    char value [10];
    
    char *tokenstring = "/command value";
    
    
    //sscanf("/command test", "/%s %s", command,value);
    
    //printf("COMMAND TEST %s %s\n", command, value);
    sscanf("f/command value", "%*[^/]%s %s", command,value);
    printf("Ciao %s %s\n", command, value);
     command[0]= '\0';
    value[0]= '\0';
    sscanf("dasda asdasdas asdasd command value", "/%s %s", command,value);
    printf("Ciao %s %s\n", command, value);
    
    return 0;
}
 */
/*
int main (){

    char command[10];
    char value[10];
    char *msg = "adasd /commang value";
    
    
    sscanf(msg, "%*[^ ] /%s %s", command,value);
    
    char *pipo;
    strcpy(command,pipo);
    
    printf("COMMAND VALUE PIPP [%s] [%s] [%s]\n", command, value, pipo);
    
     msg = "adasd /list ";
    sscanf(msg, "%*[^ ] /%s %s", command,value);
    
    printf("COMMAND VALUE PIPP [%s] [%s] [%s]\n", command, value, pipo);
    
    msg = "adasd /pippo ancora";
    sscanf(msg, "%*[^ ] /%s %s", command,value);
    
    printf("COMMAND VALUE PIPP [%s] [%s] [%s]\n", command, value, pipo);
   
    
    char *pippo = "ciao";
    char newVal[10];

     
}
*/


/*

int main (){
    struct command_t *t =  parseCommand("a /list 'mirko'");
    printf ("Valore di command e value [%s] [%s]\n", t->command, t->value);
    struct command_t *to =  parseCommand("a/nick 'pippo'  ");
    printf ("Valore di command e value [%s] [%s]\n", to->command, to->value);
    struct command_t *too =  parseCommand("asdasd /nick");
    printf ("Valore di command e value [%s] [%s]\n", too->command, too->value);
    
    too =  parseCommand("asdasd ");
    printf ("Valore di command e value [%s] [%s]\n", too->command, too->value);
    
    too =  parseCommand("asdasd /list \"a\"");
    printf ("Valore di command e value [%s] [%s]\n", too->command, too->value);
    
}*/


