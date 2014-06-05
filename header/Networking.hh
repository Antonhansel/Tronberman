//
// Networking.hpp for bomberman in /home/geekuillaume/Dropbox/Epitech/tek2/current/cpp_bomberman/header/Networking.hpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri Jan 10 09:07:44 2014 guillaume besson
//

#pragma once

#include <stdint.h>

#include <string>
#include <list>

#include "Core.hpp"
#include "Player.hpp"

#define     MAP_SEND_SIZE       50
#define     MAX_SEND_PLAYERS    10

enum    MSG_TYPE {
    OWN_MOVE = 1,
    OWN_BOMB = 2,
    MAP_UPDATE = 3,
    PLAYER_UPDATE = 4,
    INFOS = 5,
    CONSUME_BONUS = 6,
    OWN_PLAYER_INFO = 7,
};

struct          Message {
    MSG_TYPE    type;
    union       {
        struct {
            int playerId;
            float x;
            float y;
            dirr dir;
        } player[MAX_SEND_PLAYERS];
        struct {
            int start[2]; // x and y of start of map chunk
            enum type data[(MAP_SEND_SIZE + 1) * MAP_SEND_SIZE];
        } map;
        struct {
            unsigned int mapSize;
            unsigned int playersNb;
            unsigned int yourIndex;
            float startX;
            float startY;
        } infos;
        struct {
            int life;
            int range;
            int stock;
        } ownPlayerInfo;
    } data;
};

struct                      Client {
    int                     sockfd;
    int                     lastTick;
    std::string             name;
    std::list<std::pair<unsigned int, Message *> >       toSend;
    // first is the start position to send the message, second is the messages
    std::pair<unsigned int, char[sizeof(Message) * 2 + 1]>   inputBuffer;
    // first is the actual position in the buffer, second is the buffer
    Player                  *player;
    bool                    isConnected;
};

class NetworkPlayer : public Player {
public:
    NetworkPlayer();
    void    update(gdl::Clock const &clock, gdl::Input &input) {};
    PlayerType getType() const;
    void    setLife(int);
    void    setRange(int);
    void    setStock(int);
};

class NetworkOwnPlayer : public Player {
public:
    void    spawnBomb();
protected:
    void    _consumeBonus(AObject *);
};

class Networking {
    public:
        Networking(std::string &port); // if server
        Networking(std::string &port, std::string &addr); // if client
        ~Networking();
        bool                            newPlayers();
        // Called in loop to accept new clients, return true if new connections, else false
        void                            startGame(Core *);
        // Close listening for new clients
        const std::list<Client *>       getPlayers() const;
        // Get the list of clients
        void                            refreshGame();
        bool                            isGameStarted();
        size_t                          getListSize() const;
        bool                            isServer();
        void                            spawnBomb();
        void                            consumeBonus();
        void                            updatePlayer(Player *);
    private:
        bool                    _initialized;
        bool                    _isServer;
        Core                    *_core;
        bool                    _closed;
        int                     _sockfd;
        Message                 _initMessage;
        std::list<Client *>     _players;
        void    _receiveFromClient(Client *);
        void    _sendToClient(Client *);
        void    _sendMapUpdate(Client *);
        void    _sendPlayersUpdate(Client *);
        void    _treatMessage(Client *, Message *);
        void    _startGameServer();
        void    _startGameClient();
        void    _tryPurgeBuffer();
        void    _sendOwnInfos();
        std::list<std::pair<unsigned int, Message *> >       _toSend;
        std::pair<unsigned int, char[sizeof(Message) * 2 + 1]>   _inputBuffer;
};
