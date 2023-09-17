#pragma once

#include "common.h"

#include <algorithm>
#include <deque>
#include <map>
#include <unordered_map>

namespace object_processor {
    class ObjectProcessor {
        using ObjectMap = std::unordered_map<std::string, std::deque<const ObjectData*>>;

        const int MIN_COUNT_FOR_GROUP = 3;



    public:

        ObjectProcessor() = default;

        void ReadFromFile(const std::string& file_name);


        std::map<char, const ObjectData*> GetSortedByNameData() const {
            std::map<char, const ObjectData*> result;




        }

    private:
        std::deque<ObjectData> objects_;
        ObjectMap object_map_by_type_;
        ObjectMap object_map_by_name_;

        ObjectData GetObjectFromLine(std::istream& input) const;
        bool IsRussianLetter(unsigned char ch) const {
            return (ch >= 192 && ch <= 255);
        }
    };
} //namespace object_processor