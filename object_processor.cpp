#include "object_processor.h"

#include <fstream>
#include <sstream>
#include <vector>

namespace object_processor {
    void ObjectProcessor::ReadFromFile(const std::string &file_name) {
        std::ifstream file(file_name, std::ios::in);
        if (!file.good()) {
            file.close();
            throw std::runtime_error("Can not open file " + file_name);
        }
        while (!file.eof()) {
            std::string line;
            std::getline(file, line);
            std::istringstream input(line);
            auto object = GetObjectFromLine(input);
            if(object_map_by_name_.count(object.object_name) == 0) {
                objects_.push_back(std::move(object));
                object_map_by_name_[objects_.back().object_name].push_back(&objects_.back());
                object_map_by_type_[objects_.back().object_type].push_back(&objects_.back());
            }
        }
        file.close();
    }

    ObjectData ObjectProcessor::GetObjectFromLine(std::istream &input) const {
        ObjectData obj;
        input >> obj.object_name;
        input >> obj.pos_x;
        input >> obj.pos_y;
        input >> obj.object_type;
        input >> obj.creation_time;
        return obj;
    }

} //namespace object_processor