#include "CheckModule.h"


void CheckModule::runSensorTest()
{
    _runningSensorTest = true;
    _sensorTestStatus = SensorStatus::PENDING;

    sensorManager()->clearStatusMap();

    for (auto sensor : sensorManager()->sensors()) {
        sensorManager()->setStatus(sensor.getID(), SensorStatus::PENDING);
    }
}

void CheckModule::check(const std::string& id, const std::string& status)
{
    if (_runningSensorTest) {
        if (SensorStatus::TRIPPED == status) {
            sensorManager()->setStatus(id, SensorStatus::PASS);
        }

        if (_sensorTestDone()) {
            _terminateSensorTest();
        }
    }
}

bool CheckModule::_sensorTestDone()
{
    for (auto statusMap : sensorManager()->sensorStatusMap()) {
        std::string testStatus = statusMap.second;
        if (SensorStatus::PENDING == testStatus) {
            return false;
        }
    }
    return true;
}

void CheckModule::_terminateSensorTest()
{
    _runningSensorTest = false;

    // look at individual sensor status to determine the overall test status
    _sensorTestStatus = SensorStatus::PASS;
    for (auto statusMap : sensorManager()->sensorStatusMap()) {
        std::string status = statusMap.second;
        if (SensorStatus::PENDING == status) {
            _sensorTestStatus = SensorStatus::FAIL;
            break;
        }
    }
}
