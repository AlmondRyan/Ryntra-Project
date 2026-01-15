
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
      "INT", "RETURN", "STRING", "IF", "ELSE", "BOOL", "TRUE", "FALSE", 
      "WHILE", "FOR", "PLUS", "MINUS", "INC", "DEC", "MULT", "DIV", "ASSIGN", 
      "GREATER", "LESS", "COND_EQUAL", "GREATER_EQ", "LESS_EQ", "LOGIC_AND", 
      "LOGIC_OR", "NOT", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "COMMA", "STRING_LITERAL", "IDENTIFIER", "INTEGER_LITERAL", "LINE_COMMENT", 
      "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'int'", "'return'", "'string'", "'if'", "'else'", "'bool'", "'true'", 
      "'false'", "'while'", "'for'", "'+'", "'-'", "'++'", "'--'", "'*'", 
      "'/'", "'='", "'>'", "'<'", "'=='", "'>='", "'<='", "'&&'", "'||'", 
      "'!'", "';'", "'('", "')'", "'{'", "'}'", "','"
    },
    std::vector<std::string>{
      "", "INT", "RETURN", "STRING", "IF", "ELSE", "BOOL", "TRUE", "FALSE", 
      "WHILE", "FOR", "PLUS", "MINUS", "INC", "DEC", "MULT", "DIV", "ASSIGN", 
      "GREATER", "LESS", "COND_EQUAL", "GREATER_EQ", "LESS_EQ", "LOGIC_AND", 
      "LOGIC_OR", "NOT", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "COMMA", "STRING_LITERAL", "IDENTIFIER", "INTEGER_LITERAL", "LINE_COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,36,220,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,
  	6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,
  	1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,15,
  	1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,21,
  	1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,23,1,24,1,24,1,25,1,25,1,26,1,26,
  	1,27,1,27,1,28,1,28,1,29,1,29,1,30,1,30,1,31,1,31,1,31,1,31,5,31,179,
  	8,31,10,31,12,31,182,9,31,1,31,1,31,1,32,1,32,5,32,188,8,32,10,32,12,
  	32,191,9,32,1,33,1,33,1,33,5,33,196,8,33,10,33,12,33,199,9,33,3,33,201,
  	8,33,1,34,1,34,1,34,1,34,5,34,207,8,34,10,34,12,34,210,9,34,1,34,1,34,
  	1,35,4,35,215,8,35,11,35,12,35,216,1,35,1,35,0,0,36,1,1,3,2,5,3,7,4,9,
  	5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,
  	35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,
  	29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,1,0,8,4,0,10,10,13,13,34,
  	34,92,92,7,0,34,34,92,92,98,98,102,102,110,110,114,114,116,116,3,0,65,
  	90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,1,0,49,57,1,0,48,57,2,0,
  	10,10,13,13,3,0,9,10,13,13,32,32,226,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,
  	0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,
  	17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,
  	0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,
  	0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,
  	49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,
  	0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,
  	0,0,71,1,0,0,0,1,73,1,0,0,0,3,77,1,0,0,0,5,84,1,0,0,0,7,91,1,0,0,0,9,
  	94,1,0,0,0,11,99,1,0,0,0,13,104,1,0,0,0,15,109,1,0,0,0,17,115,1,0,0,0,
  	19,121,1,0,0,0,21,125,1,0,0,0,23,127,1,0,0,0,25,129,1,0,0,0,27,132,1,
  	0,0,0,29,135,1,0,0,0,31,137,1,0,0,0,33,139,1,0,0,0,35,141,1,0,0,0,37,
  	143,1,0,0,0,39,145,1,0,0,0,41,148,1,0,0,0,43,151,1,0,0,0,45,154,1,0,0,
  	0,47,157,1,0,0,0,49,160,1,0,0,0,51,162,1,0,0,0,53,164,1,0,0,0,55,166,
  	1,0,0,0,57,168,1,0,0,0,59,170,1,0,0,0,61,172,1,0,0,0,63,174,1,0,0,0,65,
  	185,1,0,0,0,67,200,1,0,0,0,69,202,1,0,0,0,71,214,1,0,0,0,73,74,5,105,
  	0,0,74,75,5,110,0,0,75,76,5,116,0,0,76,2,1,0,0,0,77,78,5,114,0,0,78,79,
  	5,101,0,0,79,80,5,116,0,0,80,81,5,117,0,0,81,82,5,114,0,0,82,83,5,110,
  	0,0,83,4,1,0,0,0,84,85,5,115,0,0,85,86,5,116,0,0,86,87,5,114,0,0,87,88,
  	5,105,0,0,88,89,5,110,0,0,89,90,5,103,0,0,90,6,1,0,0,0,91,92,5,105,0,
  	0,92,93,5,102,0,0,93,8,1,0,0,0,94,95,5,101,0,0,95,96,5,108,0,0,96,97,
  	5,115,0,0,97,98,5,101,0,0,98,10,1,0,0,0,99,100,5,98,0,0,100,101,5,111,
  	0,0,101,102,5,111,0,0,102,103,5,108,0,0,103,12,1,0,0,0,104,105,5,116,
  	0,0,105,106,5,114,0,0,106,107,5,117,0,0,107,108,5,101,0,0,108,14,1,0,
  	0,0,109,110,5,102,0,0,110,111,5,97,0,0,111,112,5,108,0,0,112,113,5,115,
  	0,0,113,114,5,101,0,0,114,16,1,0,0,0,115,116,5,119,0,0,116,117,5,104,
  	0,0,117,118,5,105,0,0,118,119,5,108,0,0,119,120,5,101,0,0,120,18,1,0,
  	0,0,121,122,5,102,0,0,122,123,5,111,0,0,123,124,5,114,0,0,124,20,1,0,
  	0,0,125,126,5,43,0,0,126,22,1,0,0,0,127,128,5,45,0,0,128,24,1,0,0,0,129,
  	130,5,43,0,0,130,131,5,43,0,0,131,26,1,0,0,0,132,133,5,45,0,0,133,134,
  	5,45,0,0,134,28,1,0,0,0,135,136,5,42,0,0,136,30,1,0,0,0,137,138,5,47,
  	0,0,138,32,1,0,0,0,139,140,5,61,0,0,140,34,1,0,0,0,141,142,5,62,0,0,142,
  	36,1,0,0,0,143,144,5,60,0,0,144,38,1,0,0,0,145,146,5,61,0,0,146,147,5,
  	61,0,0,147,40,1,0,0,0,148,149,5,62,0,0,149,150,5,61,0,0,150,42,1,0,0,
  	0,151,152,5,60,0,0,152,153,5,61,0,0,153,44,1,0,0,0,154,155,5,38,0,0,155,
  	156,5,38,0,0,156,46,1,0,0,0,157,158,5,124,0,0,158,159,5,124,0,0,159,48,
  	1,0,0,0,160,161,5,33,0,0,161,50,1,0,0,0,162,163,5,59,0,0,163,52,1,0,0,
  	0,164,165,5,40,0,0,165,54,1,0,0,0,166,167,5,41,0,0,167,56,1,0,0,0,168,
  	169,5,123,0,0,169,58,1,0,0,0,170,171,5,125,0,0,171,60,1,0,0,0,172,173,
  	5,44,0,0,173,62,1,0,0,0,174,180,5,34,0,0,175,179,8,0,0,0,176,177,5,92,
  	0,0,177,179,7,1,0,0,178,175,1,0,0,0,178,176,1,0,0,0,179,182,1,0,0,0,180,
  	178,1,0,0,0,180,181,1,0,0,0,181,183,1,0,0,0,182,180,1,0,0,0,183,184,5,
  	34,0,0,184,64,1,0,0,0,185,189,7,2,0,0,186,188,7,3,0,0,187,186,1,0,0,0,
  	188,191,1,0,0,0,189,187,1,0,0,0,189,190,1,0,0,0,190,66,1,0,0,0,191,189,
  	1,0,0,0,192,201,5,48,0,0,193,197,7,4,0,0,194,196,7,5,0,0,195,194,1,0,
  	0,0,196,199,1,0,0,0,197,195,1,0,0,0,197,198,1,0,0,0,198,201,1,0,0,0,199,
  	197,1,0,0,0,200,192,1,0,0,0,200,193,1,0,0,0,201,68,1,0,0,0,202,203,5,
  	47,0,0,203,204,5,47,0,0,204,208,1,0,0,0,205,207,8,6,0,0,206,205,1,0,0,
  	0,207,210,1,0,0,0,208,206,1,0,0,0,208,209,1,0,0,0,209,211,1,0,0,0,210,
  	208,1,0,0,0,211,212,6,34,0,0,212,70,1,0,0,0,213,215,7,7,0,0,214,213,1,
  	0,0,0,215,216,1,0,0,0,216,214,1,0,0,0,216,217,1,0,0,0,217,218,1,0,0,0,
  	218,219,6,35,0,0,219,72,1,0,0,0,8,0,178,180,189,197,200,208,216,1,6,0,
  	0
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
