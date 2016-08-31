#include <glibmm-2.4/glibmm/ustring.h>

#include "Communicator.h"

Communicator::Communicator()
{

}

Communicator::Communicator(const char* addr)
{
    struct sockaddr_in serv_addr;
    int portno = aip::PORT;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(/*addr*/"10.42.0.147");
    serv_addr.sin_port = htons(portno);

    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Error on connecting" << std::endl;
        exit(1);
    }
}

void Communicator::SendMessage(int msgCode)
{
    char buffer[2];
    buffer[0] = 2;
    buffer[1] = msgCode;

    Send(buffer);
}

void Communicator::SendMessage(int msgCode, Glib::ustring message) {
    char buffer[129];
    
    bzero(buffer, sizeof(buffer));
    buffer[0] = message.length() + 2;
    buffer[1] = msgCode;
    
    for(int i = 0; i < 127 && i < message.size(); i++) {
        buffer[i+2] = message[i];
    }
    
    Send(buffer);
}

void Communicator::Send(char* buffer) {
    int command = buffer[0];
    
    switch(command) {
        case aip::TIMER:
            std::cout << int(buffer[2]) << ':' << int(buffer[3]) << ':' << int(buffer[4]) << std::endl;
            break;
            
        case aip::RUNTEXT:
            for(int i = 0; i < int(buffer[1]); i++) {
                std::cout << buffer[i+2];
            } std::cout << std::endl;
            break;
            
        case aip::NEW_ROUND:
            int duration;
            duration += buffer[4]*10;
            duration += buffer[5];
            bool group;
            group = (buffer[6] - '0') ? true : false;
            std::cout << int(buffer[2]) << int(buffer[3]) << duration << group << std::endl;
            break;
            
        case aip::TIME:
            std::cout << "Displaying time" << std::endl;
            break;
            
        default:
            std::cout << buffer << std::endl;
            break;
    }
    
    send(sockfd, buffer, strlen(buffer), MSG_CONFIRM);
    bzero(buffer, strlen(buffer));
}

int timer = 60;
int group = 0;
void Communicator::ReceiveMsg(char* buffer)
{
    read(sockfd, buffer, sizeof(buffer)/sizeof(char));
}

Communicator::return_values Communicator::ReceiveMsg() {
    char buffer[7];
    this->ReceiveMsg(buffer);
    
    Communicator::return_values values;
    values.time = buffer[1]*10 + buffer[2];
    values.color = buffer[3];
    values.group = buffer[4];
    values.end = buffer[5] + 1;
    values.max_ends = buffer[6];
    
    return values;
}

Communicator::~Communicator()
{
    close(sockfd);
}
