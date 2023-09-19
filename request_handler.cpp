#include "request_handler.h"

#include <iomanip>

namespace request_handler {
    RequestHandler::RequestHandler(const object_processor::ObjectProcessor& object_processor)
    : db_(object_processor) {
    }

void RequestHandler::OutputSortedByNameData(std::ofstream& output) const {
    auto sorted_by_name = db_.GetSortedByNameData();
    for(const auto& [ch, list] : sorted_by_name) {
        if(!list.empty()) {
            output << "Буква "s << ch << '\n';
            for(const auto name : list) {
                OutputObject(output, name);
            }
            output << '\n';
        }
    }
}

    void RequestHandler::OutputSortedByTypeData(std::ofstream& output) const {
        auto sorted_by_name = db_.GetSortedByTypeData();
        for(const auto& [type, list] : sorted_by_name) {
            if(!list.empty()) {
                output << "Тип объекта - "s << type << '\n';
                for(const auto name : list) {
                    OutputObject(output, name);
                }
                output << '\n';
            }
        }
    }

    void RequestHandler::OutputSortedByDistanceData(std::ofstream& output) const {
        auto sorted_by_name = db_.GetSortedByDistanceData();
        for(const auto& [distance, list] : sorted_by_name) {
            if(!list.empty()) {
                output << "До "s << distance << " ед."s << '\n';
                for(const auto name : list) {
                    OutputObject(output, name);
                }
                output << '\n';
            }
        }
    }

    void RequestHandler::OutputSortedByTimeData(std::ofstream& output) const {
        auto sorted_by_name = db_.GetSortedByByTimeData();
        for(const auto& [data, list] : sorted_by_name) {
            if(!list.empty()) {
                output << data << '\n';
                for(const auto name : list) {
                    OutputObject(output, name);
                }
                output << '\n';
            }
        }
    }

    void RequestHandler::OutputObject(std::ostream& output,std::string_view name) const {
        const auto* object = db_.GetObjectByName(name);
        output << object->object_name << ' ';
        output << object->pos_x << ' ';
        output << object->pos_y << ' ';
        output << object->object_type << ' ';
        output << std::fixed << std::setprecision(2) << object->creation_time << '\n';
    }


} // namespace request_handler