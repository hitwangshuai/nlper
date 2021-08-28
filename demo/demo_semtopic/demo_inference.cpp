#include "semtopic/inference.h"
#include "semtopic/tokenizer.h"
#include "semtopic/util.h"
#include <iostream>
#include <gflags/gflags.h>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using namespace semtopic; // no lint

DEFINE_string(model_dir, "./", "model directory");
DEFINE_string(conf_file, "lda.conf", "model configuration file");

// 打印文档的主题分布
void print_doc_topic_dist(const vector<Topic>& topics) {
    printf("Document Topic Distribution:\n");
    for (size_t i = 0; i < topics.size(); ++i) {
        printf("%d:%f ", topics[i].tid, topics[i].prob);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    google::SetVersionString("1.0.0.0");
    string usage = string("Usage: ./inference_demo --model_dir=\"PATH/TO/MODEL\" ") + 
                   string("--conf_file=\"lda.conf\" ");
    google::SetUsageMessage(usage);
    google::ParseCommandLineFlags(&argc, &argv, true);

    InferenceEngine engine(FLAGS_model_dir, FLAGS_conf_file, SamplerType::MetropolisHastings);
   
    std::string vocab_path = FLAGS_model_dir + "/vocab_info.txt";
    Tokenizer* tokenizer = new SimpleTokenizer(vocab_path);

    string line;
    vector<vector<string>> sentences;
    while (true) {
        cout << "请输入文档:" << endl;
        getline(cin, line);
        vector<string> input;
        tokenizer->tokenize(line, input);
        if (engine.model_type() == ModelType::LDA) {
            LDADoc doc;
            engine.infer(input, doc);
            vector<Topic> topics;
            doc.sparse_topic_dist(topics);
            print_doc_topic_dist(topics);
        } else if (engine.model_type() == ModelType::SLDA) {
            vector<string> sent;
            for (size_t i = 0; i < input.size(); ++i) {
                sent.emplace_back(input[i]);
                // 为了简化句子边界问题，以5-gram作为一个句子
                // 其中n不宜太大，否则会导致采样过程中数值计算精度下降
                if (sent.size() % 5 == 0) {
                    sentences.emplace_back(sent);
                    sent.clear();
                }
            }

            // 剩余单词作为一个句子
            if (sent.size() > 0) {
                sentences.emplace_back(sent);
            }

            SLDADoc doc;
            engine.infer(sentences, doc);
            vector<Topic> topics;
            doc.sparse_topic_dist(topics);
            print_doc_topic_dist(topics);
            sentences.clear();
        }
    }
        
    delete tokenizer;

    return 0;
}
