#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <SFML/Network.hpp>

class UDPConnection
{
private:
    sf::Uint16 _id;
    sf::IpAddress _ip;
    sf::Uint16 _port;
    double lastMsg;

public:
    explicit UDPConnection(sf::Uint16 id, sf::IpAddress ip, sf::Uint16 port);
    sf::Uint16 getId() const;
    const sf::IpAddress& getIp() const;
    sf::Uint16 getPort() const;
    bool isTimeout() const;
    bool equals(sf::IpAddress& ip, sf::Uint16 port) const;
    void update();
    void sendPacket(sf::UdpSocket& socket, sf::Packet& packet);
};


#endif //UDPCONNECTION_H
