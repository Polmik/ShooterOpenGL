#ifndef SERVERUDP_H
#define SERVERUDP_H

#include "World.h"
#include "Camera.h"
#include "ReliableMsg.h"
#include "UDPSocket.h"
#include <memory>

class ServerUDP
{
private:
    World& _world;
    UDPSocket _socket;
    double _lastBroadcast;
    bool _working;

    std::map<sf::Uint16, std::shared_ptr<Player>> _players;
    std::vector<Point2D> _spawns;

    bool process();
    bool timeout(sf::Uint16 id);

public:
    ServerUDP(World& world);
    bool isWorking() const;
    bool start(sf::Uint16 port);
    void stop();
    void update();
    void addSpawn(Point2D point);
    void clearSpawns();
};


#endif //SERVERUDP_H
