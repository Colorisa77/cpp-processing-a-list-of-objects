#pragma once

#include "common.h"

#include <chrono>
#include <set>
#include <string_view>
#include <deque>
#include <map>
#include <unordered_map>
#include <locale>


namespace object_processor {

    double ComputeDistance(double pos_x, double pos_y);

    class ObjectProcessor {
    private:
        using ObjectMapByType = std::unordered_map<std::string, std::set<std::string_view>>;
        using ObjectMapByName = std::unordered_map<std::string_view, const ObjectData*>;

        using SortedObjects = std::map<std::string, std::set<std::string_view>>;

        const size_t MIN_COUNT_FOR_GROUP = 3;

        const int HUNDRED = 100;
        const int THOUSAND = 1000;
        const int TEN_THOUSAND = 10000;

        const int SECONDS_IN_DAY = 60 * 60 * 24;
        const int SECONDS_IN_WEEK = SECONDS_IN_DAY * 7;
        const int SECONDS_IN_MONTH = SECONDS_IN_DAY * 30;
        const int SECONDS_IN_YEAR = SECONDS_IN_DAY * 365;
    public:
        ObjectProcessor() = default;

        void ReadFromFile(std::istream& input);

        SortedObjects GetSortedByNameData() const;
        SortedObjects GetSortedByTypeData() const;
        SortedObjects GetSortedByDistanceData() const;
        SortedObjects GetSortedByByTimeData() const;

        const ObjectData* GetObjectByName(std::string_view name) const;

    private:
        std::deque<ObjectData> objects_;
        ObjectMapByType object_map_by_type_;
        ObjectMapByName object_map_by_name_;

        ObjectData GetObjectFromLine(std::istream& input) const;
        std::string GetKeyForMap(std::string_view str) const;
        bool IsRussianLetter(unsigned char byte1, unsigned char byte2) const;
        double ConvertTime(std::chrono::system_clock::time_point time) const;
    };

} //namespace object_processor