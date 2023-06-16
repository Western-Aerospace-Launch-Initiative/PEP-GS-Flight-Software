add_test( ADCS_Tests.Basic_Assertions /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/libs/ADCS/build/test/ut/ADCS_Tests [==[--gtest_filter=ADCS_Tests.Basic_Assertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( ADCS_Tests.Basic_Assertions PROPERTIES WORKING_DIRECTORY /home/noahbraasch/WALI/PEP-GS-Flight-Software/Deployments/PEP_GS_Main/libs/ADCS/build/test/ut SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( ADCS_Tests_TESTS ADCS_Tests.Basic_Assertions)
