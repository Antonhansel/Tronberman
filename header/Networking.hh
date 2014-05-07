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

#include <string>
#include <list>

struct          Client {
    int         sockfd;
    int         lastTick;
    std::string name;
};

class Networking {
    public:
        Networking(int port); // if server
        Networking(std::string &port, std::string &addr); // if client
        ~Networking();
        bool                            newPlayers();
        void                            finishListening();
        const std::list<Client *>       getPlayers() const;
        void                            refreshPlayers();
    private:
        bool                    _closed;
        int                     _sockfd;
        std::list<Client *>     _players;
        std::string             _buffer;
};
