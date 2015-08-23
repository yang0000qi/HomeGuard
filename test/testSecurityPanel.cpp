#include "catch.hpp"
#define private public
#include "CentralUnit.h"


TEST_CASE("test security panel", "[SecurityPanel,unit]") {
    SecurityPanel sp;
    sp.setSecurityCode("this is correct password");
    CHECK(sp.isValidCode("this is not correct password") == false);
    CHECK(sp.isValidCode("this is correct password") == true);

    sp.arm();
    CHECK(sp.isArmed() == true);
    sp.enterCode("this is correct password");
    CHECK(sp.isArmed() == false);
}
