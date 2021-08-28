#ifndef NLPER_MATCHING_INTERFACE_H
#define NLPER_MATCHING_INTERFACE_H

#include <vector>
#include <string>
#include "nlper.pb.h"
#include "common/common_define.h"
#include "dict/dict_adapter.h"
#include "dict/dual_dict_wrapper.h"
#include "common/utils.h"

namespace nlper {

class MatchingInterface {
//mathcing特征插件接口,继承类必须实现init,destroy和compute_similarity三个函数
public:
    MatchingInterface() {};
    virtual ~MatchingInterface() {};
    // 线程资源初始化
    virtual int init(DualDictWrapper* dict, const MatchingConfig& matching_config) = 0;
    // 释放线程资源
    virtual int destroy() = 0;
    virtual int compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) = 0;
    // 基类初始化
    int init_base(const std::string& feature_name, int output_num, float feature_weight){
        _feature_name = feature_name;
        _output_num = output_num;
		_feature_weight = feature_weight;
        return 0;
    }

    std::string feature_name(){
        return _feature_name;
    }

    int get_output_num(){
        return _output_num;
    }
	
	float get_feature_weight(){
		return _feature_weight;
	}

protected:
    void set_output_num(int output_num){
        _output_num = output_num;
    }

	void set_feature_weight(float feature_weight){
		_feature_weight = feature_weight;
	}
private:
    std::string _feature_name;
    // 特征值个数。一个matching插件可以有多个特征值; 
    // 当output_num=0时,该插件不输出特征值,只对候选query进行处理,如分词等
    int _output_num;
	// 当feature_weight=0时,该插件不做相似度强度贡献，只对候选query进行处理,如分词等
	float _feature_weight;
    DISALLOW_COPY_AND_ASSIGN(MatchingInterface);
};

} // namespace nlper

#endif  //NLPER_MATCHING_INTERFACE_H
