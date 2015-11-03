#include "Packets.h"


PacketTulpe Packets::parse(const std::string& packet)
{
    std::string id;
    std::string status;

    size_t splitPosition = packet.find(',');
    if (splitPosition != std::string::npos) {
        id = packet.substr(0, splitPosition);
        status = packet.substr(splitPosition + 1);
    }

    return make_tuple(id, status);
}
