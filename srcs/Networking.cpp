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
    _allInitialized = true;
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
    _allInitialized = false;
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
    if (_isServer)
    {
        for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
            close((*i)->sockfd);
    }
}

void Networking::startGame(Core *core)
{
    NetworkPlayer *player;
    std::pair<float, float> tmpPos(_initMessage.data.infos.startX, _initMessage.data.infos.startY);

    _core = core;
    if (_isServer)
    {
        close(_sockfd);
        _closed = true;
        _startGameServer();
    }
    else
    {
        _core->getPlayer()[0]->setAbsPos(tmpPos);
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
        }
        _allInitialized = true;
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
            throw new BomberException(strerror(errno));
        inet_ntop(AF_INET, &saddr.sin_addr, ipv4addr, 100);
        client->name = ipv4addr;
        client->lastTick = 0;
        client->isConnected = true;
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
        if ((*i)->isConnected == false)
            continue;
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
        if (sizeRecv <= 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return;
            std::cerr << "Error recv : " << strerror(errno) << std::endl;
            if (client)
            {
                client->player->setLife(0);
                client->player->setIsAlive();
                client->isConnected = false;
                std::cerr << "Disconnected" << std::endl;
            }
            else
                throw new BomberException("Server Disconnected");
            return;
        }
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
    Bonus *tmp;

    if (message->type == INFOS)
    {
        memcpy(&_initMessage, message, sizeof(*message));
        _initialized = true;
    }
    if (!_core || !_allInitialized)
        return;
    if (!_isServer && message->type == MAP_UPDATE)
    {
        for(unsigned x = 0; x < MAP_SEND_SIZE; ++x) {
            for(unsigned y = 0; y < MAP_SEND_SIZE; ++y) {
                if (message->data.map.data[x * MAP_SEND_SIZE + y] == NOTHING)
                    _core->getMap()->deleteCube(x + message->data.map.start[0], y + message->data.map.start[1]);
                else if (!_core->getMap()->getCase(x, y) || _core->getMap()->getCase(x, y)->getType() != message->data.map.data[x * MAP_SEND_SIZE + y])
                    _core->getMap()->addCube(x + message->data.map.start[0],
                        y + message->data.map.start[1], message->data.map.data[x * MAP_SEND_SIZE + y]);
            }
        }
    }
    if (!_isServer && message->type == PLAYER_UPDATE)
    {
        for(unsigned i = 0; i < MAX_SEND_PLAYERS; ++i) {
            if (message->data.player[i].playerId == -1)
                break;
            if ((unsigned int)(message->data.player[i].playerId + 1) < _core->getPlayer().size())
            {
                _core->getPlayer()[message->data.player[i].playerId + 1]->setAbsPos(message->data.player[i].x, message->data.player[i].y);
                _core->getPlayer()[message->data.player[i].playerId + 1]->dir(message->data.player[i].dir);
            }
        }
    }
    if (!_isServer && message->type == OWN_PLAYER_INFO)
    {
        _core->getPlayer()[0]->setLife(message->data.ownPlayerInfo.life);
        _core->getPlayer()[0]->setRange(message->data.ownPlayerInfo.range);
        _core->getPlayer()[0]->setStock(message->data.ownPlayerInfo.stock);
    }
    if (!client)
        return;
    if (message->type == CONSUME_BONUS)
    {
        try {
            tmp = dynamic_cast<Bonus *>(_core->getMap()->getCase(client->player->getPos().first, client->player->getPos().second));
        }
        catch (...) {
            return;
        }
        if (!tmp)
            return;
        tmp->addToPlayer(client->player);
        _core->getMap()->deleteCube(tmp->getPos().first, tmp->getPos().second);
    }
    if (message->type == OWN_MOVE)
    {
        std::pair<float, float> pos = std::make_pair<float, float>(message->data.player[0].x, message->data.player[0].y);
        client->player->setAbsPos(pos);
        client->player->dir(message->data.player[0].dir);
    }
    if (message->type == OWN_BOMB)
        client->player->spawnBomb();
}

void    Networking::_sendToClient(Client *client)
{
    ssize_t     sizeSent;
    std::pair<unsigned int, Message *>     *toSend;

    do {
        if (((client) ? (client->toSend) : (_toSend)).size() == 0)
            return;
        toSend = (client) ? (&*(client->toSend.begin())) : (&*_toSend.begin());
        sizeSent = send((client) ? (client->sockfd) : (_sockfd),
            &((char*)toSend->second)[toSend->first],
            sizeof(*toSend->second) - toSend->first,
            MSG_NOSIGNAL | MSG_DONTWAIT);
        if (sizeSent <= 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return;
            std::cerr << "Error send : " << strerror(errno) << std::endl;
            if (client)
            {
                client->player->setLife(0);
                client->player->setIsAlive();
                client->isConnected = false;
                std::cerr << "Disconnected" << std::endl;
            }
            else
                throw new BomberException("Server Disconnected");
            return;
        }
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

void    Networking::spawnBomb()
{
    Message                 *msg = new Message;

    msg->type = OWN_BOMB;
    _toSend.push_back(std::make_pair<unsigned int, Message *>(0, msg));
}

void    Networking::consumeBonus()
{
    Message                 *msg = new Message;

    msg->type = CONSUME_BONUS;
    _toSend.push_back(std::make_pair<unsigned int, Message *>(0, msg));
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
        if (messagePos > MAX_SEND_PLAYERS - 2)
            break;
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

bool    Networking::isServer()
{
    return _isServer;
}

size_t     Networking::getListSize() const
{
    return (_players.size());
}

void    Networking::updatePlayer(Player *player)
{
    Client      *client = NULL;
    Message     *msg = new Message();

    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        if ((*i)->player == player)
        {
            client = *i;
            break;
        }
    }
    msg->type = OWN_PLAYER_INFO;
    msg->data.ownPlayerInfo.life = client->player->getLife();
    msg->data.ownPlayerInfo.range = client->player->getRange();
    msg->data.ownPlayerInfo.stock = client->player->getStock();
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

void    NetworkPlayer::setLife(int newLife)
{
    _life = newLife;
    _shield = 0;
    _core->getNetworking()->updatePlayer(this);
}

void  NetworkPlayer::setRange(int range)
{
    _range = range;
    _core->getNetworking()->updatePlayer(this);
}

void  NetworkPlayer::setStock(int stock)
{
    _stock = stock;
    _core->getNetworking()->updatePlayer(this);
}

void    NetworkOwnPlayer::spawnBomb()
{
    _core->getNetworking()->spawnBomb();
}

void    NetworkOwnPlayer::_consumeBonus(AObject *tmp)
{
    _core->getNetworking()->consumeBonus();
    _sound->playSound(BONUS_S, 30);
}
