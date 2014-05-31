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
    _isServer = true;
}

Networking::Networking(std::string &port, std::string &addr)
{
    struct addrinfo     hints;
    struct addrinfo     *info;
    struct protoent     *pe;
    int                 s;

    _isServer = false;
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

void Networking::startGame(Core *core)
{
    _core = core;
    _closed = true;
    close(_sockfd);
    if (_isServer)
        _startGameServer();
    else
        _startGameClient();
}

void    Networking::_startGameServer()
{
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {

    }
}

void    Networking::_startGameClient()
{

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

void    Networking::_tryPurgeBuffer()
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
    if (message->type == OWN_MOVE)
    {
        std::pair<float, float> pos = std::make_pair<float, float>(message->data.player.x, message->data.player.y);
        client->player->setPos(pos);
    }
    if (message->type == OWN_BOMB)
        client->player->spawnBomb();
    if (message->type == MAP_UPDATE)
    {
        for(unsigned x = 0; x < MAP_SEND_SIZE; ++x) {
            for(unsigned y = 0; y < MAP_SEND_SIZE; ++y) {
                _core->getMap()->deleteCube(x + message->data.map.start[0],
                    y + message->data.map.start[1]);
                if (message->data.map.data[x * MAP_SEND_SIZE + y] != NOTHING)
                    _core->getMap()->addCube(x + message->data.map.start[0],
                        y + message->data.map.start[1], message->data.map.data[x * MAP_SEND_SIZE + y]);
            }
        }
    }

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

void    Networking::refreshGame()
{
    if (_isServer)
    {
        _tryPurgeBuffer();
        for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
        {
            if (!(*i)->toSend.empty())
                continue;
            _sendMapUpdate(*i);
            _sendPlayersUpdate(*i);
        }
        _tryPurgeBuffer();
    }
}

void    Networking::_sendMapUpdate(Client *client)
{
    Message                 *msg = new Message;
    std::pair<float, float> pos = client->player->getPos();
    AObject                 *tmp;

    msg->type = MAP_UPDATE;
    msg->data.map.start[0] = pos.first - (MAP_SEND_SIZE / 2);
    msg->data.map.start[0] = pos.second - (MAP_SEND_SIZE / 2);
    for (unsigned x = 0; x < MAP_SEND_SIZE; ++x) {
        for (unsigned y = 0; y < MAP_SEND_SIZE; ++y) {
            tmp = _core->getMap()->getCase(x, y);
            if (tmp)
                msg->data.map.data[x * MAP_SEND_SIZE + y] = tmp->getType();
            else
                msg->data.map.data[x * MAP_SEND_SIZE + y] = NOTHING;
        }
    }
    client->toSend.push_back(std::make_pair<unsigned int, Message *>(0, msg));
}

void    Networking::_sendPlayersUpdate(Client *client)
{

}

NetworkPlayer::NetworkPlayer()
{
  _modelpath = "./ressources/assets/anim/bomberman_blue_run.FBX";
}

PlayerType NetworkPlayer::getType() const
{
    return (NETWORK);
}
