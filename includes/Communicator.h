//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program; if not, write to the Free Software Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA,
//  or see see <http://gnu.org/licenses/gpl-2.0.txt>

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
        int StrLen(Glib::ustring message);
        int sockfd;
};

#endif // COMMUNICATOR_H
