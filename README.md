## MCCHAT: A Server/Client textual C chat  

The aim of the project is to create the a multi room chat based on Berkley Socket API. [http://en.wikipedia.org/wiki/Berkeley_sockets](http://en.wikipedia.org/wiki/Berkeley_sockets).
Functionalities provided by the server are:

* concurrent access of multiple clients
* maintaining and showing the clients list
* creating or joining a room
* changing host nickname
* sending a private message to a specific user

## Client basic usage:  
***


* Write to the console to send a message to the current client room
* `/room "[ROOMNAME]"` to change the current room
* `/nickname "[NICKNAME]"` to change nickname
* `/[NICKNAME] "[MESSAGE]"` to send a private message to the nickname specified
* `/list "ALL"` to get all participants nickname and rooms
* `/list` "[ROOMNAME]" to see all client in the relative rom
* `/help` to get the available commands

***
## How to compile
`make clean`  
`make`  

## How to start the server 
`./chat_server [portNumber] `
## How to start the client 
`./chat_client [serverIp] [serverPort] `  
A demonstration video is available at the url:
http://www.youtube.com/watch?v=-33-0DcUfS4

## Platform 
* Linux, Unix, Mac 
* gcc compiler version 4.1+
