add_executable(Mini-Mahjong-Test
    Test.cpp
    Test.h
    TestMain.cpp
)

set_target_properties (Mini-Mahjong-Test PROPERTIES CXX_STANDARD 17)

target_link_libraries(Mini-Mahjong-Test Mini-Mahjong)
