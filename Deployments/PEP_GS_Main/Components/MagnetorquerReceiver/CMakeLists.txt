####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MagnetorquerReceiver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/MagnetorquerReceiver.cpp"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS
#     Add your dependencies here
# )

register_fprime_module()

get_module_name("${CMAKE_CURRENT_LIST_DIR}")
find_library(libBootloader bootloader ${CMAKE_CURRENT_LIST_DIR}/../../libs/ADCS/build)
find_library(libCommon common ${CMAKE_CURRENT_LIST_DIR}/../../libs/ADCS/build)
find_library(libCubeACP cubeacp ${CMAKE_CURRENT_LIST_DIR}/../../libs/ADCS/build)
find_library(libCubeADCS cubeadcs ${CMAKE_CURRENT_LIST_DIR}/../../libs/ADCS/build)
find_path(ADCS_LINCLUDES types.h ${CMAKE_CURRENT_LIST_DIR}/../../libs/ADCS/src)
include_directories(${ADCS_LINCLUDES})

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC ${libBootloader}
    PUBLIC ${libCommon}
    PUBLIC ${libCubeACP}
    PUBLIC ${libCubeADCS}
    )
