#pragma once

#include "object_processor.h"
#include <fstream>

namespace request_handler {
    class RequestHandler {
    public:
        RequestHandler(const object_processor::ObjectProcessor& object_processor);

        void OutPutSortedByNameData() const;
        void OutPutSortedByTypeData() const;
        void OutPutSortedByDistanceData() const;
        void OutPutSortedByTimeData() const;

    private:
        const object_processor::ObjectProcessor& db_;

        void OutPutObject(std::ostream& output,std::string_view name) const;
    };
} // namespace request_handler
