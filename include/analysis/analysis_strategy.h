#ifndef NLPER_ANALYSIS_STRATEGY_H
#define NLPER_ANALYSIS_STRATEGY_H

#include "analysis/method_interface.h"
#include "nlper.pb.h"
#include "dict/dict_manager.h"

namespace nlper {
// 对输入query进行分析，
class AnalysisStrategy {
public:
    AnalysisStrategy();
    ~AnalysisStrategy();
    
    // 使用词典和配置初始化
    int init(DictMap* dict_map, const std::string& analysis_conf);
    // 运行Analysis的插件
    int run_strategy(const std::string& analysis_input_str, std::vector<AnalysisItem>& analysis_items);
    
    int destroy();
private:
    // 输入格式转换
    int json_parser(const std::string& analysis_input_str, std::vector<AnalysisItem>& analysis_items);
    
    // 分析插件列表
    std::vector<AnalysisMethodInterface*> _method_list;
    
    DictMap* _dict_map;
    DISALLOW_COPY_AND_ASSIGN(AnalysisStrategy);
};

} // namespace nlper

#endif //NLPER_ANALYSIS_STRATEGY_H
