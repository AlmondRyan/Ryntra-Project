
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2


#include "RyntraLexer.h"


using namespace antlr4;

using namespace Ryntra::antlr;


using namespace antlr4;

namespace {

struct RyntraLexerStaticData final {
  RyntraLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  RyntraLexerStaticData(const RyntraLexerStaticData&) = delete;
  RyntraLexerStaticData(RyntraLexerStaticData&&) = delete;
  RyntraLexerStaticData& operator=(const RyntraLexerStaticData&) = delete;
  RyntraLexerStaticData& operator=(RyntraLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ryntralexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<RyntraLexerStaticData> ryntralexerLexerStaticData = nullptr;

void ryntralexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ryntralexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(ryntralexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<RyntraLexerStaticData>(
    std::vector<std::string>{
      "INT", "RETURN", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "STRING_LITERAL", "IDENTIFIER", "LINE_COMMENT", "WS", "COMMA", "ASSIGN", 
      "INTEGER_LITERAL"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'int'", "'return'", "';'", "'('", "')'", "'{'", "'}'", "", "", 
      "", "", "','", "'='"
    },
    std::vector<std::string>{
      "", "INT", "RETURN", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "STRING_LITERAL", "IDENTIFIER", "LINE_COMMENT", "WS", "COMMA", "ASSIGN", 
      "INTEGER_LITERAL"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,14,100,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,1,0,
  	1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,
  	5,1,6,1,6,1,7,1,7,1,7,1,7,5,7,55,8,7,10,7,12,7,58,9,7,1,7,1,7,1,8,1,8,
  	5,8,64,8,8,10,8,12,8,67,9,8,1,9,1,9,1,9,1,9,5,9,73,8,9,10,9,12,9,76,9,
  	9,1,9,1,9,1,10,4,10,81,8,10,11,10,12,10,82,1,10,1,10,1,11,1,11,1,12,1,
  	12,1,13,1,13,1,13,5,13,94,8,13,10,13,12,13,97,9,13,3,13,99,8,13,0,0,14,
  	1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,
  	1,0,8,4,0,10,10,13,13,34,34,92,92,7,0,34,34,92,92,98,98,102,102,110,110,
  	114,114,116,116,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,2,
  	0,10,10,13,13,3,0,9,10,13,13,32,32,1,0,49,57,1,0,48,57,106,0,1,1,0,0,
  	0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,
  	0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,
  	0,0,25,1,0,0,0,0,27,1,0,0,0,1,29,1,0,0,0,3,33,1,0,0,0,5,40,1,0,0,0,7,
  	42,1,0,0,0,9,44,1,0,0,0,11,46,1,0,0,0,13,48,1,0,0,0,15,50,1,0,0,0,17,
  	61,1,0,0,0,19,68,1,0,0,0,21,80,1,0,0,0,23,86,1,0,0,0,25,88,1,0,0,0,27,
  	98,1,0,0,0,29,30,5,105,0,0,30,31,5,110,0,0,31,32,5,116,0,0,32,2,1,0,0,
  	0,33,34,5,114,0,0,34,35,5,101,0,0,35,36,5,116,0,0,36,37,5,117,0,0,37,
  	38,5,114,0,0,38,39,5,110,0,0,39,4,1,0,0,0,40,41,5,59,0,0,41,6,1,0,0,0,
  	42,43,5,40,0,0,43,8,1,0,0,0,44,45,5,41,0,0,45,10,1,0,0,0,46,47,5,123,
  	0,0,47,12,1,0,0,0,48,49,5,125,0,0,49,14,1,0,0,0,50,56,5,34,0,0,51,55,
  	8,0,0,0,52,53,5,92,0,0,53,55,7,1,0,0,54,51,1,0,0,0,54,52,1,0,0,0,55,58,
  	1,0,0,0,56,54,1,0,0,0,56,57,1,0,0,0,57,59,1,0,0,0,58,56,1,0,0,0,59,60,
  	5,34,0,0,60,16,1,0,0,0,61,65,7,2,0,0,62,64,7,3,0,0,63,62,1,0,0,0,64,67,
  	1,0,0,0,65,63,1,0,0,0,65,66,1,0,0,0,66,18,1,0,0,0,67,65,1,0,0,0,68,69,
  	5,47,0,0,69,70,5,47,0,0,70,74,1,0,0,0,71,73,8,4,0,0,72,71,1,0,0,0,73,
  	76,1,0,0,0,74,72,1,0,0,0,74,75,1,0,0,0,75,77,1,0,0,0,76,74,1,0,0,0,77,
  	78,6,9,0,0,78,20,1,0,0,0,79,81,7,5,0,0,80,79,1,0,0,0,81,82,1,0,0,0,82,
  	80,1,0,0,0,82,83,1,0,0,0,83,84,1,0,0,0,84,85,6,10,0,0,85,22,1,0,0,0,86,
  	87,5,44,0,0,87,24,1,0,0,0,88,89,5,61,0,0,89,26,1,0,0,0,90,99,5,48,0,0,
  	91,95,7,6,0,0,92,94,7,7,0,0,93,92,1,0,0,0,94,97,1,0,0,0,95,93,1,0,0,0,
  	95,96,1,0,0,0,96,99,1,0,0,0,97,95,1,0,0,0,98,90,1,0,0,0,98,91,1,0,0,0,
  	99,28,1,0,0,0,8,0,54,56,65,74,82,95,98,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ryntralexerLexerStaticData = std::move(staticData);
}

}

RyntraLexer::RyntraLexer(CharStream *input) : Lexer(input) {
  RyntraLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ryntralexerLexerStaticData->atn, ryntralexerLexerStaticData->decisionToDFA, ryntralexerLexerStaticData->sharedContextCache);
}

RyntraLexer::~RyntraLexer() {
  delete _interpreter;
}

std::string RyntraLexer::getGrammarFileName() const {
  return "Ryntra.g4";
}

const std::vector<std::string>& RyntraLexer::getRuleNames() const {
  return ryntralexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& RyntraLexer::getChannelNames() const {
  return ryntralexerLexerStaticData->channelNames;
}

const std::vector<std::string>& RyntraLexer::getModeNames() const {
  return ryntralexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& RyntraLexer::getVocabulary() const {
  return ryntralexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView RyntraLexer::getSerializedATN() const {
  return ryntralexerLexerStaticData->serializedATN;
}

const atn::ATN& RyntraLexer::getATN() const {
  return *ryntralexerLexerStaticData->atn;
}




void RyntraLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ryntralexerLexerInitialize();
#else
  ::antlr4::internal::call_once(ryntralexerLexerOnceFlag, ryntralexerLexerInitialize);
#endif
}
