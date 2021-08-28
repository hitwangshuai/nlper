#include "dict/dict_adapter.h"
#include "common/utils.h"

namespace nlper {

SemtopicAdapter::SemtopicAdapter() {
}

SemtopicAdapter::~SemtopicAdapter() {
}

int SemtopicAdapter::load(const std::string& path, const DictConfig& config) {
    SemtopicPack *p_semtopic_pack = new SemtopicPack();
    
    // 内部切词器
    p_semtopic_pack->tokenizer = NULL;
    p_semtopic_pack->tokenizer = new semtopic::SimpleTokenizer(path + "/vocab_info.txt");
    
    // LDA主题模型
    std::string lda_conf = "lda.conf";
    p_semtopic_pack->lda_engine = NULL;
    p_semtopic_pack->lda_engine = new semtopic::InferenceEngine(path, lda_conf, semtopic::SamplerType::MetropolisHastings);
    if (p_semtopic_pack->lda_engine == NULL)
    {
        FATAL_LOG("semtopic lda dict load error");
        return -1;
    } else {
        TRACE_LOG("semtopic  lda dict load success.");
    }
    
    // SLDA主题模型
    std::string slda_conf = "slda.conf";
    p_semtopic_pack->slda_engine = NULL;
    p_semtopic_pack->slda_engine = new semtopic::InferenceEngine(path, slda_conf, semtopic::SamplerType::MetropolisHastings);
    if (p_semtopic_pack->slda_engine == NULL)
    {
        FATAL_LOG("semtopic slda dict load error");
        return -1;
    } else {
        TRACE_LOG("semtopic slda dict load success.");
    }
    
    // TWE模型
    std::string emb_file = "twe_lda.model";
    p_semtopic_pack->twe = new semtopic::TopicalWordEmbedding(path, emb_file); 

    set_dict((void*)p_semtopic_pack);
    return 0;
}

int SemtopicAdapter::release() {
    void* dict = get_dict();
    if (dict != NULL) {
        SemtopicPack* p_semtopic_pack = static_cast<SemtopicPack*>(dict);
        delete p_semtopic_pack->tokenizer;
        p_semtopic_pack->tokenizer = NULL;
        delete p_semtopic_pack->lda_engine;
        p_semtopic_pack->lda_engine = NULL;
        delete p_semtopic_pack->slda_engine;
        p_semtopic_pack->slda_engine = NULL;
        delete p_semtopic_pack->twe;
        p_semtopic_pack->twe = NULL;
        delete p_semtopic_pack;
        set_dict(NULL);
    }
    return 0;
}

} // namespace nlper
