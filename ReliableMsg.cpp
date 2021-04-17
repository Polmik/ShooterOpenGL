#include <cmath>
#include "ReliableMsg.h"
#include "Time.h"
#include "settings.h"
ReliableMsg::ReliableMsg(sf::Packet& packet, sf::IpAddress address, sf::Uint16 port) : packet(packet), address(address), port(port), lastTry(-INFINITY), firstTry(Time::getTime()) {}
ReliableMsg::ReliableMsg(const ReliableMsg& msg) : packet(msg.packet), address(msg.address), port(msg.port), lastTry(msg.lastTry), firstTry(msg.firstTry) {}

bool ReliableMsg::trySend(sf::UdpSocket& socket)
{
    if (Time::getTime() - firstTry > TIMEOUT_SECONDS)
        return false;
    if (Time::getTime() - lastTry > RELIABLE_RETRY_TIME)
    {
        lastTry = Time::getTime();
        socket.send(packet, address, port);
    }
    return true;
}
