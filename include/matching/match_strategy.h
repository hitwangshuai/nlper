#ifndef NLPER_MATCH_STRATEGY_H
#define NLPER_MATCH_STRATEGY_H

#include <numeric>
#include <algorithm>
#include "nlper.pb.h"
#include "dict/dict_adapter.h"
#include "matching/matching_interface.h"
#include "dict/dict_manager.h"
#include "common/common_define.h"
#include "common/utils.h"

namespace nlper {
//match策略类, match模块的入口
class MatchStrategy {
public:
    MatchStrategy();
    ~MatchStrategy();
    // 初始化匹配特征
    int init_feature(const MatchConfig& match_config);
    // 初始化线程资源
    int init(DictMap* dict_map, const std::string& match_conf);
    int destroy();
    // 相似特征计算
    int compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates);
    // 计算匹配特征
    int compute(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates);
    // 返回结果填充
    int collect_result(const MatchResult& candidates, NlperResult& result);
    // debug打印最终结果信息
    int debug_result(const std::vector<AnalysisItem>& analysis_items, NlperResult& result);
    // 设置候选的query作为匹配信息
    int fill_query_info(const std::vector<AnalysisItem>& analysis_items, MatchResult& match_candidates);
    // 总策略流程
    int run_strategy(const std::vector<AnalysisItem>& analysis_items, NlperResult& result);
private:
    std::vector<MatchingInterface*> _feature_calculator;
    DictMap* _dict_map;
    std::vector<std::string> _feature_names;
};

} // namespace nlper

#endif  //NLPER_MATCH_STRATEGY_H
