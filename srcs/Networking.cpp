//
// Networking.cpp for bomberman in /home/geekuillaume/Dropbox/Epitech/tek2/current/cpp_bomberman/srcs/Networking.cpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri Jan 10 09:07:44 2014 guillaume besson
//

#include <sys/types.h>
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

Networking::Networking(int port)
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

Networking::Networking(std::string &port, std::string &addr)
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

    FD_ZERO(&sets[0]);
    FD_ZERO(&sets[1]);
    FD_ZERO(&sets[2]);
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
        FD_SET((*i)->sockfd, &sets[0]);
}

