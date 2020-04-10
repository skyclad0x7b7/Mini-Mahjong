#include <Source/Constant.h>
#include <Source/Assert.h>

namespace Mini
{
    std::string GetWindTypeString(WindType type)
    {
        switch(type)
        {
        case WindType::East:
            return "East";
        case WindType::South:
            return "South";
        case WindType::West:
            return "South";
        case WindType::North:
            return "North";
        default:
            assert_unreachable();
        }
    }
} // namespace Mini