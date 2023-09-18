#pragma once

#include "object_processor.h"
#include <fstream>

namespace request_handler {
    class RequestHandler {
    public:
        explicit RequestHandler(const object_processor::ObjectProcessor& object_processor);

        void OutputSortedByNameData(std::ofstream& output) const;
        void OutputSortedByTypeData(std::ofstream& output) const;
        void OutputSortedByDistanceData(std::ofstream& output) const;
        void OutputSortedByTimeData( std::ofstream& output) const;

    private:
        const object_processor::ObjectProcessor& db_;

        void OutputObject(std::ostream& output,std::string_view name) const;
    };
} // namespace request_handler
