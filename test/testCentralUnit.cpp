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
    Sensor s1("1", "door", Sensor::Type::DOOR);
    Sensor s2("2", "window", Sensor::Type::FIRE);
    Sensor s3("3", "cell", Sensor::Type::WINDOW);
    cu.registerSensor(s1);
    cu.registerSensor(s2);
    cu.registerSensor(s3);

    Sensor s = cu.getSensor("1");
    CHECK(s.id == "1");
    CHECK(s.location == "door");
    CHECK(s.type == Sensor::Type::DOOR);

    s = cu.getSensor("3");
    CHECK(s.id == "3");
    CHECK(s.location == "cell");
    CHECK(s.type == Sensor::Type::WINDOW);
}

TEST_CASE("test get sensor message", "[Sensor,unit]") {
    Sensor s1("-1", "no location", Sensor::Type::NONE);
    CHECK(s1.getMessage() == "default");

    Sensor s2("1", "door", Sensor::Type::DOOR);
    s2.trip();
    CHECK(s2.getMessage() == "door is open");
    s2.reset();
    CHECK(s2.getMessage() == "door is closed");
}
