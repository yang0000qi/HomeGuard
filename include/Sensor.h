#pragma once

#include <map>
#include <string>


static const std::string InvalidId = "-1";

struct SensorMessage {
    std::function<std::string(std::string)> tripped;
    std::function<std::string(std::string)> normal;
};

enum class SensorType {
    DOOR, WINDOW, MOTION, FIRE, NONE
};

typedef std::map<SensorType, SensorMessage> SensorMessageMap;

class Sensor {
public:
    Sensor(const std::string& id,
           const std::string& location,
           SensorType type);

    std::string getID () const;
    std::string getLocation() const;
    SensorType getType() const;

    bool isTripped() const;
    void trip();
    void reset();
    void triggerByStatus(const std::string status);
    std::string getMessage() const;

private:
    std::string id;
    std::string location;
    SensorType type;
    bool tripped;
};
