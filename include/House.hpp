#pragma once

#include <stdint.h>

namespace DataStructures {

    typedef enum class house : uint8_t {
        ROW = 0,
        COLUMN = ROW + 1,
        BOX = COLUMN + 1
    } House;
    
    static const std::set<House> HOUSES = {House::ROW, House::COLUMN, House::BOX};
}