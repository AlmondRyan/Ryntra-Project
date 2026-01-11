
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
      "INT", "RETURN", "PLUS", "MINUS", "MULT", "DIV", "ASSIGN", "SEMICOLON", 
      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "STRING_LITERAL", 
      "IDENTIFIER", "INTEGER_LITERAL", "LINE_COMMENT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'int'", "'return'", "'+'", "'-'", "'*'", "'/'", "'='", "';'", 
      "'('", "')'", "'{'", "'}'", "','"
    },
    std::vector<std::string>{
      "", "INT", "RETURN", "PLUS", "MINUS", "MULT", "DIV", "ASSIGN", "SEMICOLON", 
      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "STRING_LITERAL", 
      "IDENTIFIER", "INTEGER_LITERAL", "LINE_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,18,116,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,
  	1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,13,1,13,5,13,75,8,13,10,
  	13,12,13,78,9,13,1,13,1,13,1,14,1,14,5,14,84,8,14,10,14,12,14,87,9,14,
  	1,15,1,15,1,15,5,15,92,8,15,10,15,12,15,95,9,15,3,15,97,8,15,1,16,1,16,
  	1,16,1,16,5,16,103,8,16,10,16,12,16,106,9,16,1,16,1,16,1,17,4,17,111,
  	8,17,11,17,12,17,112,1,17,1,17,0,0,18,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,
  	8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,1,0,8,4,
  	0,10,10,13,13,34,34,92,92,7,0,34,34,92,92,98,98,102,102,110,110,114,114,
  	116,116,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,1,0,49,57,
  	1,0,48,57,2,0,10,10,13,13,3,0,9,10,13,13,32,32,122,0,1,1,0,0,0,0,3,1,
  	0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,
  	15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,
  	0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,
  	0,1,37,1,0,0,0,3,41,1,0,0,0,5,48,1,0,0,0,7,50,1,0,0,0,9,52,1,0,0,0,11,
  	54,1,0,0,0,13,56,1,0,0,0,15,58,1,0,0,0,17,60,1,0,0,0,19,62,1,0,0,0,21,
  	64,1,0,0,0,23,66,1,0,0,0,25,68,1,0,0,0,27,70,1,0,0,0,29,81,1,0,0,0,31,
  	96,1,0,0,0,33,98,1,0,0,0,35,110,1,0,0,0,37,38,5,105,0,0,38,39,5,110,0,
  	0,39,40,5,116,0,0,40,2,1,0,0,0,41,42,5,114,0,0,42,43,5,101,0,0,43,44,
  	5,116,0,0,44,45,5,117,0,0,45,46,5,114,0,0,46,47,5,110,0,0,47,4,1,0,0,
  	0,48,49,5,43,0,0,49,6,1,0,0,0,50,51,5,45,0,0,51,8,1,0,0,0,52,53,5,42,
  	0,0,53,10,1,0,0,0,54,55,5,47,0,0,55,12,1,0,0,0,56,57,5,61,0,0,57,14,1,
  	0,0,0,58,59,5,59,0,0,59,16,1,0,0,0,60,61,5,40,0,0,61,18,1,0,0,0,62,63,
  	5,41,0,0,63,20,1,0,0,0,64,65,5,123,0,0,65,22,1,0,0,0,66,67,5,125,0,0,
  	67,24,1,0,0,0,68,69,5,44,0,0,69,26,1,0,0,0,70,76,5,34,0,0,71,75,8,0,0,
  	0,72,73,5,92,0,0,73,75,7,1,0,0,74,71,1,0,0,0,74,72,1,0,0,0,75,78,1,0,
  	0,0,76,74,1,0,0,0,76,77,1,0,0,0,77,79,1,0,0,0,78,76,1,0,0,0,79,80,5,34,
  	0,0,80,28,1,0,0,0,81,85,7,2,0,0,82,84,7,3,0,0,83,82,1,0,0,0,84,87,1,0,
  	0,0,85,83,1,0,0,0,85,86,1,0,0,0,86,30,1,0,0,0,87,85,1,0,0,0,88,97,5,48,
  	0,0,89,93,7,4,0,0,90,92,7,5,0,0,91,90,1,0,0,0,92,95,1,0,0,0,93,91,1,0,
  	0,0,93,94,1,0,0,0,94,97,1,0,0,0,95,93,1,0,0,0,96,88,1,0,0,0,96,89,1,0,
  	0,0,97,32,1,0,0,0,98,99,5,47,0,0,99,100,5,47,0,0,100,104,1,0,0,0,101,
  	103,8,6,0,0,102,101,1,0,0,0,103,106,1,0,0,0,104,102,1,0,0,0,104,105,1,
  	0,0,0,105,107,1,0,0,0,106,104,1,0,0,0,107,108,6,16,0,0,108,34,1,0,0,0,
  	109,111,7,7,0,0,110,109,1,0,0,0,111,112,1,0,0,0,112,110,1,0,0,0,112,113,
  	1,0,0,0,113,114,1,0,0,0,114,115,6,17,0,0,115,36,1,0,0,0,8,0,74,76,85,
  	93,96,104,112,1,6,0,0
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
