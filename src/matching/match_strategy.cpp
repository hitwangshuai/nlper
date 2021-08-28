#include <sstream>
#include "matching/match_strategy.h"
#include "common/plugin_factory.h"

namespace nlper {

MatchStrategy::MatchStrategy() {
}

MatchStrategy::~MatchStrategy() {
    if (destroy() != 0) {
        FATAL_LOG("release match stategy error");
    }
}

// 初始化匹配特征计算实例
int MatchStrategy::init_feature(const MatchConfig& match_config) {
    // 遍历每个匹配特征的配置完成实例化
	for (int i = 0; i < match_config.matching_config_size(); i++) {
        const MatchingConfig& matching_config = match_config.matching_config(i);
        std::string fea_type = matching_config.type();
        std::string fea_name = matching_config.name();
        int output_num = matching_config.output_num();
        float feature_weight = matching_config.feature_weight();

		// 获取匹配插件
        MatchingInterface* tmp_fea = 
                static_cast<MatchingInterface*>(PLUGIN_FACTORY.create_plugin(fea_type));
        if (tmp_fea == NULL) {
            FATAL_LOG("can't find feature_type:%s", fea_type.c_str());
            return -1;
        }
        
		// 获取全局字典
        DualDictWrapper* dict_ptr = NULL;
        if (matching_config.has_using_dict_name()) {
            std::string matching_dict_name = matching_config.using_dict_name();
            if (_dict_map->count(matching_dict_name) < 1) {
                FATAL_LOG("using dict %s that does not exist", matching_dict_name.c_str());
                return -1;
            }
            dict_ptr = (*_dict_map)[matching_dict_name];
        }
        
		// 基类成员初始化
        tmp_fea->init_base(fea_name, output_num, feature_weight);
        // 子类成员初始化
        if (tmp_fea->init(dict_ptr, matching_config) != 0) {
            FATAL_LOG("init feature error %s", fea_name.c_str());
            return -1;
        }
        TRACE_LOG("create feature %s success", fea_name.c_str());
        _feature_calculator.emplace_back(tmp_fea);

		// 如果该匹配特征插件的特征值个数大于1,则特征名用后缀区分开
        if (output_num > 1) {
            for (int i = 0; i < output_num; i++){
                std::stringstream ss;
                ss << fea_name << "-" << i;
                _feature_names.emplace_back(ss.str());
            }
        } else if (output_num > 0) {
            _feature_names.emplace_back(fea_name);
        }
    }

    return 0;
}

int MatchStrategy::init(DictMap* dict_map, const std::string& match_conf) {
    _dict_map = dict_map;
    MatchConfig match_config;
    if (load_config_from_file(match_conf, match_config) != 0) {
        return -1;
    }
    // 初始化匹配特征插件
    if (init_feature(match_config) != 0) {
        FATAL_LOG("init matching feature error");
        return -1;
    }

    return 0;
}

int MatchStrategy::destroy() {
    std::vector<MatchingInterface*>::iterator it;
    int i = 0;
    for (it = _feature_calculator.begin(); it != _feature_calculator.end(); ++it, ++i) {
        if ((*it)->destroy() != 0) {
            FATAL_LOG("feature %s destroy error", ((*it)->feature_name()).c_str());
            return -1;
        }
        delete *it;
    }
    _feature_calculator.clear();

    return 0;
}

// 相似特征计算
int MatchStrategy::compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) {
	// 每个匹配算法走一遍
    for (size_t i = 0; i < _feature_calculator.size(); i++) {
        // 每个算法计算跟所有候选的相似度
		if (_feature_calculator[i]->compute_similarity(analysis_items, candidates) != 0) {
            FATAL_LOG("feature %s compute error", (_feature_calculator[i]->feature_name()).c_str());
            return -1;
        }
    }
    
	return 0;
}

// 计算匹配特征
int MatchStrategy::compute(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) {
    // 计算相似度特征
    if (compute_similarity(analysis_items, candidates) != 0) {
        return -1;
    }
    
	return 0;
}

// debug打印最终结果信息
int MatchStrategy::debug_result(const std::vector<AnalysisItem>& analysis_items, NlperResult& result) {
    std::string query;
    for (size_t i = 0; i < analysis_items.size(); i++) {
        if (analysis_items[i].type != 0) {
            continue;
        }
        query = analysis_items[i].query;
        break;
    }
    DEBUG_LOG("aim_query: %s", query.c_str());
    for (size_t j = 0; j < result.match_items.size(); j++) {
        DEBUG_LOG("\tcand_query:%s", result.match_items[j].query.c_str());
        DEBUG_LOG("\tcand_confidence:%f", result.match_items[j].confidence);
    }
    
	return 0;
}

// 把得分高的候选排在前面
bool candidate_cmp(const MatchItem& item1, const MatchItem& item2) {
    if (item1.score > item2.score) {
        return true;
    }
    
	return false;
}
// 设置候选的query作为匹配信息
int MatchStrategy::fill_query_info(const std::vector<AnalysisItem>& analysis_items, MatchResult& match_candidates) {
    size_t cand_cnt = analysis_items.size();
    match_candidates.resize(cand_cnt - 1);
	// 忽略第一项的目标query项
    for (size_t i = 1; i < cand_cnt; i++) {
        // fill info used for matching
        match_candidates[i - 1].analysis_item = analysis_items[i];
        match_candidates[i - 1].features.clear();
    }
    
	return 0;
}

// 将MatchResult结构转化为系统的输出结构NlperResult
int MatchStrategy::collect_result(const MatchResult& candidates, NlperResult& result) {
    for (size_t i = 0; i < candidates.size(); i++) {
        NlperItem item;
        const AnalysisItem& analysis_item = candidates[i].analysis_item;
        item.id = analysis_item.id;
        item.query = analysis_item.query;
        item.confidence = candidates[i].score;
        item.matching_features = candidates[i].features;
        item.matching_feature_names = _feature_names;
        result.match_items.emplace_back(item);
    }
    
	return 0;
}

// 匹配策略入口
int MatchStrategy::run_strategy(const std::vector<AnalysisItem>& analysis_items, NlperResult& result) {
    float time_use = 0; // 毫秒
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    if (analysis_items.size() < 2) {
        return 0;
    }

	// 候选填充
    MatchResult trans_candidates;
    fill_query_info(analysis_items, trans_candidates);
    if (trans_candidates.size() == 0) {
        return 0;
    }
	
	// 相似度特征计算
    if (compute(analysis_items, trans_candidates) != 0) {
        return -1;
    }
	
	// 综合score计算
    for (size_t i = 0; i < trans_candidates.size(); i++) {
		std::vector<float> features = trans_candidates[i].features;
		float score = 0.0;
		for (size_t j = 0; j < features.size(); j++) {
			score += features[j];
		}
		trans_candidates[i].score = score;
    }
    
	// 结果排序
    std::sort(trans_candidates.begin(), trans_candidates.end(), candidate_cmp);

    // 结果填充
    collect_result(trans_candidates, result);

    // 打印最终结果信息
    debug_result(analysis_items, result);

    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
    DEBUG_LOG("matching_item_num=%d; matching_time=%.2fms;", trans_candidates.size(), time_use);

    return 0;
}

} // namespace nlper
