set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/MCP9600.h"
)

register_fprime_module()

set(UT_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/MCP9600.h"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
