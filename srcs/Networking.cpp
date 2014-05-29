//
// Networking.cpp for bomberman in /home/geekuillaume/Dropbox/Epitech/tek2/current/cpp_bomberman/srcs/Networking.cpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri May  9 15:35:33 2014 Mehdi Chouag
//

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <poll.h>
#include <netdb.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include "BomberException.hpp"
#include "Networking.hh"

Networking::Networking(Core &core, int port) : _core(core)
{
    struct protoent *pe;
    int         tmp;
    struct sockaddr_in  localaddr;

    if ((pe = getprotobyname("TCP")) == NULL)
        throw new BomberException(strerror(errno));
    if ((_sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
        throw new BomberException(strerror(errno));
    setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = INADDR_ANY;
    localaddr.sin_port = htons(port);
    if (bind(_sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr)) == -1)
        throw new BomberException(strerror(errno));
    if (listen(_sockfd, 10) == -1)
        throw new BomberException(strerror(errno));
    _closed = false;
}

Networking::Networking(Core &core, std::string &port, std::string &addr) : _core(core)
{
    struct addrinfo     hints;
    struct addrinfo     *info;
    struct protoent     *pe;
    int                 s;

    _closed = false;
    if ((pe = getprotobyname("TCP")) == NULL)
        throw new BomberException(strerror(errno));
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = pe->p_proto;
    if ((s = getaddrinfo(addr.c_str(), port.c_str(), &hints, &info)) != 0)
        throw new BomberException(strerror(errno));
    while (info)
    {
        if ((_sockfd = socket(info->ai_family, info->ai_socktype,
            info->ai_protocol)) != -1 && connect(_sockfd, info->ai_addr,
            info->ai_addrlen) != -1)
            return ;
        info = info->ai_next;
    }
    throw new BomberException(strerror(errno));
}

Networking::~Networking()
{
    if (!_closed)
        close(_sockfd);
}

void Networking::finishListening()
{
    _closed = true;
    close(_sockfd);
}

bool     Networking::newPlayers()
{
    struct pollfd   fds;
    Client          *client;
    bool            rtr;

    fds.fd = _sockfd;
    fds.events = POLLIN;
    rtr = false;
    while (poll(&fds, 1, 0) > 0)
    {
        client = new Client;
        if (accept(client->sockfd, NULL, 0) == -1)
            throw new BomberException(strerror(errno));
        client->name = "Test";
        client->lastTick = 0;
        _players.push_back(client);
        rtr = true;
    }
    return rtr;
}

const std::list<Client *>   Networking::getPlayers() const
{
    return _players;
}

void    Networking::refreshPlayers()
{
    fd_set      sets[3];
    int         max = 0;

    FD_ZERO(&sets[0]);
    FD_ZERO(&sets[1]);
    FD_ZERO(&sets[2]);
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        FD_SET((*i)->sockfd, &sets[0]);
        if (!(*i)->toSend.empty())
            FD_SET((*i)->sockfd, &sets[1]);
        max = ((*i)->sockfd > max) ? (*i)->sockfd + 1 : max;
    }
    select(max, &sets[0], &sets[1], &sets[2], NULL);
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        if (FD_ISSET((*i)->sockfd, &sets[0]))
            _receiveFromClient(*i);
        if (FD_ISSET((*i)->sockfd, &sets[1]))
            _sendToClient(*i);
    }
}

void    Networking::_receiveFromClient(Client *client)
{
    ssize_t     sizeRecv;

    do {
        sizeRecv = recv(client->sockfd,
            &client->inputBuffer.second[client->inputBuffer.first],
            sizeof(Message),
            MSG_DONTWAIT);
        client->inputBuffer.first += sizeRecv;
        if (client->inputBuffer.first >= sizeof(Message))
        {
            _treatMessage(client, reinterpret_cast<Message *>(client->inputBuffer.second));
            memmove(client->inputBuffer.second,
                &client->inputBuffer.second[client->inputBuffer.first],
                client->inputBuffer.first - sizeof(Message));
            client->inputBuffer.first -= sizeof(Message);
        }
    } while (sizeRecv > 0);
}

void    Networking::_treatMessage(Client *client, Message *message)
{

}

void    Networking::_sendToClient(Client *client)
{
    ssize_t     sizeSent;
    std::pair<unsigned int, Message *>     *toSend;

    do {
        toSend = &*(client->toSend.begin());
        sizeSent = send(client->sockfd,
            &toSend->second[toSend->first],
            sizeof(*toSend->second) - toSend->first,
            MSG_NOSIGNAL | MSG_DONTWAIT);
        if (sizeSent < 0 && errno == EPIPE)
        {
            // TODO : treat disconnection of player
        }
        toSend->first += sizeSent;
        if (toSend->first >= sizeof(*toSend->second))
        {
            client->toSend.pop_front();
            delete toSend;
        }
    } while (sizeSent > 0);
}
