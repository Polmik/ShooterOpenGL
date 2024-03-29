#ifndef CLIENTUDP_H
#define CLIENTUDP_H

#include "World.h"
#include "Camera.h"
#include "ReliableMsg.h"
#include "UDPSocket.h"
#include <memory>

class ClientUDP
{
private:
    World& _world;
    Camera* _localPlayer;
    UDPSocket _socket;
    double _lastBroadcast;
    bool _working;

    std::map<sf::Uint16, std::shared_ptr<Player>> _players;

    bool process();
    bool timeout(sf::Uint16 id);

public:
    ClientUDP(World& world);
    bool isWorking() const;
    bool isConnected() const;
    Camera* localPlayer();
    void connect(sf::IpAddress ip, sf::Uint16 port);
    void disconnect();
    void update();
    void shoot(const std::string& name, double damage, double distance);
};


#endif //CLIENTUDP_H
