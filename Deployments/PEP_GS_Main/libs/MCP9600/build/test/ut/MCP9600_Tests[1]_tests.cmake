add_test( MCP9600_Tests.mcp_device_enable_function /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/libs/MCP9600/build/test/ut/MCP9600_Tests [==[--gtest_filter=MCP9600_Tests.mcp_device_enable_function]==] --gtest_also_run_disabled_tests)
set_tests_properties( MCP9600_Tests.mcp_device_enable_function PROPERTIES WORKING_DIRECTORY /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/libs/MCP9600/build/test/ut SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( MCP9600_Tests.mcp_device_disable_function /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/libs/MCP9600/build/test/ut/MCP9600_Tests [==[--gtest_filter=MCP9600_Tests.mcp_device_disable_function]==] --gtest_also_run_disabled_tests)
set_tests_properties( MCP9600_Tests.mcp_device_disable_function PROPERTIES WORKING_DIRECTORY /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/libs/MCP9600/build/test/ut SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( MCP9600_Tests_TESTS MCP9600_Tests.mcp_device_enable_function MCP9600_Tests.mcp_device_disable_function)
