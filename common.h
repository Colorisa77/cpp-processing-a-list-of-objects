#pragma once

#include <string>
#include <ctime>

struct ObjectData {
    std::string object_name;
    double pos_x;
    double pos_y;
    std::string object_type;
    std::time_t creation_time;

    bool operator==(const ObjectData& other) const {
        return object_name == other.object_name &&
            pos_x == other.pos_x &&
            pos_y == other.pos_y &&
            object_type == other.object_type &&
            creation_time == other.creation_time;
    }
};