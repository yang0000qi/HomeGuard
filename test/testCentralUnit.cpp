#include "catch.hpp"
#define private public
#include "CentralUnit.h"


TEST_CASE("test parse packet", "[CentralUnit,unit]") {
    CentralUnit cu;

    SECTION("split the packet") {
        std::string id, status;
        std::tie(id, status) = cu._parsePacket("1,TRIPPED");
        CHECK(id == "1");
        CHECK(status == "TRIPPED");
    }
}

TEST_CASE("test find sensor by id", "[CentralUnit,unit]") {
    CentralUnit cu;

    SECTION("find the sensor") {
        Sensor s1("1", "door", SensorType::DOOR);
        Sensor s2("2", "window", SensorType::FIRE);
        Sensor s3("3", "cell", SensorType::WINDOW);
        cu.sensorManager().registerSensor(s1);
        cu.sensorManager().registerSensor(s2);
        cu.sensorManager().registerSensor(s3);

        Sensor s = cu.sensorManager().getSensor("1");
        CHECK(s.getID() == "1");
        CHECK(s.getLocation() == "door");
        CHECK(s.getType() == SensorType::DOOR);

        s = cu.sensorManager().getSensor("3");
        CHECK(s.getID() == "3");
        CHECK(s.getLocation() == "cell");
        CHECK(s.getType() == SensorType::WINDOW);
    }

    SECTION("no sensor in CentralUnit") {
        Sensor s = cu.sensorManager().getSensor("1");

        CHECK(s.getID() == "-1");
        CHECK(s.getLocation() == "No place");
        CHECK(s.getType() == SensorType::NONE);
    }
}

TEST_CASE("test get sensor message", "[Sensor,unit]") {
    Sensor s1("-1", "no location", SensorType::NONE);
    CHECK(s1.getMessage() == "default");

    Sensor s2("2", "door", SensorType::DOOR);
    s2.trip();
    CHECK(s2.getMessage() == "door is open");
    s2.reset();
    CHECK(s2.getMessage() == "door is closed");

    Sensor s3("3", "fan", SensorType::MOTION);
    s3.trip();
    CHECK(s3.getMessage() == "Motion detected in fan");
    s3.reset();
    CHECK(s3.getMessage() == "fan is motionless");
}

TEST_CASE("run sensor test", "[Sensor,unit]") {
    CentralUnit cu;
    Sensor s1("1", "door", SensorType::DOOR);
    Sensor s2("2", "window", SensorType::WINDOW);

    cu.sensorManager().registerSensor(s1);
    cu.runSensorTest();
    cu.onRadioBroadcast("1,NOT_TRIPPED");
    CHECK(cu.getSensorStatus() == SensorStatus::PENDING);
    cu.onRadioBroadcast("1,TRIPPED");
    CHECK(cu.getSensorStatus() == SensorStatus::PASS);

    s1.reset();
    cu.sensorManager().registerSensor(s2);
    cu.runSensorTest();
    cu.onRadioBroadcast("1,NOT_TRIPPED");
    cu.onRadioBroadcast("2,NOT_TRIPPED");
    CHECK(cu.getSensorStatus() == SensorStatus::PENDING);
    cu.onRadioBroadcast("1,TRIPPED");
    cu.onRadioBroadcast("2,TRIPPED");
    CHECK(cu.getSensorStatus() == SensorStatus::PASS);
}
