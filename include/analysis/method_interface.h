#ifndef NLPER_ANALYSIS_METHOD_INTERFACE_H
#define NLPER_ANALYSIS_METHOD_INTERFACE_H

#include <vector>
#include <string>
#include <set>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <list>

#include "common/common_define.h"
#include "nlper.pb.h"
#include "dict/dict_adapter.h"
#include "dict/dual_dict_wrapper.h"

namespace nlper {

class AnalysisMethodInterface {
public:
    AnalysisMethodInterface() {
    };
    virtual ~AnalysisMethodInterface() {
    };

    virtual int init(DualDictWrapper* dict, const AnalysisMethodConfig& analysis_method) = 0;
    virtual int init(std::vector<DualDictWrapper*>& dicts, const AnalysisMethodConfig& analysis_method) = 0;
    virtual int destroy() = 0;
    
    // 处理query(可能包含多个，如改写或扩展会增加query)
    virtual int method_process(std::vector<AnalysisItem>& analysis_items);

    // 处理单个query
    virtual int single_process(AnalysisItem& analysis_item);
    
    std::string get_method_name() {
        return _method_name;
    }

    std::string get_method_type() {
        return _method_type;
    }

    int get_method_level() {
        return _method_level;
    }
protected:
    void set_method_name(const std::string& method_name) {
        _method_name = method_name;
    }

    void set_method_type(const std::string& method_type) {
        _method_type = method_type;
    }
    
    void set_method_level(const int method_level) {
        _method_level = method_level;
    }
private:
    std::string _method_name;
    std::string _method_type;
    int _method_level;
    DISALLOW_COPY_AND_ASSIGN(AnalysisMethodInterface);
};

} // namespace nlper

#endif //NLPER_ANALYSIS_METHOD_INTERFACE_H
