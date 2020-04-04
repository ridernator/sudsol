#pragma once

#include <stdint.h>
#include <set>

namespace DataStructures {

    typedef enum class direction : uint8_t {
        NEXT = 0,
        PREVIOUS = NEXT + 1
    } Direction;
    
    static const std::set<Direction> DIRECTIONS = {Direction::NEXT, Direction::PREVIOUS};
}