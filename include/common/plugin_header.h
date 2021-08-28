#ifndef NLPER_PLUGIN_HEADER_H
#define NLPER_PLUGIN_HEADER_H

#include "common/plugin_factory.h"

// dict
#include "dict/dict_adapter.h"

// Analysis
#include "analysis/method_semtopic.h"

// MATCHING
#include "matching/lexical/contain_sim.h"
#include "matching/lexical/jaccard_sim.h"
#include "matching/semantic/semtopic_qd_sim.h"
#include "matching/semantic/semtopic_dd_sim.h"

// REQUEST POSTPROCESS
#include "server/qdmatch_preprocessor.h"
#include "server/ddmatch_preprocessor.h"
#include "server/semtopic_preprocessor.h"

#include "server/qdmatch_postprocessor.h"
#include "server/ddmatch_postprocessor.h"
#include "server/semtopic_postprocessor.h"

// DICT
REGISTER_PLUGIN(String2FloatAdapter);
REGISTER_PLUGIN(String2IntAdapter);
REGISTER_PLUGIN(String2StringAdapter);
REGISTER_PLUGIN(SemtopicAdapter);

// ANALYSIS
REGISTER_PLUGIN(AnalysisSemtopic);

// MATCHING
REGISTER_PLUGIN(ContainSimilarity);
REGISTER_PLUGIN(JaccardSimilarity);
REGISTER_PLUGIN(SemtopicQDSimilarity);
REGISTER_PLUGIN(SemtopicDDSimilarity);

// REQUEST POSTPROCESS
REGISTER_PLUGIN(QDMatchPreprocessor);
REGISTER_PLUGIN(DDMatchPreprocessor);
REGISTER_PLUGIN(SemtopicPreprocessor);

REGISTER_PLUGIN(QDMatchPostprocessor);
REGISTER_PLUGIN(DDMatchPostprocessor);
REGISTER_PLUGIN(SemtopicPostprocessor);

#endif  // NLPER_PLUGIN_HEADER_H
