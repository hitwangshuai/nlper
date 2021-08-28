#ifndef NLPER_SEMTOPIC_STRATEGY_H
#define NLPER_SEMTOPIC_STRATEGY_H

#include "dict/dict_manager.h"
#include "analysis/analysis_strategy.h"
#include "common/utils.h"

namespace nlper {
//总体策略类
class SemtopicStrategy {
public:
    SemtopicStrategy();
    ~SemtopicStrategy();
    // 创建线程资源
    int create_resource(DictManager& dm, const std::string& conf_path);
    /// 释放线程资源
    int release_resource();
    // 策略运行接口
    int run_strategy(const std::string& analysis_input, NlperResult& result);
private:
    AnalysisStrategy _analysis;
    DISALLOW_COPY_AND_ASSIGN(SemtopicStrategy);
};

}

#endif  //NLPER_STRATEGY_H
