#pragma once

#include <memory>
#include <string>

#include "SensorManager.h"


class CheckModule {
public:
    void runSensorTest();
    void check(const std::string& id, const std::string& status);

    std::string status() const {
        return _sensorTestStatus;
    }

    void setSensorManager(std::shared_ptr<SensorManager> manager) {
        _sensorManager = manager;
    }

    std::shared_ptr<SensorManager> sensorManager() {
        return _sensorManager;
    }

private:
    void _terminateSensorTest();
    bool _sensorTestDone();

private:
    std::string _sensorTestStatus = SensorStatus::PENDING;
    bool _runningSensorTest = false;

    std::shared_ptr<SensorManager> _sensorManager;
};
