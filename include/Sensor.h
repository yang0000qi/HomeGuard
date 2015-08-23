#pragma once

#include <functional>
#include <map>
#include <string>


static const std::string InvalidId = "-1";

struct SensorMessage {
    std::function<std::string()> tripped;
    std::function<std::string()> normal;
};

enum class SensorType {
    DOOR, WINDOW, MOTION, FIRE, NONE
};

typedef std::map<SensorType, SensorMessage> SensorMessageMap;

struct SensorStatus {
    static const std::string PASS;
    static const std::string FAIL;
    static const std::string PENDING;
    static const std::string READY;
    static const std::string TRIPPED;
};

class Sensor {
public:
    Sensor(const std::string& id,
           const std::string& location,
           SensorType type);

    void triggerByStatus(const std::string status);
    std::string message() const;

    std::string getID () const { return _id; }
    std::string getLocation() const { return _location; }
    SensorType getType() const { return _type; }
    bool isTripped() const { return _tripped; }
    void trip() { _tripped = true; }
    void reset() { _tripped = false; }

private:
    void _initSensorMessage();

private:
    std::string _id;
    std::string _location;
    SensorType _type;

    SensorMessageMap _messageMap;
    bool _tripped = false;
};
