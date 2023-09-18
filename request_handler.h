#pragma once

#include "object_processor.h"
#include <fstream>

namespace request_handler {
    class RequestHandler {
    public:
        RequestHandler(const object_processor::ObjectProcessor& object_processor);

        void OutputSortedByNameData() const;
        void OutputSortedByTypeData() const;
        void OutputSortedByDistanceData() const;
        void OutputSortedByTimeData() const;

    private:
        const object_processor::ObjectProcessor& db_;

        void OutputObject(std::ostream& output,std::string_view name) const;
    };
} // namespace request_handler
