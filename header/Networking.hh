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

enum    MSG_TYPE {
    OWN_MOVE = 1,
    OWN_BOMB = 2,
    MAP_UPDATE = 3,
    PLAYER_UPDATE = 4,
};

struct          message {
    MSG_TYPE    type;
    union       data {
        struct player {
            unsigned int playerId;
            unsigned int x;
            unsigned int y;
        };
        struct map {
            int start[2]; // x and y of start of map chunk
            int width; // width of a line sended
            char data[256]; // 0 for nothing, 1 for border, 2 for basic block, 3 for destroyable block
        };
    };
};

struct                      Client {
    int                     sockfd;
    int                     lastTick;
    std::string             name;
    std::list<std::pair<int, message *> >       toSend;
    // first is the start position to send the message, second is the messages
    std::pair<int, char[sizeof(message) + 1]>   inputBuffer;
    // first is the actual position in the buffer, second is the buffer
};


class Networking {
    public:
        Networking(int port); // if server
        Networking(std::string &port, std::string &addr); // if client
        ~Networking();
        bool                            newPlayers();
        // Called in loop to accept new clients, return true if new connections, else false
        void                            finishListening();
        // Close listening for new clients
        const std::list<Client *>       getPlayers() const;
        // Get the list of clients
        void                            refreshPlayers();
    private:
        bool                    _closed;
        int                     _sockfd;
        std::list<Client *>     _players;
        void    _receiveFromClient(Client *);
        void    _sendToClient(Client *);
};
