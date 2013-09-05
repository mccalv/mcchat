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
 
 
 
/**
Utility file with functions to open and reads content from FS
*/
#include "basic.h"






char  *parseInt(int input)


{
    static char parsedString[5];
    sprintf(parsedString, "%d", input);
    return parsedString;
    
};

/*
Opens a file in a given location and returns its content as char *
*/
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



