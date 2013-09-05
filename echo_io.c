
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
ssize_t writen(int fd, const void *buf, size_t n)
{
  size_t nleft;
  ssize_t nwritten;
  const char *ptr;

  ptr = buf;
  nleft = n;
  while (nleft > 0) {
    if ((nwritten = write(fd, ptr, nleft)) <= 0) {
       if ((nwritten < 0) && (errno == EINTR)) nwritten = 0; 	    
       else return(-1);	    /* errore */
    }
    nleft -= nwritten;
    ptr += nwritten;  
  }
  return(n-nleft);
}

/******/
int readline(int fd, void *vptr, int maxlen)
{
  int  n, rc;
  char c, *ptr;

  ptr = vptr;
  for (n = 1; n < maxlen; n++) {
    if ((rc = read(fd, &c, 1)) == 1) { 
      *ptr++ = c;
      if (c == '\n') break;
   } 
   else 
      if (rc == 0) {		/* read ha letto l'EOF */
 	 if (n == 1) return(0);	/* esce senza aver letto nulla */
 	 else break;
      } 
      else return(-1);		/* errore */
  }

  *ptr = 0;	/* per indicare la fine dell'input */
  return(n);	/* restituisce il numero di byte letti */
};
