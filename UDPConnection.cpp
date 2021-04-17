#include "UDPConnection.h"
#include "Time.h"
#include "settings.h"

UDPConnection::UDPConnection(sf::Uint16 id, sf::IpAddress ip, sf::Uint16 port) : _id(id), _ip(ip), _port(port), lastMsg(Time::getTime()) {}

sf::Uint16 UDPConnection::getId() const
{
    return _id;
}

const sf::IpAddress& UDPConnection::getIp() const
{
    return _ip;
}

sf::Uint16 UDPConnection::getPort() const
{
    return _port;
}

bool UDPConnection::isTimeout() const
{
    return Time::getTime() - lastMsg > TIMEOUT_SECONDS;
}

bool UDPConnection::equals(sf::IpAddress& ip, sf::Uint16 port) const
{
    return _port == port && _ip == ip;
}

void UDPConnection::update()
{
    lastMsg = Time::getTime();
}

void UDPConnection::sendPacket(sf::UdpSocket& socket, sf::Packet& packet)
{
    socket.send(packet, _ip, _port);
}
