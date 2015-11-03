#pragma once

#include <tuple>
#include <string>


typedef std::tuple<std::string, std::string> PacketTulpe;

class Packets {
public:
    static PacketTulpe parse(const std::string& packet);
};
