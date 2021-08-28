#include "analysis/method_semtopic.h"
#include <exception>

namespace nlper {

AnalysisSemtopic::AnalysisSemtopic(){
    _p_semtopic_pack = NULL;
}

AnalysisSemtopic::~AnalysisSemtopic(){
    destroy();
}

int AnalysisSemtopic::init(DualDictWrapper* dict, const AnalysisMethodConfig& analysis_method)
{
    _p_semtopic_pack = (SemtopicPack*)dict->get_dict();
    set_method_name(analysis_method.name());
    set_method_type(analysis_method.type());
    set_method_level(analysis_method.level());
    TRACE_LOG("init semtopic success");
    return 0;
}

int AnalysisSemtopic::init(std::vector<DualDictWrapper*>& dicts, const AnalysisMethodConfig& analysis_method)
{
    if (dicts.size() == 0) {
        FATAL_LOG("semtopic_method init error");
        return -1;    
    }

    _p_semtopic_pack = (SemtopicPack*)dicts[0]->get_dict();
    set_method_name(analysis_method.name());
    set_method_type(analysis_method.type());
    set_method_level(analysis_method.level());
    TRACE_LOG("init semtopic success");
    return 0;
}

int AnalysisSemtopic::destroy(){
    return 0;
}

int AnalysisSemtopic::single_process(AnalysisItem& analysis_item) {
    float time_use;
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);

    // 内部分词,只提取模型词表内有的词
    std::vector<std::string> input;
    _p_semtopic_pack->tokenizer->tokenize(analysis_item.query, analysis_item.topics_basic.tokens);

    // LDA主题分析
    semtopic::LDADoc lda_doc;
    _p_semtopic_pack->lda_engine->infer(analysis_item.topics_basic.tokens, lda_doc);
    lda_doc.sparse_topic_dist(analysis_item.topics_basic.lda_spase_topic_dist);
    lda_doc.dense_topic_dist(analysis_item.topics_basic.lda_dense_topic_dist);
    
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
    DEBUG_LOG("Semtopic used_time=%.2fms", time_use);

    return 0;
};

} // namespace nlper
