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
#include <arpa/inet.h>
#include <poll.h>
#include <netdb.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include "BomberException.hpp"
#include "Networking.hh"

Networking::Networking(std::string &port)
{
    struct protoent *pe;
    int         tmp;
    struct sockaddr_in  localaddr;

    std::cout << "Server start" << std::endl;
    if ((pe = getprotobyname("TCP")) == NULL)
        throw new BomberException(strerror(errno));
    if ((_sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
        throw new BomberException(strerror(errno));
    setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = INADDR_ANY;
    localaddr.sin_port = htons(atoi(port.c_str()));
    if (bind(_sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr)) == -1)
        throw new BomberException(strerror(errno));
    if (listen(_sockfd, 10) == -1)
        throw new BomberException(strerror(errno));
    _closed = false;
    _isServer = true;
    _core = NULL;
}

Networking::Networking(std::string &port, std::string &addr)
{
    struct addrinfo     hints;
    struct addrinfo     *info;
    struct protoent     *pe;
    int                 s;

    std::cout << "Client start" << std::endl;
    _isServer = false;
    _closed = false;
    _initialized = false;
    _core = NULL;
    _inputBuffer.first = 0;
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
    NetworkPlayer *player;
    std::pair<float, float> tmpPos(_initMessage.data.infos.startX, _initMessage.data.infos.startY);

    _core = core;
    std::cout << "here" << std::endl;
    if (_isServer)
    {
        close(_sockfd);
        _closed = true;
        _startGameServer();
    }
    else
    {
        std::cout << "map size : " << _initMessage.data.infos.mapSize << std::endl;
        _core->getPlayer()[0]->setAbsPos(tmpPos);
        std::cout << "pos : " << tmpPos.first << " - " << tmpPos.second << std::endl;
        for(unsigned i = 0; i < _initMessage.data.infos.playersNb - 1; ++i) {
            player = new NetworkPlayer();
            player->initialize();
            tmpPos.first = -1;
            tmpPos.second = -1;
            player->setAbsPos(tmpPos);
            player->setMap(_core->getMap());
            player->setBombs(&_core->getBombs());
            player->setPlayerTab(&_core->getPlayer());
            player->setSound(_core->getSound());
            _core->getPlayer().push_back(player);
            printf("Created client at index : %lu\n", _core->getPlayer().size());
        }
        std::cout << "max player : " << _initMessage.data.infos.playersNb << std::endl;
    }
}

void    Networking::_startGameServer()
{
    NetworkPlayer *player;
    std::pair<float, float> tmpPos;
    Message                 *msg;
    unsigned int            playerNb;

    playerNb = _core->getPlayer().size() + _players.size();
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        std::cout << "added player" << std::endl;
        player = new NetworkPlayer();
        tmpPos = _core->getMap()->getSpawn();
        player->initialize();
        player->setAbsPos(tmpPos);
        player->setMap(_core->getMap());
        player->setBombs(&_core->getBombs());
        player->setPlayerTab(&_core->getPlayer());
        player->setSound(_core->getSound());
        _core->getPlayer().push_back(player);
        (*i)->player = player;
        msg = new Message;
        msg->type = INFOS;
        msg->data.infos.mapSize = _core->getMap()->getSize();
        msg->data.infos.startX = player->getPos().first;
        msg->data.infos.startY = player->getPos().second;
        msg->data.infos.playersNb = playerNb;
        msg->data.infos.yourIndex = _core->getPlayer().size() - 1;
        (*i)->toSend.push_back(std::make_pair<int, Message *>(0, msg));
        _sendMapUpdate(*i);
    }
    _tryPurgeBuffer();
}

bool    Networking::isGameStarted()
{
    _tryPurgeBuffer();
    return (_initialized);
}

bool     Networking::newPlayers()
{
    struct pollfd       fds;
    Client              *client;
    bool                rtr;
    char                ipv4addr[100];
    struct sockaddr_in  saddr;
    socklen_t           len = sizeof(saddr);

    if (!_isServer)
        return false;
    fds.fd = _sockfd;
    fds.events = POLLIN;
    rtr = false;
    while (poll(&fds, 1, 0) > 0)
    {
        client = new Client;
        if ((client->sockfd = accept(_sockfd, reinterpret_cast<struct sockaddr*>(&saddr), &len)) == -1)
        {
            std::cout << "here" << std::endl;
            throw new BomberException(strerror(errno));
        }
        inet_ntop(AF_INET, &saddr.sin_addr, ipv4addr, 100);
        client->name = ipv4addr;
        client->lastTick = 0;
        _players.push_back(client);
        std::cout << "new player " << client->name << std::endl;
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
    struct timeval timeout;

    FD_ZERO(&sets[0]);
    FD_ZERO(&sets[1]);
    FD_ZERO(&sets[2]);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    if (!_isServer)
    {
        FD_SET(_sockfd, &sets[0]);
        if (!_toSend.empty())
            FD_SET(_sockfd, &sets[1]);
        max = _sockfd + 1;
    }
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        FD_SET((*i)->sockfd, &sets[0]);
        if (!(*i)->toSend.empty())
            FD_SET((*i)->sockfd, &sets[1]);
        max = ((*i)->sockfd > max) ? (*i)->sockfd + 1 : max;
    }
    if (select(max, &sets[0], &sets[1], &sets[2], &timeout) < 0)
        std::cerr << "Error on select : " << strerror(errno) << std::endl;
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        if (FD_ISSET((*i)->sockfd, &sets[0]))
            _receiveFromClient(*i);
        if (FD_ISSET((*i)->sockfd, &sets[1]))
            _sendToClient(*i);
    }
    if (FD_ISSET(_sockfd, &sets[0]))
        _receiveFromClient(NULL);
    if (FD_ISSET(_sockfd, &sets[1]))
        _sendToClient(NULL);
}

void    Networking::_receiveFromClient(Client *client)
{
    ssize_t     sizeRecv;
    std::pair<unsigned int, char[sizeof(Message) * 2 + 1]> *tmp;

    tmp = (!client) ? &_inputBuffer : &client->inputBuffer;
    do {
        sizeRecv = recv((!client) ? _sockfd : client->sockfd,
            &tmp->second[tmp->first],
            sizeof(Message),
            MSG_DONTWAIT);
        if (sizeRecv < 0)
            return;
        std::cout << "received : " << sizeRecv << std::endl;
        tmp->first += sizeRecv;
        if (tmp->first >= sizeof(Message))
        {
            _treatMessage(client, reinterpret_cast<Message *>(tmp->second));
            memmove(tmp->second,
                &tmp->second[tmp->first],
                tmp->first - sizeof(Message));
            tmp->first -= sizeof(Message);
        }
    } while (sizeRecv > 0);
}

void    Networking::_treatMessage(Client *client, Message *message)
{
    std::cout << "Treating message" << std::endl;
    if (message->type == INFOS)
    {
        std::cout << "INFOS" << std::endl;
        memcpy(&_initMessage, message, sizeof(*message));
        _initialized = true;
    }
    if (!_core)
        return;
    if (message->type == OWN_MOVE)
    {
        std::cout << "OWN MOVE" << std::endl;
        printf("OWN MOVE : %fx%f\n", message->data.player[0].x, message->data.player[0].y);
        std::pair<float, float> pos = std::make_pair<float, float>(message->data.player[0].x, message->data.player[0].y);
        client->player->setAbsPos(pos);
        client->player->dir(message->data.player[0].dir);
    }
    if (message->type == OWN_BOMB)
    {
        std::cout << "OWN BOMB" << std::endl;
        client->player->spawnBomb();
    }
    if (message->type == MAP_UPDATE)
    {
        std::cout << "MAP UPDATE" << std::endl;
        std::cout << "from : " << message->data.map.start[0] << "x" << message->data.map.start[1] << std::endl;
        for(unsigned x = 0; x < MAP_SEND_SIZE; ++x) {
            for(unsigned y = 0; y < MAP_SEND_SIZE; ++y) {
                // printf("Change at %dx%d\n", x, y);
                if (message->data.map.data[x * MAP_SEND_SIZE + y] == NOTHING)
                    _core->getMap()->deleteCube(x + message->data.map.start[0], y + message->data.map.start[1]);
                else if (!_core->getMap()->getCase(x, y) || _core->getMap()->getCase(x, y)->getType() != message->data.map.data[x * MAP_SEND_SIZE + y])
                    _core->getMap()->addCube(x + message->data.map.start[0],
                        y + message->data.map.start[1], message->data.map.data[x * MAP_SEND_SIZE + y]);
            }
        }
    }
    if (message->type == PLAYER_UPDATE)
    {
        for(unsigned i = 0; i < MAX_SEND_PLAYERS; ++i) {
            if (message->data.player[i].playerId == -1)
                break;
            printf("Setting player : %d at %fx%f\n", message->data.player[i].playerId, message->data.player[i].x, message->data.player[i].y);
            _core->getPlayer()[message->data.player[i].playerId + 1]->setAbsPos(message->data.player[i].x, message->data.player[i].y);
            _core->getPlayer()[message->data.player[i].playerId + 1]->dir(message->data.player[i].dir);
        }
    }
}

void    Networking::_sendToClient(Client *client)
{
    ssize_t     sizeSent;
    std::pair<unsigned int, Message *>     *toSend;

    do {
        toSend = (client) ? (&*(client->toSend.begin())) : (&*_toSend.begin());
        sizeSent = send((client) ? (client->sockfd) : (_sockfd),
            &toSend->second[toSend->first],
            sizeof(*toSend->second) - toSend->first,
            MSG_NOSIGNAL | MSG_DONTWAIT);
        if (sizeSent < 0 || sizeSent == 0)
        {
            if (client && (sizeSent == 0 || errno == EPIPE || errno == ECONNRESET || errno == EINTR))
                client->player->setIsAlive();
            return;
        }
        std::cout << "sent : " << sizeSent << std::endl;
        printf("From %d of type %d -> %p\n", toSend->first, toSend->second->type, toSend->second);
        toSend->first += sizeSent;
        if (toSend->first >= sizeof(*toSend->second))
        {
            delete toSend->second;
            if (client)
                client->toSend.pop_front();
            else
                _toSend.pop_front();
        }
    } while (sizeSent > 0);
}

void    Networking::refreshGame()
{
    _tryPurgeBuffer();
    if (_isServer)
    {
        for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
        {
            if (!(*i)->toSend.empty())
                continue;
            _sendMapUpdate(*i);
            _sendPlayersUpdate(*i);
        }
        _tryPurgeBuffer();
    }
    else
        _sendOwnInfos();
}

void    Networking::_sendOwnInfos()
{
    Message                 *msg = new Message;

    msg->type = OWN_MOVE;
    msg->data.player[0].x = _core->getPlayer()[0]->getPos().first;
    msg->data.player[0].y = _core->getPlayer()[0]->getPos().second;
    msg->data.player[0].dir = _core->getPlayer()[0]->dir();
    _toSend.push_back(std::make_pair<unsigned int, Message *>(0, msg));
}

void    Networking::_sendMapUpdate(Client *client)
{
    Message                 *msg = new Message;
    std::pair<float, float> pos = client->player->getPos();
    AObject                 *tmp;

    msg->type = MAP_UPDATE;
    msg->data.map.start[0] = static_cast<int>(pos.first) - (MAP_SEND_SIZE / 2);
    msg->data.map.start[1] = static_cast<int>(pos.second) - (MAP_SEND_SIZE / 2);
    for (unsigned x = 0; x < MAP_SEND_SIZE; ++x) {
        for (unsigned y = 0; y < MAP_SEND_SIZE; ++y) {
            tmp = _core->getMap()->getCase(x + msg->data.map.start[0], y + msg->data.map.start[1]);
            if (tmp)
                msg->data.map.data[x * MAP_SEND_SIZE + y] = tmp->getType();
            else
                msg->data.map.data[x * MAP_SEND_SIZE + y] = NOTHING;
        }
    }
    printf("Sending map update from : %dx%d -> %p\n", msg->data.map.start[0], msg->data.map.start[1], msg);
    printf("Client is at : %fx%f\n", pos.first, pos.second);
    client->toSend.push_back(std::make_pair<unsigned int, Message *>(0, msg));
}

void    Networking::_sendPlayersUpdate(Client *client)
{
    int id = 0;
    int messagePos = 0;
    Message *msg = new Message;

    msg->type = PLAYER_UPDATE;
    for (std::vector<Player *>::iterator i = _core->getPlayer().begin(); i != _core->getPlayer().end(); ++i)
    {
        if (*i && *i != client->player)
        {
            msg->data.player[messagePos].playerId = id;
            msg->data.player[messagePos].x = (*i)->getPos().first;
            msg->data.player[messagePos].y = (*i)->getPos().second;
            msg->data.player[messagePos].dir = (*i)->dir();
            ++messagePos;
        }
        ++id;
    }
    msg->data.player[messagePos].playerId = -1;
    client->toSend.push_back(std::make_pair<unsigned int, Message *>(0, msg));
}

NetworkPlayer::NetworkPlayer()
{
  _modelpath = "./ressources/assets/anim/bomberman_blue_run.FBX";
}

PlayerType NetworkPlayer::getType() const
{
    return (NETWORK);
}

size_t     Networking::getListSize() const
{
    return (_players.size());
}
