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
