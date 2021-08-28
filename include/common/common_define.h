#ifndef NLPER_COMMON_DEFINE_H
#define NLPER_COMMON_DEFINE_H
    
#include <vector>
#include <string>
#include "json/json.h"
#include "semtopic/inference.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&); \
        TypeName(TypeName&&); \
        TypeName& operator=(const TypeName&); \
        TypeName& operator=(TypeName&&)

namespace nlper {

struct analysis_topic_t {
    std::vector<std::string> tokens; // 基于主题词表的切词
    std::vector<semtopic::Topic> lda_spase_topic_dist; // LDA的topic分布
    std::vector<semtopic::Topic> slda_spase_topic_dist; // SLDA的topic分布
    
    std::vector<float> lda_dense_topic_dist; // LDA的topic分布
    std::vector<float> slda_dense_topic_dist; // SLDA的topic分布
};

struct AnalysisItem{
	std::string id;
	int type;
    std::string query;
    analysis_topic_t topics_basic; // 主题分析相关
};

struct MatchItem {
	// 候选匹配项的分析结果
    AnalysisItem analysis_item;
    // 记录所有匹配算法的相似度
    std::vector<float> features;
    // 最终的打分
    float score;
};

typedef std::vector<MatchItem> MatchResult;

// 单项结果
struct NlperItem {
    std::string id;
    std::string query;
    float confidence;
    std::vector<float> matching_features;
    std::vector<std::string> matching_feature_names;
};

struct NlperResult {
    std::vector<AnalysisItem> analysis_items; // 目标分析项结果
    std::vector<NlperItem> match_items; // 候选匹配项结果
};

const unsigned MAX_TERM_COUNT = 10240;
const unsigned INITIAL_INDEX = 0xffff; 

} //namespace nlper

#endif  // NLPER_COMMON_DEFINE_H
