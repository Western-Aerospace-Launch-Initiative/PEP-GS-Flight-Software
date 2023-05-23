// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

extern "C" {
    #include "../../MCP9600.h"
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
