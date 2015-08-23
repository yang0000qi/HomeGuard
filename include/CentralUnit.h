﻿#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "AudibleAlarm.h"
#include "HomeguardView.h"
#include "Sensor.h"
#include "SensorManager.h"


typedef std::tuple<std::string, std::string> PacketTulpe;

class CentralUnit {
public:
    CentralUnit();

    bool isArmed() const;
    void arm();
    void disarm();

    bool isValidCode(const std::string& code) const;
    void setSecurityCode(const std::string& code);
    void enterCode(const std::string& code);

    SensorManager& sensorManager();
    std::string getSensorStatus() const;
    void onRadioBroadcast(const std::string& packet);
    void runSensorTest();

private:
    void _sensorTest(const std::string& id, const std::string& status);
    void _terminateSensorTest();
    PacketTulpe _parsePacket(const std::string& packet);
    bool _sensorTestDone();

private:
    bool _armed;
    std::shared_ptr<AudibleAlarm> _audibleAlarm;
    std::shared_ptr<HomeguardView> _homeGuardView;
    bool _runningSensorTest;

    std::string _sensorTestStatus;
    std::string _securityCode;
    SensorManager _sensorManager;
};
