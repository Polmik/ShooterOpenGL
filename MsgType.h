#ifndef MSGTYPE_H
#define MSGTYPE_H

#include <SFML/Network.hpp>

enum class MsgType
{
    None,        
    Fake,        
    Confirm,     
    Connect,     
    Disconnect,  
    WorldInit,   
    WorldUpdate, 
    PlayerUpdate,
    Shoot,       
};

sf::Packet& operator<<(sf::Packet& packet, MsgType type);
sf::Packet& operator>>(sf::Packet& packet, MsgType& type);


#endif //MSGTYPE_H
