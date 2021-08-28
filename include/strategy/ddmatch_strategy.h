#ifndef NLPER_DDMATCH_STRATEGY_H
#define NLPER_DDMATCH_STRATEGY_H

#include "dict/dict_manager.h"
#include "analysis/analysis_strategy.h"
#include "matching/match_strategy.h"
#include "common/utils.h"

namespace nlper {
//总体策略类
class DDMatchStrategy {
public:
    DDMatchStrategy();
    ~DDMatchStrategy();
    // 创建线程资源
    int create_resource(DictManager& dm, const std::string& conf_path);
    /// 释放线程资源
    int release_resource();
    // 策略运行接口
    int run_strategy(const std::string& analysis_input, NlperResult& result);
private:
    AnalysisStrategy _analysis;
    MatchStrategy _match;
    DISALLOW_COPY_AND_ASSIGN(DDMatchStrategy);
};

}

#endif  //NLPER_STRATEGY_H
