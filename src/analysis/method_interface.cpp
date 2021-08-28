#include "analysis/method_interface.h"

namespace nlper {

int AnalysisMethodInterface::single_process(AnalysisItem& analysis_item) {
    return 0;
}

int AnalysisMethodInterface::method_process(std::vector<AnalysisItem>& analysis_items) {
    for (size_t j = 0; j < analysis_items.size(); j++) {
        AnalysisItem& analysis_item = analysis_items[j];
        if (single_process(analysis_item) != 0) {
            FATAL_LOG("single_process err");
            return -1;
        }
    }
    return 0;
}

} // namespace nlper
