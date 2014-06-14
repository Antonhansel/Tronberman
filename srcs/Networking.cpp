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

Networking::Networking(const std::string &port)
{
    struct protoent     *pe;
    int                 tmp;
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
    _messageLength = -1;
    _closed = false;
    _isServer = true;
    _core = NULL;
}

Networking::Networking(const std::string &port, const std::string &addr)
{
    struct addrinfo     hints;
    struct addrinfo     *info;
    struct protoent     *pe;
    int                 s;

    std::cout << "Client start" << std::endl;
    _isServer = false;
    _sizeSended = -1;
    _closed = false;
    _initialized = false;
    _core = NULL;
    _messageLength = -1;
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

Bomberman::Message  *Networking::_buildMessage(Bomberman::Message::MessageType type)
{
    Bomberman::Message *message = new Bomberman::Message;

    message->set_type(type);
    return message;
}

void Networking::startGame(Core *core)
{
    NetworkPlayer *player;
    std::pair<float, float> tmpPos;

    _core = core;
    if (_isServer)
    {
        close(_sockfd);
        _closed = true;
        _startGameServer();
    }
    else
    {
        tmpPos = std::make_pair<float, float>(_initMessage.info(0).startx(), _initMessage.info(0).starty());
        std::cout << "map size : " << _initMessage.info(0).mapsize() << std::endl;
        _core->getPlayer()[0]->setAbsPos(tmpPos);
        std::cout << "pos : " << tmpPos.first << " - " << tmpPos.second << std::endl;
        std::cout << "received pos : " << _initMessage.info(0).startx() << " - " << _initMessage.info(0).starty() << std::endl;
        for(int i = 0; i < _initMessage.info(0).playersnb() - 1; ++i) {
            player = new NetworkPlayer();
            player->initialize();
            tmpPos.first = -1;
            tmpPos.second = -1;
            player->setAbsPos(tmpPos);
            player->setMap(_core->getMap());
            player->setBombs(_core->getBombs());
            player->setPlayerTab(&_core->getPlayer());
            player->setSound(_core->getSound());
            _core->getPlayer().push_back(player);
            printf("Created client at index : %lu\n", _core->getPlayer().size());
        }
        std::cout << "max player : " << _initMessage.info(0).playersnb() << std::endl;
    }
}

void    Networking::_startGameServer()
{
    NetworkPlayer *player;
    std::pair<float, float> tmpPos;
    Bomberman::Message                  *msg;
    Bomberman::Message_Info             *info;
    std::string                         *serialized;
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
        player->setBombs(_core->getBombs());
        player->setPlayerTab(&_core->getPlayer());
        player->setSound(_core->getSound());
        _core->getPlayer().push_back(player);
        (*i)->player = player;
        msg = _buildMessage(Bomberman::Message::INFOS);
        info = msg->add_info();
        info->set_mapsize(_core->getMap()->getSize());
        info->set_startx(player->getPos().first);
        info->set_starty(player->getPos().second);
        info->set_playersnb(playerNb);
        serialized = new std::string();
        msg->SerializeToString(serialized);
        (*i)->toSend.push_back(serialized);
        _sendMapUpdate(*i);
        delete msg;
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
        client->messageLength = -1;
        client->sizeSended = -1;
        _players.push_back(client);
        std::cout << "new player " << client->name << std::endl;
        rtr = true;
    }
    return rtr;
}

const std::list<Client *>   &Networking::getPlayers() const
{
    return _players;
}

void    Networking::_tryPurgeBuffer()
{
    fd_set      sets[2];
    int         max = 0;
    struct timeval timeout;

    FD_ZERO(&sets[0]);
    FD_ZERO(&sets[1]);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    if (!_isServer)
    {
        FD_SET(_sockfd, &sets[0]);
        if (!_toSend.empty())
        {
            printf("Have to send...\n");
            FD_SET(_sockfd, &sets[1]);
        }
        max = _sockfd + 1;
    }
    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        FD_SET((*i)->sockfd, &sets[0]);
        if (!(*i)->toSend.empty())
            FD_SET((*i)->sockfd, &sets[1]);
        max = ((*i)->sockfd > max) ? (*i)->sockfd + 1 : max;
    }
    if (select(max, &sets[0], &sets[1], NULL, &timeout) < 0)
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
    int     sizeMsg;
    char        *tmp;
    Bomberman::Message msg;

    do {
        if (((!client) ? _messageLength : client->messageLength) == -1)
        {
            sizeRecv = recv(((!client) ? _sockfd : client->sockfd),
                &sizeMsg,
                sizeof(sizeMsg), MSG_DONTWAIT);
            if (sizeRecv <= 0)
                return;
            printf("Readed msg size : %d (total : %lu)\n", sizeMsg, sizeRecv);
            ((!client) ? _messageLength : client->messageLength) = sizeMsg;
        }
        printf("Allocating : %d\n", ((!client) ? _messageLength : client->messageLength));
        tmp = new char[((!client) ? _messageLength : client->messageLength)];
        sizeRecv = recv((!client) ? _sockfd : client->sockfd,
            tmp,
            ((!client) ? _messageLength : client->messageLength) - ((!client) ? _inputBuffer : client->inputBuffer).size(),
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
        ((!client) ? _inputBuffer : client->inputBuffer).append(tmp, sizeRecv);
        printf("Received : %lu (total : %lu / %d)\n", sizeRecv, ((!client) ? _inputBuffer : client->inputBuffer).size(), ((!client) ? _messageLength : client->messageLength));
        if ((int)((!client) ? _inputBuffer : client->inputBuffer).size() <= ((!client) ? _messageLength : client->messageLength))
        {
            printf("Got one message\n");
            if (msg.ParseFromString(((!client) ? _inputBuffer : client->inputBuffer)))
                _treatMessage(client, &msg);
            ((!client) ? _inputBuffer : client->inputBuffer).clear();
            ((!client) ? _messageLength : client->messageLength) = -1;
            printf("Size now : %lu / %d\n", ((!client) ? _inputBuffer : client->inputBuffer).size(), ((!client) ? _messageLength : client->messageLength));
        }
        delete tmp;
    } while (sizeRecv > 0);
}

void    Networking::_treatMessage(Client *client, Bomberman::Message *message)
{
    std::cout << "Treating message" << std::endl;
    if (message->type() == Bomberman::Message::INFOS)
    {
        std::cout << "INFOS" << std::endl;
        _initMessage = *message;
        _initialized = true;
    }
    if (!_core)
        return;
    if (message->type() == Bomberman::Message::OWN_MOVE)
    {
        std::cout << "OWN MOVE" << std::endl;
        printf("OWN MOVE : %fx%f\n", message->player(0).x(), message->player(0).y());
        std::pair<float, float> pos = std::make_pair<float, float>(message->player(0).x(), message->player(0).y());
        client->player->setAbsPos(pos);
        client->player->dir((dirr)message->player(0).dir());
    }
    if (message->type() == Bomberman::Message::OWN_BOMB)
    {
        std::cout << "OWN BOMB" << std::endl;
        client->player->spawnBomb();
    }
    if (message->type() == Bomberman::Message::MAP_UPDATE)
    {
        std::cout << "MAP UPDATE" << std::endl;
        std::cout << "from : " << message->map(0).startx() << "x" << message->map(0).starty() << std::endl;
        for(unsigned x = 0; x < MAP_SEND_SIZE; ++x) {
            for(unsigned y = 0; y < MAP_SEND_SIZE; ++y) {
                if (message->map(0).data()[x * MAP_SEND_SIZE + y] == NOTHING)
                    _core->getMap()->deleteCube(x + message->map(0).startx(), y + message->map(0).starty());
                else if (!_core->getMap()->getCase(x, y) || _core->getMap()->getCase(x, y)->getType() != message->map(0).data()[x * MAP_SEND_SIZE + y])
                {
                    // printf("Added cube of type : %d\n", message->map(0).data()[x * MAP_SEND_SIZE + y]);
                    _core->getMap()->addCube(x + message->map(0).startx(),
                        y + message->map(0).starty(), (type)message->map(0).data()[x * MAP_SEND_SIZE + y]);
                }
            }
        }
    }
    if (message->type() == Bomberman::Message::PLAYER_UPDATE)
    {
        for (int i = 0; i < message->player_size(); ++i)
        {
            printf("Setting player : %d at %fx%f\n", message->player(i).playerid(), message->player(i).x(), message->player(i).y());
            _core->getPlayer()[message->player(i).playerid() + 1]->setAbsPos(message->player(i).x(), message->player(i).y());
            _core->getPlayer()[message->player(i).playerid() + 1]->dir((dirr)message->player(i).dir());
        }
    }
    if (message->type() == Bomberman::Message::OWN_PLAYER_INFO)
    {
        _core->getPlayer()[0]->setLife(message->ownplayerinfo(0).life());
        _core->getPlayer()[0]->setRange(message->ownplayerinfo(0).range());
        _core->getPlayer()[0]->setStock(message->ownplayerinfo(0).stock());
    }
    if (message->type() == Bomberman::Message::CONSUME_BONUS)
    {
        Bonus *tmp;
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
}

void    Networking::_sendToClient(Client *client)
{
    ssize_t     sizeSent;
    int     msgSize;
    std::string     *toSend;
    const char            *reelSend;

    do {
        if (((client) ? (client->toSend) : (_toSend)).size() == 0)
            return;
        toSend = *((client) ? (&*(client->toSend.begin())) : (&*_toSend.begin()));
        if (((!client) ? _sizeSended : client->sizeSended) == -1)
        {
            msgSize = toSend->size();
            sizeSent = send((client) ? (client->sockfd) : (_sockfd),
                &msgSize,
                sizeof(msgSize),
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
            (!client) ? _sizeSended : client->sizeSended = 0;
            printf("Sended size : %d (total : %lu)\n", msgSize, sizeSent);
        }
        reelSend = &toSend->c_str()[(!client) ? _sizeSended : client->sizeSended];
        sizeSent = send((client) ? (client->sockfd) : (_sockfd),
            reelSend,
            toSend->size() - ((!client) ? _sizeSended : client->sizeSended),
            MSG_NOSIGNAL | MSG_DONTWAIT);
        if (sizeSent <= 0)
        {
            if (client && (sizeSent == 0 || errno == EPIPE || errno == ECONNRESET || errno == EINTR))
                client->player->setIsAlive();
            return;
        }
        std::cout << "sent : " << sizeSent << std::endl;
        printf("Send %li of %lu From %d\n", sizeSent, toSend->size(), (!client) ? _sizeSended : client->sizeSended);
        ((!client) ? _sizeSended : client->sizeSended) += sizeSent;
        if ((size_t)((!client) ? _sizeSended : client->sizeSended) >= toSend->size())
        {
            delete toSend;
            ((client) ? (client->toSend) : (_toSend)).pop_front();
            (!client) ? _sizeSended : client->sizeSended = -1;
            return;
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
    else if (_toSend.empty())
    {
        _sendOwnInfos();
        _tryPurgeBuffer();
    }
}

void    Networking::spawnBomb()
{
    Bomberman::Message                  *msg = _buildMessage(Bomberman::Message::OWN_BOMB);
    std::string                         *serialized = new std::string;

    msg->SerializeToString(serialized);
    _toSend.push_back(serialized);
    delete msg;
}

void    Networking::consumeBonus()
{
    Bomberman::Message                  *msg = _buildMessage(Bomberman::Message::CONSUME_BONUS);
    std::string                         *serialized = new std::string;

    msg->SerializeToString(serialized);
    _toSend.push_back(serialized);
    delete msg;
}

void    Networking::_sendOwnInfos()
{
    Bomberman::Message          *msg = _buildMessage(Bomberman::Message::OWN_MOVE);
    Bomberman::Message_Player   *player;
    std::string                 *serialized;

    player = msg->add_player();
    player->set_x(_core->getPlayer()[0]->getPos().first);
    player->set_y(_core->getPlayer()[0]->getPos().second);
    player->set_dir(_core->getPlayer()[0]->dir());
    serialized = new std::string();
    msg->SerializeToString(serialized);
    _toSend.push_back(serialized);
    delete msg;
}

void    Networking::_sendMapUpdate(Client *client)
{
    Bomberman::Message                 *msg = _buildMessage(Bomberman::Message::MAP_UPDATE);
    Bomberman::Message_Map             *map;
    char                               *mapData = new char[MAP_SEND_SIZE * MAP_SEND_SIZE];
    std::pair<float, float> pos = client->player->getPos();
    AObject                 *tmp;
    std::string             *serialized;

    map = msg->add_map();
    map->set_startx(static_cast<int>(pos.first) - (MAP_SEND_SIZE / 2));
    map->set_starty(static_cast<int>(pos.second) - (MAP_SEND_SIZE / 2));
    for (unsigned x = 0; x < MAP_SEND_SIZE; ++x) {
        for (unsigned y = 0; y < MAP_SEND_SIZE; ++y) {
            tmp = _core->getMap()->getCase(x + map->startx(), y + map->starty());
            if (tmp)
                mapData[x * MAP_SEND_SIZE + y] = tmp->getType();
            else
                mapData[x * MAP_SEND_SIZE + y] = NOTHING;
        }
    }
    map->set_data(mapData, MAP_SEND_SIZE * MAP_SEND_SIZE);
    printf("Sending map update from : %dx%d -> %p\n", map->startx(), map->starty(), msg);
    printf("Client is at : %fx%f\n", pos.first, pos.second);
    serialized = new std::string();
    msg->SerializeToString(serialized);
    client->toSend.push_back(serialized);
    delete msg;
    delete mapData;
}

void    Networking::_sendPlayersUpdate(Client *client)
{
    int id = 0;
    Bomberman::Message *msg = _buildMessage(Bomberman::Message::PLAYER_UPDATE);
    Bomberman::Message_Player   *player;
    std::string                 *serialized;

    for (std::vector<Player *>::iterator i = _core->getPlayer().begin(); i != _core->getPlayer().end(); ++i)
    {
        if (*i && *i != client->player)
        {
            player = msg->add_player();
            player->set_playerid(id);
            player->set_x((*i)->getPos().first);
            player->set_y((*i)->getPos().second);
            player->set_dir((*i)->dir());
        }
        ++id;
    }
    serialized = new std::string();
    msg->SerializeToString(serialized);
    client->toSend.push_back(serialized);
    delete msg;
}

bool    Networking::isServer() const
{
    return _isServer;
}

void    Networking::updatePlayer(Player *player)
{
    Client      *client = NULL;
    Bomberman::Message     *msg = _buildMessage(Bomberman::Message::OWN_PLAYER_INFO);
    Bomberman::Message_OwnPlayerInfo *info;

    for (std::list<Client *>::iterator i = _players.begin(); i != _players.end(); ++i)
    {
        if ((*i)->player == player)
        {
            client = *i;
            break;
        }
    }
    info = msg->add_ownplayerinfo();
    info->set_life(client->player->getLife());
    info->set_range(client->player->getRange());
    info->set_stock(client->player->getStock());
    std::string *serialized = new std::string();
    msg->SerializeToString(serialized);
    client->toSend.push_back(serialized);
    delete msg;
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
