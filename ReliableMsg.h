#ifndef RELIABLEMSG_H
#define RELIABLEMSG_H

#include <SFML/Network.hpp>

class ReliableMsg
{
private:
    sf::Packet packet;
    sf::IpAddress address;
    sf::Uint16 port;
    double lastTry;
    double firstTry;

public:
    ReliableMsg(sf::Packet& packet, sf::IpAddress address, sf::Uint16 port);
    ReliableMsg(const ReliableMsg& msg);

    bool trySend(sf::UdpSocket& socket);
};


#endif //RELIABLEMSG_H
