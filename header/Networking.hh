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

#include "NetworkProtocol.pb.h"
#include "Core.hpp"
#include "Player.hpp"

#define     MAP_SEND_SIZE       50
#define     MAX_SEND_PLAYERS    10

struct                      Client {
    int                     sockfd;
    std::string             name;
    std::list<std::string *>    toSend;
    int                         sizeSended;
    // first is the start position to send the message, second is the messages
    std::string     inputBuffer;
    int          messageLength;
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
        Networking(const std::string &port); // if server
        Networking(const std::string &port, const std::string &addr); // if client
        ~Networking();
        bool                            newPlayers();
        // Called in loop to accept new clients, return true if new connections, else false
        void                            startGame(Core *);
        // Close listening for new clients
        const std::list<Client *>       &getPlayers() const;
        // Get the list of clients
        bool                            isServer() const;
        void                            refreshGame();
        bool                            isGameStarted();
        void                            spawnBomb();
        void                            consumeBonus();
        void                            updatePlayer(Player *);
    private:
        bool                    _initialized;
        bool                    _isServer;
        Core                    *_core;
        bool                    _closed;
        int                     _sockfd;
        Bomberman::Message      _initMessage;
        std::list<Client *>     _players;
        void    _receiveFromClient(Client *);
        void    _sendToClient(Client *);
        void    _sendMapUpdate(Client *);
        void    _sendPlayersUpdate(Client *);
        void    _treatMessage(Client *, Bomberman::Message *);
        void    _startGameServer();
        void    _startGameClient();
        void    _tryPurgeBuffer();
        void    _sendOwnInfos();
        Bomberman::Message          *_buildMessage(Bomberman::Message::MessageType);
        std::list<std::string *>    _toSend;
        int                         _sizeSended;
        std::string                 _inputBuffer;
        int                         _messageLength;
};
