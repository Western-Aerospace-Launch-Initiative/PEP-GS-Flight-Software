add_test( TestTests.BasicAssertions /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/Drivers/MCP9600/build/test/ut/MCP9600_Tests [==[--gtest_filter=TestTests.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( TestTests.BasicAssertions PROPERTIES WORKING_DIRECTORY /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/Drivers/MCP9600/build/test/ut SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( MCP9600_Tests_TESTS TestTests.BasicAssertions)
