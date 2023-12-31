#include "object_processor.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <locale>

#include <iostream>

namespace object_processor {
    using namespace std::literals;

    double ComputeDistance(double pos_x, double pos_y) {
        return std::sqrt(pos_x * pos_x + pos_y * pos_y);
    }

    void ObjectProcessor::ReadFromFile(std::istream& input) {
        while (!input.eof()) {
            std::string line;
            std::getline(input, line);
            if(line.empty()) {
                return;
            }
            std::istringstream stream(line);
            auto object = GetObjectFromLine(stream);
            if(object_map_by_name_.count(object.object_name) == 0) {
                objects_.push_back(std::move(object));
                object_map_by_name_[objects_.back().object_name] = &objects_.back();
                object_map_by_type_[objects_.back().object_type].insert(objects_.back().object_name);
            }
        }
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

    ObjectProcessor::SortedObjects ObjectProcessor::GetSortedByNameData() const {
        SortedObjects result;
        for(const auto& [str, _] : object_map_by_name_) {
            std::string key = GetKeyForMap(str);
            result[key].insert(str);
        }
        return result;
    }

    ObjectProcessor::SortedObjects ObjectProcessor::GetSortedByTypeData() const {
        SortedObjects result;
        std::set<std::string_view> other;
        for(const auto& [type, list_of_obj] : object_map_by_type_) {
            object_map_by_type_.at(type).size() >= MIN_COUNT_FOR_GROUP ? result[type].insert(list_of_obj.begin(), list_of_obj.end()) : other.insert(list_of_obj.begin(), list_of_obj.end());
        }
        if(!other.empty()) {
            result["Разное"s] = std::move(other);
        }
        return result;
    }

    ObjectProcessor::SortedObjects ObjectProcessor::GetSortedByDistanceData() const {
        SortedObjects result;
        std::vector<std::pair<std::string_view, double>> name_and_distance;
        name_and_distance.reserve(object_map_by_name_.size());

        for(const auto& [name, obj] : object_map_by_name_) {
            name_and_distance.emplace_back(name, ComputeDistance(obj->pos_x, obj->pos_y));
        }

        std::sort(name_and_distance.begin(), name_and_distance.end(), [](const auto& lhs, const auto& rhs){
            return lhs.second < rhs.second;
        });

        for(const auto& [name, distance] : name_and_distance) {
            if(distance < HUNDRED) {
                result[std::to_string(HUNDRED)].insert(name);
                continue;
            }
            if(distance >= HUNDRED && distance < THOUSAND) {
                result[std::to_string(THOUSAND)].insert(name);
                continue;
            }
            if(distance >= THOUSAND && distance < TEN_THOUSAND) {
                result[std::to_string(TEN_THOUSAND)].insert(name);
                continue;
            }
            result["Слишком далеко"s].insert(name);
        }
        return result;
    }

    ObjectProcessor::SortedObjects ObjectProcessor::GetSortedByByTimeData() const {
        SortedObjects result;

        std::vector<std::pair<std::string_view, double>> name_and_time;
        name_and_time.reserve(object_map_by_name_.size());

        for(const auto& [name, obj] : object_map_by_name_) {
            name_and_time.emplace_back(name, obj->creation_time);
        }

        std::sort(name_and_time.begin(), name_and_time.end(), [](const auto& lhs, const auto& rhs){
            return lhs.second > rhs.second;
        });

        auto current_time = std::chrono::system_clock::now();

        for(const auto& [name, time] : name_and_time) {
            double time_diff = ConvertTime(current_time) - time;

            if(time_diff < SECONDS_IN_DAY) {
                result["Сегодня"s].insert(name);
                continue;
            }
            if(time_diff >= SECONDS_IN_DAY && time_diff < SECONDS_IN_WEEK) {
                result["Вчера"s].insert(name);
                continue;
            }
            if(time_diff >= SECONDS_IN_DAY && time_diff < SECONDS_IN_WEEK) {
                result["На этой неделе"s].insert(name);
                continue;
            }
            if(time_diff >= SECONDS_IN_WEEK && time_diff < SECONDS_IN_MONTH) {
                result["В этом месяце"s].insert(name);
                continue;
            }
            if(time_diff >= SECONDS_IN_MONTH && time_diff < SECONDS_IN_YEAR) {
                result["В этом году"s].insert(name);
                continue;
            }
            result["Ранее"s].insert(name);
        }
        return result;
    }

    const ObjectData* ObjectProcessor::GetObjectByName(std::string_view name) const {
        return object_map_by_name_.at(name);
    }

    std::string ObjectProcessor::GetKeyForMap(std::string_view str) const {

        std::string result;
        auto byte1 = static_cast<unsigned char>(str[0]);
        if(byte1 != 208 && byte1 != 209) {
            result.push_back('#');
            return result;
        }
        auto byte2 = static_cast<unsigned char>(str[1]);
        if(IsRussianLetter(byte1, byte2)) {
            result.reserve(2);
            result.push_back(byte1);
            result.push_back(byte2);
            return result;
        } else {
            result.push_back('#');
            return result;
        }
    }

    bool ObjectProcessor::IsRussianLetter(unsigned char byte1, unsigned char byte2) const {
        if(byte1 == 208) {
            return byte2 >= 144 && byte2 <= 191;
        } else if(byte1 == 209) {
            return (byte2 >= 128 && byte2 <= 142) || byte2 == 145;
        }
        return false;
    }

    double ObjectProcessor::ConvertTime(std::chrono::system_clock::time_point time) const {
        std::chrono::duration<double> result = time.time_since_epoch();
        return result.count();
    }

} //namespace object_processor