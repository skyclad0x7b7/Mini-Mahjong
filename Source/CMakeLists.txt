add_library(Mini-Mahjong STATIC 
    Assert.h
    Constant.cpp
    Constant.h
    Player.cpp
    Player.h
    Tile.cpp
    Tile.h
    TileGroup.cpp
    TileGroup.h
    Utils.cpp
    Utils.h
    Yaku.cpp
    Yaku.h
    ReassembledTileGroup.cpp
    ReassembledTileGroup.h
)

set_target_properties (Mini-Mahjong PROPERTIES CXX_STANDARD 17)
