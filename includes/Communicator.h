#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include "aipprotocol.h"

class Communicator
{
    public:
        Communicator();
        Communicator(const char*);
        virtual ~Communicator();
        void SendMessage(int msgCode);
        void SendMessage(int msgCode, Glib::ustring message);
        void ReceiveMsg(char* buffer);
        
        struct return_values {
            int time;
            int color;
            int group;
            int end;
            int max_ends;
        };
        
        return_values ReceiveMsg();

    protected:

    private:
        void Send(char* buffer);
        int sockfd;
};

#endif // COMMUNICATOR_H
