
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2


#include "RyntraListener.h"
#include "RyntraVisitor.h"

#include "RyntraParser.h"


using namespace antlrcpp;
using namespace Ryntra::antlr;

using namespace antlr4;

namespace {

struct RyntraParserStaticData final {
  RyntraParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  RyntraParserStaticData(const RyntraParserStaticData&) = delete;
  RyntraParserStaticData(RyntraParserStaticData&&) = delete;
  RyntraParserStaticData& operator=(const RyntraParserStaticData&) = delete;
  RyntraParserStaticData& operator=(RyntraParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ryntraParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<RyntraParserStaticData> ryntraParserStaticData = nullptr;

void ryntraParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ryntraParserStaticData != nullptr) {
    return;
  }
#else
  assert(ryntraParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<RyntraParserStaticData>(
    std::vector<std::string>{
      "program", "functionDefinition", "parameterList", "block", "typeSpecifier", 
      "variableDeclaration", "statement", "returnStatement", "ifStatement", 
      "elseClause", "whileStatement", "forStatement", "breakStatement", 
      "continueStatement", "functionCall", "argumentList", "assignment", 
      "expression", "logicalOrExpression", "logicalAndExpression", "inclusiveOrExpression", 
      "exclusiveOrExpression", "andExpression", "equalityExpression", "relationalExpression", 
      "shiftExpression", "additiveExpression", "multiplicativeExpression", 
      "unaryExpression", "postfixExpression", "primaryExpression", "literal"
    },
    std::vector<std::string>{
      "", "'int'", "'return'", "'string'", "'if'", "'else'", "'bool'", "'true'", 
      "'false'", "'while'", "'for'", "'break'", "'continue'", "'long'", 
      "'float'", "'double'", "'+'", "'-'", "'++'", "'--'", "'*'", "'/'", 
      "'%'", "'='", "'+='", "'-='", "'*='", "'/='", "'%='", "'&='", "'|='", 
      "'^='", "'<<='", "'>>='", "'>'", "'<'", "'=='", "'!='", "'>='", "'<='", 
      "'&&'", "'||'", "'!'", "';'", "'('", "')'", "'{'", "'}'", "'['", "']'", 
      "','", "", "", "", "", "", "", "'&'", "'|'", "'^'", "'~'", "'<<'", 
      "'>>'"
    },
    std::vector<std::string>{
      "", "INT", "RETURN", "STRING", "IF", "ELSE", "BOOL", "TRUE", "FALSE", 
      "WHILE", "FOR", "BREAK", "CONTINUE", "LONG", "FLOAT", "DOUBLE", "PLUS", 
      "MINUS", "INC", "DEC", "MULT", "DIV", "MOD", "ASSIGN", "ADD_ASSIGN", 
      "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", 
      "OR_ASSIGN", "XOR_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "GREATER", 
      "LESS", "COND_EQUAL", "NOT_EQUAL", "GREATER_EQ", "LESS_EQ", "LOGIC_AND", 
      "LOGIC_OR", "NOT", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "LBRACKET", "RBRACKET", "COMMA", "STRING_LITERAL", "IDENTIFIER", "INTEGER_LITERAL", 
      "FLOAT_LITERAL", "LINE_COMMENT", "WS", "BIT_AND", "BIT_OR", "BIT_XOR", 
      "BIT_NOT", "LSHIFT", "RSHIFT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,62,332,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,1,0,4,0,66,8,0,11,0,12,0,67,1,0,1,0,
  	1,1,1,1,1,1,1,1,3,1,76,8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,5,2,87,
  	8,2,10,2,12,2,90,9,2,1,3,1,3,5,3,94,8,3,10,3,12,3,97,9,3,1,3,1,3,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,109,8,4,1,5,1,5,1,5,1,5,1,5,3,5,116,8,
  	5,1,5,1,5,3,5,120,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,147,8,6,1,7,1,
  	7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,3,8,158,8,8,1,9,1,9,1,9,3,9,163,8,9,1,10,
  	1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,3,11,176,8,11,1,11,
  	1,11,3,11,180,8,11,1,11,1,11,1,11,3,11,185,8,11,1,11,1,11,1,11,1,12,1,
  	12,1,13,1,13,1,14,1,14,1,14,3,14,197,8,14,1,14,1,14,1,15,1,15,1,15,5,
  	15,204,8,15,10,15,12,15,207,9,15,1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,
  	18,1,18,5,18,218,8,18,10,18,12,18,221,9,18,1,19,1,19,1,19,5,19,226,8,
  	19,10,19,12,19,229,9,19,1,20,1,20,1,20,5,20,234,8,20,10,20,12,20,237,
  	9,20,1,21,1,21,1,21,5,21,242,8,21,10,21,12,21,245,9,21,1,22,1,22,1,22,
  	5,22,250,8,22,10,22,12,22,253,9,22,1,23,1,23,1,23,5,23,258,8,23,10,23,
  	12,23,261,9,23,1,24,1,24,1,24,5,24,266,8,24,10,24,12,24,269,9,24,1,25,
  	1,25,1,25,5,25,274,8,25,10,25,12,25,277,9,25,1,26,1,26,1,26,5,26,282,
  	8,26,10,26,12,26,285,9,26,1,27,1,27,1,27,5,27,290,8,27,10,27,12,27,293,
  	9,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,3,28,302,8,28,1,29,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,5,29,316,8,29,10,29,12,29,
  	319,9,29,1,30,1,30,1,30,1,30,1,30,1,30,1,30,3,30,328,8,30,1,31,1,31,1,
  	31,0,1,58,32,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
  	42,44,46,48,50,52,54,56,58,60,62,0,7,1,0,23,33,1,0,36,37,2,0,34,35,38,
  	39,1,0,61,62,1,0,16,17,1,0,20,22,3,0,7,8,51,51,53,54,350,0,65,1,0,0,0,
  	2,71,1,0,0,0,4,80,1,0,0,0,6,91,1,0,0,0,8,108,1,0,0,0,10,110,1,0,0,0,12,
  	146,1,0,0,0,14,148,1,0,0,0,16,151,1,0,0,0,18,159,1,0,0,0,20,164,1,0,0,
  	0,22,170,1,0,0,0,24,189,1,0,0,0,26,191,1,0,0,0,28,193,1,0,0,0,30,200,
  	1,0,0,0,32,208,1,0,0,0,34,212,1,0,0,0,36,214,1,0,0,0,38,222,1,0,0,0,40,
  	230,1,0,0,0,42,238,1,0,0,0,44,246,1,0,0,0,46,254,1,0,0,0,48,262,1,0,0,
  	0,50,270,1,0,0,0,52,278,1,0,0,0,54,286,1,0,0,0,56,301,1,0,0,0,58,303,
  	1,0,0,0,60,327,1,0,0,0,62,329,1,0,0,0,64,66,3,2,1,0,65,64,1,0,0,0,66,
  	67,1,0,0,0,67,65,1,0,0,0,67,68,1,0,0,0,68,69,1,0,0,0,69,70,5,0,0,1,70,
  	1,1,0,0,0,71,72,3,8,4,0,72,73,5,52,0,0,73,75,5,44,0,0,74,76,3,4,2,0,75,
  	74,1,0,0,0,75,76,1,0,0,0,76,77,1,0,0,0,77,78,5,45,0,0,78,79,3,6,3,0,79,
  	3,1,0,0,0,80,81,3,8,4,0,81,88,5,52,0,0,82,83,5,50,0,0,83,84,3,8,4,0,84,
  	85,5,52,0,0,85,87,1,0,0,0,86,82,1,0,0,0,87,90,1,0,0,0,88,86,1,0,0,0,88,
  	89,1,0,0,0,89,5,1,0,0,0,90,88,1,0,0,0,91,95,5,46,0,0,92,94,3,12,6,0,93,
  	92,1,0,0,0,94,97,1,0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,96,98,1,0,0,0,97,
  	95,1,0,0,0,98,99,5,47,0,0,99,7,1,0,0,0,100,109,5,1,0,0,101,109,5,3,0,
  	0,102,109,5,6,0,0,103,109,5,13,0,0,104,105,5,13,0,0,105,109,5,13,0,0,
  	106,109,5,14,0,0,107,109,5,15,0,0,108,100,1,0,0,0,108,101,1,0,0,0,108,
  	102,1,0,0,0,108,103,1,0,0,0,108,104,1,0,0,0,108,106,1,0,0,0,108,107,1,
  	0,0,0,109,9,1,0,0,0,110,111,3,8,4,0,111,115,5,52,0,0,112,113,5,48,0,0,
  	113,114,5,53,0,0,114,116,5,49,0,0,115,112,1,0,0,0,115,116,1,0,0,0,116,
  	119,1,0,0,0,117,118,5,23,0,0,118,120,3,34,17,0,119,117,1,0,0,0,119,120,
  	1,0,0,0,120,11,1,0,0,0,121,122,3,28,14,0,122,123,5,43,0,0,123,147,1,0,
  	0,0,124,125,3,34,17,0,125,126,5,43,0,0,126,147,1,0,0,0,127,128,3,10,5,
  	0,128,129,5,43,0,0,129,147,1,0,0,0,130,131,3,14,7,0,131,132,5,43,0,0,
  	132,147,1,0,0,0,133,134,3,32,16,0,134,135,5,43,0,0,135,147,1,0,0,0,136,
  	147,3,16,8,0,137,147,3,20,10,0,138,147,3,22,11,0,139,140,3,24,12,0,140,
  	141,5,43,0,0,141,147,1,0,0,0,142,143,3,26,13,0,143,144,5,43,0,0,144,147,
  	1,0,0,0,145,147,5,43,0,0,146,121,1,0,0,0,146,124,1,0,0,0,146,127,1,0,
  	0,0,146,130,1,0,0,0,146,133,1,0,0,0,146,136,1,0,0,0,146,137,1,0,0,0,146,
  	138,1,0,0,0,146,139,1,0,0,0,146,142,1,0,0,0,146,145,1,0,0,0,147,13,1,
  	0,0,0,148,149,5,2,0,0,149,150,3,34,17,0,150,15,1,0,0,0,151,152,5,4,0,
  	0,152,153,5,44,0,0,153,154,3,34,17,0,154,155,5,45,0,0,155,157,3,6,3,0,
  	156,158,3,18,9,0,157,156,1,0,0,0,157,158,1,0,0,0,158,17,1,0,0,0,159,162,
  	5,5,0,0,160,163,3,16,8,0,161,163,3,6,3,0,162,160,1,0,0,0,162,161,1,0,
  	0,0,163,19,1,0,0,0,164,165,5,9,0,0,165,166,5,44,0,0,166,167,3,34,17,0,
  	167,168,5,45,0,0,168,169,3,6,3,0,169,21,1,0,0,0,170,171,5,10,0,0,171,
  	175,5,44,0,0,172,176,3,10,5,0,173,176,3,32,16,0,174,176,3,34,17,0,175,
  	172,1,0,0,0,175,173,1,0,0,0,175,174,1,0,0,0,175,176,1,0,0,0,176,177,1,
  	0,0,0,177,179,5,43,0,0,178,180,3,34,17,0,179,178,1,0,0,0,179,180,1,0,
  	0,0,180,181,1,0,0,0,181,184,5,43,0,0,182,185,3,32,16,0,183,185,3,34,17,
  	0,184,182,1,0,0,0,184,183,1,0,0,0,184,185,1,0,0,0,185,186,1,0,0,0,186,
  	187,5,45,0,0,187,188,3,6,3,0,188,23,1,0,0,0,189,190,5,11,0,0,190,25,1,
  	0,0,0,191,192,5,12,0,0,192,27,1,0,0,0,193,194,5,52,0,0,194,196,5,44,0,
  	0,195,197,3,30,15,0,196,195,1,0,0,0,196,197,1,0,0,0,197,198,1,0,0,0,198,
  	199,5,45,0,0,199,29,1,0,0,0,200,205,3,34,17,0,201,202,5,50,0,0,202,204,
  	3,34,17,0,203,201,1,0,0,0,204,207,1,0,0,0,205,203,1,0,0,0,205,206,1,0,
  	0,0,206,31,1,0,0,0,207,205,1,0,0,0,208,209,3,58,29,0,209,210,7,0,0,0,
  	210,211,3,34,17,0,211,33,1,0,0,0,212,213,3,36,18,0,213,35,1,0,0,0,214,
  	219,3,38,19,0,215,216,5,41,0,0,216,218,3,38,19,0,217,215,1,0,0,0,218,
  	221,1,0,0,0,219,217,1,0,0,0,219,220,1,0,0,0,220,37,1,0,0,0,221,219,1,
  	0,0,0,222,227,3,40,20,0,223,224,5,40,0,0,224,226,3,40,20,0,225,223,1,
  	0,0,0,226,229,1,0,0,0,227,225,1,0,0,0,227,228,1,0,0,0,228,39,1,0,0,0,
  	229,227,1,0,0,0,230,235,3,42,21,0,231,232,5,58,0,0,232,234,3,42,21,0,
  	233,231,1,0,0,0,234,237,1,0,0,0,235,233,1,0,0,0,235,236,1,0,0,0,236,41,
  	1,0,0,0,237,235,1,0,0,0,238,243,3,44,22,0,239,240,5,59,0,0,240,242,3,
  	44,22,0,241,239,1,0,0,0,242,245,1,0,0,0,243,241,1,0,0,0,243,244,1,0,0,
  	0,244,43,1,0,0,0,245,243,1,0,0,0,246,251,3,46,23,0,247,248,5,57,0,0,248,
  	250,3,46,23,0,249,247,1,0,0,0,250,253,1,0,0,0,251,249,1,0,0,0,251,252,
  	1,0,0,0,252,45,1,0,0,0,253,251,1,0,0,0,254,259,3,48,24,0,255,256,7,1,
  	0,0,256,258,3,48,24,0,257,255,1,0,0,0,258,261,1,0,0,0,259,257,1,0,0,0,
  	259,260,1,0,0,0,260,47,1,0,0,0,261,259,1,0,0,0,262,267,3,50,25,0,263,
  	264,7,2,0,0,264,266,3,50,25,0,265,263,1,0,0,0,266,269,1,0,0,0,267,265,
  	1,0,0,0,267,268,1,0,0,0,268,49,1,0,0,0,269,267,1,0,0,0,270,275,3,52,26,
  	0,271,272,7,3,0,0,272,274,3,52,26,0,273,271,1,0,0,0,274,277,1,0,0,0,275,
  	273,1,0,0,0,275,276,1,0,0,0,276,51,1,0,0,0,277,275,1,0,0,0,278,283,3,
  	54,27,0,279,280,7,4,0,0,280,282,3,54,27,0,281,279,1,0,0,0,282,285,1,0,
  	0,0,283,281,1,0,0,0,283,284,1,0,0,0,284,53,1,0,0,0,285,283,1,0,0,0,286,
  	291,3,56,28,0,287,288,7,5,0,0,288,290,3,56,28,0,289,287,1,0,0,0,290,293,
  	1,0,0,0,291,289,1,0,0,0,291,292,1,0,0,0,292,55,1,0,0,0,293,291,1,0,0,
  	0,294,302,3,58,29,0,295,296,5,42,0,0,296,302,3,56,28,0,297,298,5,60,0,
  	0,298,302,3,56,28,0,299,300,5,17,0,0,300,302,3,56,28,0,301,294,1,0,0,
  	0,301,295,1,0,0,0,301,297,1,0,0,0,301,299,1,0,0,0,302,57,1,0,0,0,303,
  	304,6,29,-1,0,304,305,3,60,30,0,305,317,1,0,0,0,306,307,10,3,0,0,307,
  	308,5,48,0,0,308,309,3,34,17,0,309,310,5,49,0,0,310,316,1,0,0,0,311,312,
  	10,2,0,0,312,316,5,18,0,0,313,314,10,1,0,0,314,316,5,19,0,0,315,306,1,
  	0,0,0,315,311,1,0,0,0,315,313,1,0,0,0,316,319,1,0,0,0,317,315,1,0,0,0,
  	317,318,1,0,0,0,318,59,1,0,0,0,319,317,1,0,0,0,320,328,3,62,31,0,321,
  	328,3,28,14,0,322,328,5,52,0,0,323,324,5,44,0,0,324,325,3,34,17,0,325,
  	326,5,45,0,0,326,328,1,0,0,0,327,320,1,0,0,0,327,321,1,0,0,0,327,322,
  	1,0,0,0,327,323,1,0,0,0,328,61,1,0,0,0,329,330,7,6,0,0,330,63,1,0,0,0,
  	29,67,75,88,95,108,115,119,146,157,162,175,179,184,196,205,219,227,235,
  	243,251,259,267,275,283,291,301,315,317,327
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ryntraParserStaticData = std::move(staticData);
}

}

RyntraParser::RyntraParser(TokenStream *input) : RyntraParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

RyntraParser::RyntraParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  RyntraParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ryntraParserStaticData->atn, ryntraParserStaticData->decisionToDFA, ryntraParserStaticData->sharedContextCache, options);
}

RyntraParser::~RyntraParser() {
  delete _interpreter;
}

const atn::ATN& RyntraParser::getATN() const {
  return *ryntraParserStaticData->atn;
}

std::string RyntraParser::getGrammarFileName() const {
  return "Ryntra.g4";
}

const std::vector<std::string>& RyntraParser::getRuleNames() const {
  return ryntraParserStaticData->ruleNames;
}

const dfa::Vocabulary& RyntraParser::getVocabulary() const {
  return ryntraParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView RyntraParser::getSerializedATN() const {
  return ryntraParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

RyntraParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::ProgramContext::EOF() {
  return getToken(RyntraParser::EOF, 0);
}

std::vector<RyntraParser::FunctionDefinitionContext *> RyntraParser::ProgramContext::functionDefinition() {
  return getRuleContexts<RyntraParser::FunctionDefinitionContext>();
}

RyntraParser::FunctionDefinitionContext* RyntraParser::ProgramContext::functionDefinition(size_t i) {
  return getRuleContext<RyntraParser::FunctionDefinitionContext>(i);
}


size_t RyntraParser::ProgramContext::getRuleIndex() const {
  return RyntraParser::RuleProgram;
}

void RyntraParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void RyntraParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any RyntraParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ProgramContext* RyntraParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, RyntraParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(64);
      functionDefinition();
      setState(67); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 57418) != 0));
    setState(69);
    match(RyntraParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

RyntraParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::TypeSpecifierContext* RyntraParser::FunctionDefinitionContext::typeSpecifier() {
  return getRuleContext<RyntraParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* RyntraParser::FunctionDefinitionContext::IDENTIFIER() {
  return getToken(RyntraParser::IDENTIFIER, 0);
}

tree::TerminalNode* RyntraParser::FunctionDefinitionContext::LPAREN() {
  return getToken(RyntraParser::LPAREN, 0);
}

tree::TerminalNode* RyntraParser::FunctionDefinitionContext::RPAREN() {
  return getToken(RyntraParser::RPAREN, 0);
}

RyntraParser::BlockContext* RyntraParser::FunctionDefinitionContext::block() {
  return getRuleContext<RyntraParser::BlockContext>(0);
}

RyntraParser::ParameterListContext* RyntraParser::FunctionDefinitionContext::parameterList() {
  return getRuleContext<RyntraParser::ParameterListContext>(0);
}


size_t RyntraParser::FunctionDefinitionContext::getRuleIndex() const {
  return RyntraParser::RuleFunctionDefinition;
}

void RyntraParser::FunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDefinition(this);
}

void RyntraParser::FunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDefinition(this);
}


std::any RyntraParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::FunctionDefinitionContext* RyntraParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 2, RyntraParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    typeSpecifier();
    setState(72);
    match(RyntraParser::IDENTIFIER);
    setState(73);
    match(RyntraParser::LPAREN);
    setState(75);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 57418) != 0)) {
      setState(74);
      parameterList();
    }
    setState(77);
    match(RyntraParser::RPAREN);
    setState(78);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

RyntraParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::TypeSpecifierContext *> RyntraParser::ParameterListContext::typeSpecifier() {
  return getRuleContexts<RyntraParser::TypeSpecifierContext>();
}

RyntraParser::TypeSpecifierContext* RyntraParser::ParameterListContext::typeSpecifier(size_t i) {
  return getRuleContext<RyntraParser::TypeSpecifierContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::ParameterListContext::IDENTIFIER() {
  return getTokens(RyntraParser::IDENTIFIER);
}

tree::TerminalNode* RyntraParser::ParameterListContext::IDENTIFIER(size_t i) {
  return getToken(RyntraParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> RyntraParser::ParameterListContext::COMMA() {
  return getTokens(RyntraParser::COMMA);
}

tree::TerminalNode* RyntraParser::ParameterListContext::COMMA(size_t i) {
  return getToken(RyntraParser::COMMA, i);
}


size_t RyntraParser::ParameterListContext::getRuleIndex() const {
  return RyntraParser::RuleParameterList;
}

void RyntraParser::ParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterList(this);
}

void RyntraParser::ParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterList(this);
}


std::any RyntraParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ParameterListContext* RyntraParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 4, RyntraParser::RuleParameterList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    typeSpecifier();
    setState(81);
    match(RyntraParser::IDENTIFIER);
    setState(88);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(82);
      match(RyntraParser::COMMA);
      setState(83);
      typeSpecifier();
      setState(84);
      match(RyntraParser::IDENTIFIER);
      setState(90);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

RyntraParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::BlockContext::LBRACE() {
  return getToken(RyntraParser::LBRACE, 0);
}

tree::TerminalNode* RyntraParser::BlockContext::RBRACE() {
  return getToken(RyntraParser::RBRACE, 0);
}

std::vector<RyntraParser::StatementContext *> RyntraParser::BlockContext::statement() {
  return getRuleContexts<RyntraParser::StatementContext>();
}

RyntraParser::StatementContext* RyntraParser::BlockContext::statement(size_t i) {
  return getRuleContext<RyntraParser::StatementContext>(i);
}


size_t RyntraParser::BlockContext::getRuleIndex() const {
  return RyntraParser::RuleBlock;
}

void RyntraParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void RyntraParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any RyntraParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::BlockContext* RyntraParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, RyntraParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(RyntraParser::LBRACE);
    setState(95);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1186729288137899998) != 0)) {
      setState(92);
      statement();
      setState(97);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(98);
    match(RyntraParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecifierContext ------------------------------------------------------------------

RyntraParser::TypeSpecifierContext::TypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::TypeSpecifierContext::INT() {
  return getToken(RyntraParser::INT, 0);
}

tree::TerminalNode* RyntraParser::TypeSpecifierContext::STRING() {
  return getToken(RyntraParser::STRING, 0);
}

tree::TerminalNode* RyntraParser::TypeSpecifierContext::BOOL() {
  return getToken(RyntraParser::BOOL, 0);
}

std::vector<tree::TerminalNode *> RyntraParser::TypeSpecifierContext::LONG() {
  return getTokens(RyntraParser::LONG);
}

tree::TerminalNode* RyntraParser::TypeSpecifierContext::LONG(size_t i) {
  return getToken(RyntraParser::LONG, i);
}

tree::TerminalNode* RyntraParser::TypeSpecifierContext::FLOAT() {
  return getToken(RyntraParser::FLOAT, 0);
}

tree::TerminalNode* RyntraParser::TypeSpecifierContext::DOUBLE() {
  return getToken(RyntraParser::DOUBLE, 0);
}


size_t RyntraParser::TypeSpecifierContext::getRuleIndex() const {
  return RyntraParser::RuleTypeSpecifier;
}

void RyntraParser::TypeSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpecifier(this);
}

void RyntraParser::TypeSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpecifier(this);
}


std::any RyntraParser::TypeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitTypeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::TypeSpecifierContext* RyntraParser::typeSpecifier() {
  TypeSpecifierContext *_localctx = _tracker.createInstance<TypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 8, RyntraParser::RuleTypeSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(100);
      match(RyntraParser::INT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(101);
      match(RyntraParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(102);
      match(RyntraParser::BOOL);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(103);
      match(RyntraParser::LONG);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(104);
      match(RyntraParser::LONG);
      setState(105);
      match(RyntraParser::LONG);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(106);
      match(RyntraParser::FLOAT);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(107);
      match(RyntraParser::DOUBLE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

RyntraParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::TypeSpecifierContext* RyntraParser::VariableDeclarationContext::typeSpecifier() {
  return getRuleContext<RyntraParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* RyntraParser::VariableDeclarationContext::IDENTIFIER() {
  return getToken(RyntraParser::IDENTIFIER, 0);
}

tree::TerminalNode* RyntraParser::VariableDeclarationContext::LBRACKET() {
  return getToken(RyntraParser::LBRACKET, 0);
}

tree::TerminalNode* RyntraParser::VariableDeclarationContext::INTEGER_LITERAL() {
  return getToken(RyntraParser::INTEGER_LITERAL, 0);
}

tree::TerminalNode* RyntraParser::VariableDeclarationContext::RBRACKET() {
  return getToken(RyntraParser::RBRACKET, 0);
}

tree::TerminalNode* RyntraParser::VariableDeclarationContext::ASSIGN() {
  return getToken(RyntraParser::ASSIGN, 0);
}

RyntraParser::ExpressionContext* RyntraParser::VariableDeclarationContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}


size_t RyntraParser::VariableDeclarationContext::getRuleIndex() const {
  return RyntraParser::RuleVariableDeclaration;
}

void RyntraParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void RyntraParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


std::any RyntraParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::VariableDeclarationContext* RyntraParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 10, RyntraParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    typeSpecifier();
    setState(111);
    match(RyntraParser::IDENTIFIER);
    setState(115);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::LBRACKET) {
      setState(112);
      match(RyntraParser::LBRACKET);
      setState(113);
      match(RyntraParser::INTEGER_LITERAL);
      setState(114);
      match(RyntraParser::RBRACKET);
    }
    setState(119);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ASSIGN) {
      setState(117);
      match(RyntraParser::ASSIGN);
      setState(118);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

RyntraParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::FunctionCallContext* RyntraParser::StatementContext::functionCall() {
  return getRuleContext<RyntraParser::FunctionCallContext>(0);
}

tree::TerminalNode* RyntraParser::StatementContext::SEMICOLON() {
  return getToken(RyntraParser::SEMICOLON, 0);
}

RyntraParser::ExpressionContext* RyntraParser::StatementContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}

RyntraParser::VariableDeclarationContext* RyntraParser::StatementContext::variableDeclaration() {
  return getRuleContext<RyntraParser::VariableDeclarationContext>(0);
}

RyntraParser::ReturnStatementContext* RyntraParser::StatementContext::returnStatement() {
  return getRuleContext<RyntraParser::ReturnStatementContext>(0);
}

RyntraParser::AssignmentContext* RyntraParser::StatementContext::assignment() {
  return getRuleContext<RyntraParser::AssignmentContext>(0);
}

RyntraParser::IfStatementContext* RyntraParser::StatementContext::ifStatement() {
  return getRuleContext<RyntraParser::IfStatementContext>(0);
}

RyntraParser::WhileStatementContext* RyntraParser::StatementContext::whileStatement() {
  return getRuleContext<RyntraParser::WhileStatementContext>(0);
}

RyntraParser::ForStatementContext* RyntraParser::StatementContext::forStatement() {
  return getRuleContext<RyntraParser::ForStatementContext>(0);
}

RyntraParser::BreakStatementContext* RyntraParser::StatementContext::breakStatement() {
  return getRuleContext<RyntraParser::BreakStatementContext>(0);
}

RyntraParser::ContinueStatementContext* RyntraParser::StatementContext::continueStatement() {
  return getRuleContext<RyntraParser::ContinueStatementContext>(0);
}


size_t RyntraParser::StatementContext::getRuleIndex() const {
  return RyntraParser::RuleStatement;
}

void RyntraParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void RyntraParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any RyntraParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::StatementContext* RyntraParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 12, RyntraParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(146);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(121);
      functionCall();
      setState(122);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(124);
      expression();
      setState(125);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(127);
      variableDeclaration();
      setState(128);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(130);
      returnStatement();
      setState(131);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(133);
      assignment();
      setState(134);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(136);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(137);
      whileStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(138);
      forStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(139);
      breakStatement();
      setState(140);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(142);
      continueStatement();
      setState(143);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(145);
      match(RyntraParser::SEMICOLON);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

RyntraParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::ReturnStatementContext::RETURN() {
  return getToken(RyntraParser::RETURN, 0);
}

RyntraParser::ExpressionContext* RyntraParser::ReturnStatementContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}


size_t RyntraParser::ReturnStatementContext::getRuleIndex() const {
  return RyntraParser::RuleReturnStatement;
}

void RyntraParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void RyntraParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


std::any RyntraParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ReturnStatementContext* RyntraParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 14, RyntraParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    match(RyntraParser::RETURN);
    setState(149);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

RyntraParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::IfStatementContext::IF() {
  return getToken(RyntraParser::IF, 0);
}

tree::TerminalNode* RyntraParser::IfStatementContext::LPAREN() {
  return getToken(RyntraParser::LPAREN, 0);
}

RyntraParser::ExpressionContext* RyntraParser::IfStatementContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::IfStatementContext::RPAREN() {
  return getToken(RyntraParser::RPAREN, 0);
}

RyntraParser::BlockContext* RyntraParser::IfStatementContext::block() {
  return getRuleContext<RyntraParser::BlockContext>(0);
}

RyntraParser::ElseClauseContext* RyntraParser::IfStatementContext::elseClause() {
  return getRuleContext<RyntraParser::ElseClauseContext>(0);
}


size_t RyntraParser::IfStatementContext::getRuleIndex() const {
  return RyntraParser::RuleIfStatement;
}

void RyntraParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void RyntraParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}


std::any RyntraParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::IfStatementContext* RyntraParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, RyntraParser::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    match(RyntraParser::IF);
    setState(152);
    match(RyntraParser::LPAREN);
    setState(153);
    expression();
    setState(154);
    match(RyntraParser::RPAREN);
    setState(155);
    block();
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ELSE) {
      setState(156);
      elseClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseClauseContext ------------------------------------------------------------------

RyntraParser::ElseClauseContext::ElseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::ElseClauseContext::ELSE() {
  return getToken(RyntraParser::ELSE, 0);
}

RyntraParser::IfStatementContext* RyntraParser::ElseClauseContext::ifStatement() {
  return getRuleContext<RyntraParser::IfStatementContext>(0);
}

RyntraParser::BlockContext* RyntraParser::ElseClauseContext::block() {
  return getRuleContext<RyntraParser::BlockContext>(0);
}


size_t RyntraParser::ElseClauseContext::getRuleIndex() const {
  return RyntraParser::RuleElseClause;
}

void RyntraParser::ElseClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseClause(this);
}

void RyntraParser::ElseClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseClause(this);
}


std::any RyntraParser::ElseClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitElseClause(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ElseClauseContext* RyntraParser::elseClause() {
  ElseClauseContext *_localctx = _tracker.createInstance<ElseClauseContext>(_ctx, getState());
  enterRule(_localctx, 18, RyntraParser::RuleElseClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    match(RyntraParser::ELSE);
    setState(162);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::IF: {
        setState(160);
        ifStatement();
        break;
      }

      case RyntraParser::LBRACE: {
        setState(161);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

RyntraParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::WhileStatementContext::WHILE() {
  return getToken(RyntraParser::WHILE, 0);
}

tree::TerminalNode* RyntraParser::WhileStatementContext::LPAREN() {
  return getToken(RyntraParser::LPAREN, 0);
}

RyntraParser::ExpressionContext* RyntraParser::WhileStatementContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::WhileStatementContext::RPAREN() {
  return getToken(RyntraParser::RPAREN, 0);
}

RyntraParser::BlockContext* RyntraParser::WhileStatementContext::block() {
  return getRuleContext<RyntraParser::BlockContext>(0);
}


size_t RyntraParser::WhileStatementContext::getRuleIndex() const {
  return RyntraParser::RuleWhileStatement;
}

void RyntraParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}

void RyntraParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}


std::any RyntraParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::WhileStatementContext* RyntraParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, RyntraParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(RyntraParser::WHILE);
    setState(165);
    match(RyntraParser::LPAREN);
    setState(166);
    expression();
    setState(167);
    match(RyntraParser::RPAREN);
    setState(168);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

RyntraParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::ForStatementContext::FOR() {
  return getToken(RyntraParser::FOR, 0);
}

tree::TerminalNode* RyntraParser::ForStatementContext::LPAREN() {
  return getToken(RyntraParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> RyntraParser::ForStatementContext::SEMICOLON() {
  return getTokens(RyntraParser::SEMICOLON);
}

tree::TerminalNode* RyntraParser::ForStatementContext::SEMICOLON(size_t i) {
  return getToken(RyntraParser::SEMICOLON, i);
}

tree::TerminalNode* RyntraParser::ForStatementContext::RPAREN() {
  return getToken(RyntraParser::RPAREN, 0);
}

RyntraParser::BlockContext* RyntraParser::ForStatementContext::block() {
  return getRuleContext<RyntraParser::BlockContext>(0);
}

RyntraParser::VariableDeclarationContext* RyntraParser::ForStatementContext::variableDeclaration() {
  return getRuleContext<RyntraParser::VariableDeclarationContext>(0);
}

std::vector<RyntraParser::AssignmentContext *> RyntraParser::ForStatementContext::assignment() {
  return getRuleContexts<RyntraParser::AssignmentContext>();
}

RyntraParser::AssignmentContext* RyntraParser::ForStatementContext::assignment(size_t i) {
  return getRuleContext<RyntraParser::AssignmentContext>(i);
}

std::vector<RyntraParser::ExpressionContext *> RyntraParser::ForStatementContext::expression() {
  return getRuleContexts<RyntraParser::ExpressionContext>();
}

RyntraParser::ExpressionContext* RyntraParser::ForStatementContext::expression(size_t i) {
  return getRuleContext<RyntraParser::ExpressionContext>(i);
}


size_t RyntraParser::ForStatementContext::getRuleIndex() const {
  return RyntraParser::RuleForStatement;
}

void RyntraParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}

void RyntraParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}


std::any RyntraParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ForStatementContext* RyntraParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, RyntraParser::RuleForStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(RyntraParser::FOR);
    setState(171);
    match(RyntraParser::LPAREN);
    setState(175);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(172);
      variableDeclaration();
      break;
    }

    case 2: {
      setState(173);
      assignment();
      break;
    }

    case 3: {
      setState(174);
      expression();
      break;
    }

    default:
      break;
    }
    setState(177);
    match(RyntraParser::SEMICOLON);
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1186720492044812672) != 0)) {
      setState(178);
      expression();
    }
    setState(181);
    match(RyntraParser::SEMICOLON);
    setState(184);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(182);
      assignment();
      break;
    }

    case 2: {
      setState(183);
      expression();
      break;
    }

    default:
      break;
    }
    setState(186);
    match(RyntraParser::RPAREN);
    setState(187);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

RyntraParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::BreakStatementContext::BREAK() {
  return getToken(RyntraParser::BREAK, 0);
}


size_t RyntraParser::BreakStatementContext::getRuleIndex() const {
  return RyntraParser::RuleBreakStatement;
}

void RyntraParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void RyntraParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}


std::any RyntraParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::BreakStatementContext* RyntraParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, RyntraParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(RyntraParser::BREAK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

RyntraParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::ContinueStatementContext::CONTINUE() {
  return getToken(RyntraParser::CONTINUE, 0);
}


size_t RyntraParser::ContinueStatementContext::getRuleIndex() const {
  return RyntraParser::RuleContinueStatement;
}

void RyntraParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void RyntraParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}


std::any RyntraParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ContinueStatementContext* RyntraParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, RyntraParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    match(RyntraParser::CONTINUE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

RyntraParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::FunctionCallContext::IDENTIFIER() {
  return getToken(RyntraParser::IDENTIFIER, 0);
}

tree::TerminalNode* RyntraParser::FunctionCallContext::LPAREN() {
  return getToken(RyntraParser::LPAREN, 0);
}

tree::TerminalNode* RyntraParser::FunctionCallContext::RPAREN() {
  return getToken(RyntraParser::RPAREN, 0);
}

RyntraParser::ArgumentListContext* RyntraParser::FunctionCallContext::argumentList() {
  return getRuleContext<RyntraParser::ArgumentListContext>(0);
}


size_t RyntraParser::FunctionCallContext::getRuleIndex() const {
  return RyntraParser::RuleFunctionCall;
}

void RyntraParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void RyntraParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}


std::any RyntraParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::FunctionCallContext* RyntraParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 28, RyntraParser::RuleFunctionCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    match(RyntraParser::IDENTIFIER);
    setState(194);
    match(RyntraParser::LPAREN);

    setState(196);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1186720492044812672) != 0)) {
      setState(195);
      argumentList();
    }
    setState(198);
    match(RyntraParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

RyntraParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::ExpressionContext *> RyntraParser::ArgumentListContext::expression() {
  return getRuleContexts<RyntraParser::ExpressionContext>();
}

RyntraParser::ExpressionContext* RyntraParser::ArgumentListContext::expression(size_t i) {
  return getRuleContext<RyntraParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::ArgumentListContext::COMMA() {
  return getTokens(RyntraParser::COMMA);
}

tree::TerminalNode* RyntraParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(RyntraParser::COMMA, i);
}


size_t RyntraParser::ArgumentListContext::getRuleIndex() const {
  return RyntraParser::RuleArgumentList;
}

void RyntraParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void RyntraParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}


std::any RyntraParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ArgumentListContext* RyntraParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 30, RyntraParser::RuleArgumentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(200);
    expression();
    setState(205);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(201);
      match(RyntraParser::COMMA);
      setState(202);
      expression();
      setState(207);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

RyntraParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::PostfixExpressionContext* RyntraParser::AssignmentContext::postfixExpression() {
  return getRuleContext<RyntraParser::PostfixExpressionContext>(0);
}

RyntraParser::ExpressionContext* RyntraParser::AssignmentContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::ASSIGN() {
  return getToken(RyntraParser::ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::ADD_ASSIGN() {
  return getToken(RyntraParser::ADD_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::SUB_ASSIGN() {
  return getToken(RyntraParser::SUB_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::MUL_ASSIGN() {
  return getToken(RyntraParser::MUL_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::DIV_ASSIGN() {
  return getToken(RyntraParser::DIV_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::MOD_ASSIGN() {
  return getToken(RyntraParser::MOD_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::AND_ASSIGN() {
  return getToken(RyntraParser::AND_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::OR_ASSIGN() {
  return getToken(RyntraParser::OR_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::XOR_ASSIGN() {
  return getToken(RyntraParser::XOR_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::LSHIFT_ASSIGN() {
  return getToken(RyntraParser::LSHIFT_ASSIGN, 0);
}

tree::TerminalNode* RyntraParser::AssignmentContext::RSHIFT_ASSIGN() {
  return getToken(RyntraParser::RSHIFT_ASSIGN, 0);
}


size_t RyntraParser::AssignmentContext::getRuleIndex() const {
  return RyntraParser::RuleAssignment;
}

void RyntraParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void RyntraParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any RyntraParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::AssignmentContext* RyntraParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 32, RyntraParser::RuleAssignment);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    postfixExpression(0);
    setState(209);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17171480576) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(210);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

RyntraParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::LogicalOrExpressionContext* RyntraParser::ExpressionContext::logicalOrExpression() {
  return getRuleContext<RyntraParser::LogicalOrExpressionContext>(0);
}


size_t RyntraParser::ExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleExpression;
}

void RyntraParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void RyntraParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any RyntraParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ExpressionContext* RyntraParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 34, RyntraParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    logicalOrExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

RyntraParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::LogicalAndExpressionContext *> RyntraParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContexts<RyntraParser::LogicalAndExpressionContext>();
}

RyntraParser::LogicalAndExpressionContext* RyntraParser::LogicalOrExpressionContext::logicalAndExpression(size_t i) {
  return getRuleContext<RyntraParser::LogicalAndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::LogicalOrExpressionContext::LOGIC_OR() {
  return getTokens(RyntraParser::LOGIC_OR);
}

tree::TerminalNode* RyntraParser::LogicalOrExpressionContext::LOGIC_OR(size_t i) {
  return getToken(RyntraParser::LOGIC_OR, i);
}


size_t RyntraParser::LogicalOrExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleLogicalOrExpression;
}

void RyntraParser::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}

void RyntraParser::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}


std::any RyntraParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::LogicalOrExpressionContext* RyntraParser::logicalOrExpression() {
  LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 36, RyntraParser::RuleLogicalOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    logicalAndExpression();
    setState(219);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_OR) {
      setState(215);
      match(RyntraParser::LOGIC_OR);
      setState(216);
      logicalAndExpression();
      setState(221);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

RyntraParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::InclusiveOrExpressionContext *> RyntraParser::LogicalAndExpressionContext::inclusiveOrExpression() {
  return getRuleContexts<RyntraParser::InclusiveOrExpressionContext>();
}

RyntraParser::InclusiveOrExpressionContext* RyntraParser::LogicalAndExpressionContext::inclusiveOrExpression(size_t i) {
  return getRuleContext<RyntraParser::InclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::LogicalAndExpressionContext::LOGIC_AND() {
  return getTokens(RyntraParser::LOGIC_AND);
}

tree::TerminalNode* RyntraParser::LogicalAndExpressionContext::LOGIC_AND(size_t i) {
  return getToken(RyntraParser::LOGIC_AND, i);
}


size_t RyntraParser::LogicalAndExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleLogicalAndExpression;
}

void RyntraParser::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}

void RyntraParser::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}


std::any RyntraParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::LogicalAndExpressionContext* RyntraParser::logicalAndExpression() {
  LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, RyntraParser::RuleLogicalAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    inclusiveOrExpression();
    setState(227);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_AND) {
      setState(223);
      match(RyntraParser::LOGIC_AND);
      setState(224);
      inclusiveOrExpression();
      setState(229);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InclusiveOrExpressionContext ------------------------------------------------------------------

RyntraParser::InclusiveOrExpressionContext::InclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::ExclusiveOrExpressionContext *> RyntraParser::InclusiveOrExpressionContext::exclusiveOrExpression() {
  return getRuleContexts<RyntraParser::ExclusiveOrExpressionContext>();
}

RyntraParser::ExclusiveOrExpressionContext* RyntraParser::InclusiveOrExpressionContext::exclusiveOrExpression(size_t i) {
  return getRuleContext<RyntraParser::ExclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::InclusiveOrExpressionContext::BIT_OR() {
  return getTokens(RyntraParser::BIT_OR);
}

tree::TerminalNode* RyntraParser::InclusiveOrExpressionContext::BIT_OR(size_t i) {
  return getToken(RyntraParser::BIT_OR, i);
}


size_t RyntraParser::InclusiveOrExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleInclusiveOrExpression;
}

void RyntraParser::InclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInclusiveOrExpression(this);
}

void RyntraParser::InclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInclusiveOrExpression(this);
}


std::any RyntraParser::InclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitInclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::InclusiveOrExpressionContext* RyntraParser::inclusiveOrExpression() {
  InclusiveOrExpressionContext *_localctx = _tracker.createInstance<InclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, RyntraParser::RuleInclusiveOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(230);
    exclusiveOrExpression();
    setState(235);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::BIT_OR) {
      setState(231);
      match(RyntraParser::BIT_OR);
      setState(232);
      exclusiveOrExpression();
      setState(237);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExclusiveOrExpressionContext ------------------------------------------------------------------

RyntraParser::ExclusiveOrExpressionContext::ExclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::AndExpressionContext *> RyntraParser::ExclusiveOrExpressionContext::andExpression() {
  return getRuleContexts<RyntraParser::AndExpressionContext>();
}

RyntraParser::AndExpressionContext* RyntraParser::ExclusiveOrExpressionContext::andExpression(size_t i) {
  return getRuleContext<RyntraParser::AndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::ExclusiveOrExpressionContext::BIT_XOR() {
  return getTokens(RyntraParser::BIT_XOR);
}

tree::TerminalNode* RyntraParser::ExclusiveOrExpressionContext::BIT_XOR(size_t i) {
  return getToken(RyntraParser::BIT_XOR, i);
}


size_t RyntraParser::ExclusiveOrExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleExclusiveOrExpression;
}

void RyntraParser::ExclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExclusiveOrExpression(this);
}

void RyntraParser::ExclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExclusiveOrExpression(this);
}


std::any RyntraParser::ExclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitExclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ExclusiveOrExpressionContext* RyntraParser::exclusiveOrExpression() {
  ExclusiveOrExpressionContext *_localctx = _tracker.createInstance<ExclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, RyntraParser::RuleExclusiveOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    andExpression();
    setState(243);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::BIT_XOR) {
      setState(239);
      match(RyntraParser::BIT_XOR);
      setState(240);
      andExpression();
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExpressionContext ------------------------------------------------------------------

RyntraParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::EqualityExpressionContext *> RyntraParser::AndExpressionContext::equalityExpression() {
  return getRuleContexts<RyntraParser::EqualityExpressionContext>();
}

RyntraParser::EqualityExpressionContext* RyntraParser::AndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<RyntraParser::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::AndExpressionContext::BIT_AND() {
  return getTokens(RyntraParser::BIT_AND);
}

tree::TerminalNode* RyntraParser::AndExpressionContext::BIT_AND(size_t i) {
  return getToken(RyntraParser::BIT_AND, i);
}


size_t RyntraParser::AndExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleAndExpression;
}

void RyntraParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void RyntraParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}


std::any RyntraParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::AndExpressionContext* RyntraParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, RyntraParser::RuleAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    equalityExpression();
    setState(251);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::BIT_AND) {
      setState(247);
      match(RyntraParser::BIT_AND);
      setState(248);
      equalityExpression();
      setState(253);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

RyntraParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::RelationalExpressionContext *> RyntraParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<RyntraParser::RelationalExpressionContext>();
}

RyntraParser::RelationalExpressionContext* RyntraParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<RyntraParser::RelationalExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::EqualityExpressionContext::COND_EQUAL() {
  return getTokens(RyntraParser::COND_EQUAL);
}

tree::TerminalNode* RyntraParser::EqualityExpressionContext::COND_EQUAL(size_t i) {
  return getToken(RyntraParser::COND_EQUAL, i);
}

std::vector<tree::TerminalNode *> RyntraParser::EqualityExpressionContext::NOT_EQUAL() {
  return getTokens(RyntraParser::NOT_EQUAL);
}

tree::TerminalNode* RyntraParser::EqualityExpressionContext::NOT_EQUAL(size_t i) {
  return getToken(RyntraParser::NOT_EQUAL, i);
}


size_t RyntraParser::EqualityExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleEqualityExpression;
}

void RyntraParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void RyntraParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}


std::any RyntraParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::EqualityExpressionContext* RyntraParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, RyntraParser::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    relationalExpression();
    setState(259);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COND_EQUAL

    || _la == RyntraParser::NOT_EQUAL) {
      setState(255);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::COND_EQUAL

      || _la == RyntraParser::NOT_EQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(256);
      relationalExpression();
      setState(261);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

RyntraParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::ShiftExpressionContext *> RyntraParser::RelationalExpressionContext::shiftExpression() {
  return getRuleContexts<RyntraParser::ShiftExpressionContext>();
}

RyntraParser::ShiftExpressionContext* RyntraParser::RelationalExpressionContext::shiftExpression(size_t i) {
  return getRuleContext<RyntraParser::ShiftExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::RelationalExpressionContext::GREATER() {
  return getTokens(RyntraParser::GREATER);
}

tree::TerminalNode* RyntraParser::RelationalExpressionContext::GREATER(size_t i) {
  return getToken(RyntraParser::GREATER, i);
}

std::vector<tree::TerminalNode *> RyntraParser::RelationalExpressionContext::LESS() {
  return getTokens(RyntraParser::LESS);
}

tree::TerminalNode* RyntraParser::RelationalExpressionContext::LESS(size_t i) {
  return getToken(RyntraParser::LESS, i);
}

std::vector<tree::TerminalNode *> RyntraParser::RelationalExpressionContext::GREATER_EQ() {
  return getTokens(RyntraParser::GREATER_EQ);
}

tree::TerminalNode* RyntraParser::RelationalExpressionContext::GREATER_EQ(size_t i) {
  return getToken(RyntraParser::GREATER_EQ, i);
}

std::vector<tree::TerminalNode *> RyntraParser::RelationalExpressionContext::LESS_EQ() {
  return getTokens(RyntraParser::LESS_EQ);
}

tree::TerminalNode* RyntraParser::RelationalExpressionContext::LESS_EQ(size_t i) {
  return getToken(RyntraParser::LESS_EQ, i);
}


size_t RyntraParser::RelationalExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleRelationalExpression;
}

void RyntraParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void RyntraParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}


std::any RyntraParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::RelationalExpressionContext* RyntraParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, RyntraParser::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    shiftExpression();
    setState(267);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 876173328384) != 0)) {
      setState(263);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 876173328384) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(264);
      shiftExpression();
      setState(269);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftExpressionContext ------------------------------------------------------------------

RyntraParser::ShiftExpressionContext::ShiftExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::AdditiveExpressionContext *> RyntraParser::ShiftExpressionContext::additiveExpression() {
  return getRuleContexts<RyntraParser::AdditiveExpressionContext>();
}

RyntraParser::AdditiveExpressionContext* RyntraParser::ShiftExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<RyntraParser::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::ShiftExpressionContext::LSHIFT() {
  return getTokens(RyntraParser::LSHIFT);
}

tree::TerminalNode* RyntraParser::ShiftExpressionContext::LSHIFT(size_t i) {
  return getToken(RyntraParser::LSHIFT, i);
}

std::vector<tree::TerminalNode *> RyntraParser::ShiftExpressionContext::RSHIFT() {
  return getTokens(RyntraParser::RSHIFT);
}

tree::TerminalNode* RyntraParser::ShiftExpressionContext::RSHIFT(size_t i) {
  return getToken(RyntraParser::RSHIFT, i);
}


size_t RyntraParser::ShiftExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleShiftExpression;
}

void RyntraParser::ShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpression(this);
}

void RyntraParser::ShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpression(this);
}


std::any RyntraParser::ShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::ShiftExpressionContext* RyntraParser::shiftExpression() {
  ShiftExpressionContext *_localctx = _tracker.createInstance<ShiftExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, RyntraParser::RuleShiftExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    additiveExpression();
    setState(275);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LSHIFT

    || _la == RyntraParser::RSHIFT) {
      setState(271);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::LSHIFT

      || _la == RyntraParser::RSHIFT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(272);
      additiveExpression();
      setState(277);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

RyntraParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::MultiplicativeExpressionContext *> RyntraParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<RyntraParser::MultiplicativeExpressionContext>();
}

RyntraParser::MultiplicativeExpressionContext* RyntraParser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<RyntraParser::MultiplicativeExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::AdditiveExpressionContext::PLUS() {
  return getTokens(RyntraParser::PLUS);
}

tree::TerminalNode* RyntraParser::AdditiveExpressionContext::PLUS(size_t i) {
  return getToken(RyntraParser::PLUS, i);
}

std::vector<tree::TerminalNode *> RyntraParser::AdditiveExpressionContext::MINUS() {
  return getTokens(RyntraParser::MINUS);
}

tree::TerminalNode* RyntraParser::AdditiveExpressionContext::MINUS(size_t i) {
  return getToken(RyntraParser::MINUS, i);
}


size_t RyntraParser::AdditiveExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleAdditiveExpression;
}

void RyntraParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void RyntraParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}


std::any RyntraParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::AdditiveExpressionContext* RyntraParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 52, RyntraParser::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    multiplicativeExpression();
    setState(283);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::PLUS

    || _la == RyntraParser::MINUS) {
      setState(279);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::PLUS

      || _la == RyntraParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(280);
      multiplicativeExpression();
      setState(285);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

RyntraParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::UnaryExpressionContext *> RyntraParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<RyntraParser::UnaryExpressionContext>();
}

RyntraParser::UnaryExpressionContext* RyntraParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<RyntraParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> RyntraParser::MultiplicativeExpressionContext::MULT() {
  return getTokens(RyntraParser::MULT);
}

tree::TerminalNode* RyntraParser::MultiplicativeExpressionContext::MULT(size_t i) {
  return getToken(RyntraParser::MULT, i);
}

std::vector<tree::TerminalNode *> RyntraParser::MultiplicativeExpressionContext::DIV() {
  return getTokens(RyntraParser::DIV);
}

tree::TerminalNode* RyntraParser::MultiplicativeExpressionContext::DIV(size_t i) {
  return getToken(RyntraParser::DIV, i);
}

std::vector<tree::TerminalNode *> RyntraParser::MultiplicativeExpressionContext::MOD() {
  return getTokens(RyntraParser::MOD);
}

tree::TerminalNode* RyntraParser::MultiplicativeExpressionContext::MOD(size_t i) {
  return getToken(RyntraParser::MOD, i);
}


size_t RyntraParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleMultiplicativeExpression;
}

void RyntraParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void RyntraParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}


std::any RyntraParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::MultiplicativeExpressionContext* RyntraParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 54, RyntraParser::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    unaryExpression();
    setState(291);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7340032) != 0)) {
      setState(287);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 7340032) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(288);
      unaryExpression();
      setState(293);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

RyntraParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::PostfixExpressionContext* RyntraParser::UnaryExpressionContext::postfixExpression() {
  return getRuleContext<RyntraParser::PostfixExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::UnaryExpressionContext::NOT() {
  return getToken(RyntraParser::NOT, 0);
}

RyntraParser::UnaryExpressionContext* RyntraParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<RyntraParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::UnaryExpressionContext::BIT_NOT() {
  return getToken(RyntraParser::BIT_NOT, 0);
}

tree::TerminalNode* RyntraParser::UnaryExpressionContext::MINUS() {
  return getToken(RyntraParser::MINUS, 0);
}


size_t RyntraParser::UnaryExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleUnaryExpression;
}

void RyntraParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void RyntraParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}


std::any RyntraParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::UnaryExpressionContext* RyntraParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 56, RyntraParser::RuleUnaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(301);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::TRUE:
      case RyntraParser::FALSE:
      case RyntraParser::LPAREN:
      case RyntraParser::STRING_LITERAL:
      case RyntraParser::IDENTIFIER:
      case RyntraParser::INTEGER_LITERAL:
      case RyntraParser::FLOAT_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(294);
        postfixExpression(0);
        break;
      }

      case RyntraParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(295);
        match(RyntraParser::NOT);
        setState(296);
        unaryExpression();
        break;
      }

      case RyntraParser::BIT_NOT: {
        enterOuterAlt(_localctx, 3);
        setState(297);
        match(RyntraParser::BIT_NOT);
        setState(298);
        unaryExpression();
        break;
      }

      case RyntraParser::MINUS: {
        enterOuterAlt(_localctx, 4);
        setState(299);
        match(RyntraParser::MINUS);
        setState(300);
        unaryExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExpressionContext ------------------------------------------------------------------

RyntraParser::PostfixExpressionContext::PostfixExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::PrimaryExpressionContext* RyntraParser::PostfixExpressionContext::primaryExpression() {
  return getRuleContext<RyntraParser::PrimaryExpressionContext>(0);
}

RyntraParser::PostfixExpressionContext* RyntraParser::PostfixExpressionContext::postfixExpression() {
  return getRuleContext<RyntraParser::PostfixExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::PostfixExpressionContext::LBRACKET() {
  return getToken(RyntraParser::LBRACKET, 0);
}

RyntraParser::ExpressionContext* RyntraParser::PostfixExpressionContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::PostfixExpressionContext::RBRACKET() {
  return getToken(RyntraParser::RBRACKET, 0);
}

tree::TerminalNode* RyntraParser::PostfixExpressionContext::INC() {
  return getToken(RyntraParser::INC, 0);
}

tree::TerminalNode* RyntraParser::PostfixExpressionContext::DEC() {
  return getToken(RyntraParser::DEC, 0);
}


size_t RyntraParser::PostfixExpressionContext::getRuleIndex() const {
  return RyntraParser::RulePostfixExpression;
}

void RyntraParser::PostfixExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostfixExpression(this);
}

void RyntraParser::PostfixExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostfixExpression(this);
}


std::any RyntraParser::PostfixExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitPostfixExpression(this);
  else
    return visitor->visitChildren(this);
}


RyntraParser::PostfixExpressionContext* RyntraParser::postfixExpression() {
   return postfixExpression(0);
}

RyntraParser::PostfixExpressionContext* RyntraParser::postfixExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  RyntraParser::PostfixExpressionContext *_localctx = _tracker.createInstance<PostfixExpressionContext>(_ctx, parentState);
  RyntraParser::PostfixExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, RyntraParser::RulePostfixExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(304);
    primaryExpression();
    _ctx->stop = _input->LT(-1);
    setState(317);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(315);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<PostfixExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RulePostfixExpression);
          setState(306);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(307);
          match(RyntraParser::LBRACKET);
          setState(308);
          expression();
          setState(309);
          match(RyntraParser::RBRACKET);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<PostfixExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RulePostfixExpression);
          setState(311);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(312);
          match(RyntraParser::INC);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<PostfixExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RulePostfixExpression);
          setState(313);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(314);
          match(RyntraParser::DEC);
          break;
        }

        default:
          break;
        } 
      }
      setState(319);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

RyntraParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::LiteralContext* RyntraParser::PrimaryExpressionContext::literal() {
  return getRuleContext<RyntraParser::LiteralContext>(0);
}

RyntraParser::FunctionCallContext* RyntraParser::PrimaryExpressionContext::functionCall() {
  return getRuleContext<RyntraParser::FunctionCallContext>(0);
}

tree::TerminalNode* RyntraParser::PrimaryExpressionContext::IDENTIFIER() {
  return getToken(RyntraParser::IDENTIFIER, 0);
}

tree::TerminalNode* RyntraParser::PrimaryExpressionContext::LPAREN() {
  return getToken(RyntraParser::LPAREN, 0);
}

RyntraParser::ExpressionContext* RyntraParser::PrimaryExpressionContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::PrimaryExpressionContext::RPAREN() {
  return getToken(RyntraParser::RPAREN, 0);
}


size_t RyntraParser::PrimaryExpressionContext::getRuleIndex() const {
  return RyntraParser::RulePrimaryExpression;
}

void RyntraParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void RyntraParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}


std::any RyntraParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::PrimaryExpressionContext* RyntraParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 60, RyntraParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(327);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(320);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(321);
      functionCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(322);
      match(RyntraParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(323);
      match(RyntraParser::LPAREN);
      setState(324);
      expression();
      setState(325);
      match(RyntraParser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

RyntraParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RyntraParser::LiteralContext::STRING_LITERAL() {
  return getToken(RyntraParser::STRING_LITERAL, 0);
}

tree::TerminalNode* RyntraParser::LiteralContext::INTEGER_LITERAL() {
  return getToken(RyntraParser::INTEGER_LITERAL, 0);
}

tree::TerminalNode* RyntraParser::LiteralContext::FLOAT_LITERAL() {
  return getToken(RyntraParser::FLOAT_LITERAL, 0);
}

tree::TerminalNode* RyntraParser::LiteralContext::TRUE() {
  return getToken(RyntraParser::TRUE, 0);
}

tree::TerminalNode* RyntraParser::LiteralContext::FALSE() {
  return getToken(RyntraParser::FALSE, 0);
}


size_t RyntraParser::LiteralContext::getRuleIndex() const {
  return RyntraParser::RuleLiteral;
}

void RyntraParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void RyntraParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any RyntraParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::LiteralContext* RyntraParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 62, RyntraParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 29273397577908608) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool RyntraParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 29: return postfixExpressionSempred(antlrcpp::downCast<PostfixExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool RyntraParser::postfixExpressionSempred(PostfixExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void RyntraParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ryntraParserInitialize();
#else
  ::antlr4::internal::call_once(ryntraParserOnceFlag, ryntraParserInitialize);
#endif
}
