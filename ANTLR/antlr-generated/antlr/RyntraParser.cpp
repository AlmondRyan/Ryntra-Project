
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
      "'+'", "'-'", "'++'", "'--'", "'*'", "'/'", "'%'", "'='", "'+='", 
      "'-='", "'*='", "'/='", "'%='", "'&='", "'|='", "'^='", "'<<='", "'>>='", 
      "'>'", "'<'", "'=='", "'>='", "'<='", "'&&'", "'||'", "'!'", "';'", 
      "'('", "')'", "'{'", "'}'", "','", "", "", "", "", "", "'&'", "'|'", 
      "'^'", "'~'", "'<<'", "'>>'"
    },
    std::vector<std::string>{
      "", "INT", "RETURN", "STRING", "IF", "ELSE", "BOOL", "TRUE", "FALSE", 
      "WHILE", "FOR", "BREAK", "CONTINUE", "LONG", "PLUS", "MINUS", "INC", 
      "DEC", "MULT", "DIV", "MOD", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", 
      "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", 
      "XOR_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "GREATER", "LESS", 
      "COND_EQUAL", "GREATER_EQ", "LESS_EQ", "LOGIC_AND", "LOGIC_OR", "NOT", 
      "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "STRING_LITERAL", 
      "IDENTIFIER", "INTEGER_LITERAL", "LINE_COMMENT", "WS", "BIT_AND", 
      "BIT_OR", "BIT_XOR", "BIT_NOT", "LSHIFT", "RSHIFT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,56,315,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,1,0,4,0,66,8,0,11,0,12,0,67,1,0,1,0,
  	1,1,1,1,1,1,1,1,3,1,76,8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,5,2,87,
  	8,2,10,2,12,2,90,9,2,1,3,1,3,5,3,94,8,3,10,3,12,3,97,9,3,1,3,1,3,1,4,
  	1,4,1,4,1,4,1,4,1,4,3,4,107,8,4,1,5,1,5,1,5,1,5,3,5,113,8,5,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,3,6,140,8,6,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,3,
  	8,151,8,8,1,9,1,9,1,9,3,9,156,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,11,
  	1,11,1,11,1,11,1,11,3,11,169,8,11,1,11,1,11,3,11,173,8,11,1,11,1,11,1,
  	11,3,11,178,8,11,1,11,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,14,3,
  	14,190,8,14,1,14,1,14,1,15,1,15,1,15,5,15,197,8,15,10,15,12,15,200,9,
  	15,1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,18,1,18,5,18,211,8,18,10,18,12,
  	18,214,9,18,1,19,1,19,1,19,5,19,219,8,19,10,19,12,19,222,9,19,1,20,1,
  	20,1,20,5,20,227,8,20,10,20,12,20,230,9,20,1,21,1,21,1,21,5,21,235,8,
  	21,10,21,12,21,238,9,21,1,22,1,22,1,22,5,22,243,8,22,10,22,12,22,246,
  	9,22,1,23,1,23,1,23,5,23,251,8,23,10,23,12,23,254,9,23,1,24,1,24,1,24,
  	5,24,259,8,24,10,24,12,24,262,9,24,1,25,1,25,1,25,5,25,267,8,25,10,25,
  	12,25,270,9,25,1,26,1,26,1,26,5,26,275,8,26,10,26,12,26,278,9,26,1,27,
  	1,27,1,27,5,27,283,8,27,10,27,12,27,286,9,27,1,28,1,28,1,28,1,28,1,28,
  	1,28,1,28,3,28,295,8,28,1,29,1,29,1,29,1,29,1,29,3,29,302,8,29,1,30,1,
  	30,1,30,1,30,1,30,1,30,1,30,3,30,311,8,30,1,31,1,31,1,31,0,0,32,0,2,4,
  	6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,
  	54,56,58,60,62,0,6,1,0,21,31,2,0,32,33,35,36,1,0,55,56,1,0,14,15,1,0,
  	18,20,3,0,7,8,46,46,48,48,329,0,65,1,0,0,0,2,71,1,0,0,0,4,80,1,0,0,0,
  	6,91,1,0,0,0,8,106,1,0,0,0,10,108,1,0,0,0,12,139,1,0,0,0,14,141,1,0,0,
  	0,16,144,1,0,0,0,18,152,1,0,0,0,20,157,1,0,0,0,22,163,1,0,0,0,24,182,
  	1,0,0,0,26,184,1,0,0,0,28,186,1,0,0,0,30,193,1,0,0,0,32,201,1,0,0,0,34,
  	205,1,0,0,0,36,207,1,0,0,0,38,215,1,0,0,0,40,223,1,0,0,0,42,231,1,0,0,
  	0,44,239,1,0,0,0,46,247,1,0,0,0,48,255,1,0,0,0,50,263,1,0,0,0,52,271,
  	1,0,0,0,54,279,1,0,0,0,56,294,1,0,0,0,58,301,1,0,0,0,60,310,1,0,0,0,62,
  	312,1,0,0,0,64,66,3,2,1,0,65,64,1,0,0,0,66,67,1,0,0,0,67,65,1,0,0,0,67,
  	68,1,0,0,0,68,69,1,0,0,0,69,70,5,0,0,1,70,1,1,0,0,0,71,72,3,8,4,0,72,
  	73,5,47,0,0,73,75,5,41,0,0,74,76,3,4,2,0,75,74,1,0,0,0,75,76,1,0,0,0,
  	76,77,1,0,0,0,77,78,5,42,0,0,78,79,3,6,3,0,79,3,1,0,0,0,80,81,3,8,4,0,
  	81,88,5,47,0,0,82,83,5,45,0,0,83,84,3,8,4,0,84,85,5,47,0,0,85,87,1,0,
  	0,0,86,82,1,0,0,0,87,90,1,0,0,0,88,86,1,0,0,0,88,89,1,0,0,0,89,5,1,0,
  	0,0,90,88,1,0,0,0,91,95,5,43,0,0,92,94,3,12,6,0,93,92,1,0,0,0,94,97,1,
  	0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,96,98,1,0,0,0,97,95,1,0,0,0,98,99,5,
  	44,0,0,99,7,1,0,0,0,100,107,5,1,0,0,101,107,5,3,0,0,102,107,5,6,0,0,103,
  	107,5,13,0,0,104,105,5,13,0,0,105,107,5,13,0,0,106,100,1,0,0,0,106,101,
  	1,0,0,0,106,102,1,0,0,0,106,103,1,0,0,0,106,104,1,0,0,0,107,9,1,0,0,0,
  	108,109,3,8,4,0,109,112,5,47,0,0,110,111,5,21,0,0,111,113,3,34,17,0,112,
  	110,1,0,0,0,112,113,1,0,0,0,113,11,1,0,0,0,114,115,3,28,14,0,115,116,
  	5,40,0,0,116,140,1,0,0,0,117,118,3,34,17,0,118,119,5,40,0,0,119,140,1,
  	0,0,0,120,121,3,10,5,0,121,122,5,40,0,0,122,140,1,0,0,0,123,124,3,14,
  	7,0,124,125,5,40,0,0,125,140,1,0,0,0,126,127,3,32,16,0,127,128,5,40,0,
  	0,128,140,1,0,0,0,129,140,3,16,8,0,130,140,3,20,10,0,131,140,3,22,11,
  	0,132,133,3,24,12,0,133,134,5,40,0,0,134,140,1,0,0,0,135,136,3,26,13,
  	0,136,137,5,40,0,0,137,140,1,0,0,0,138,140,5,40,0,0,139,114,1,0,0,0,139,
  	117,1,0,0,0,139,120,1,0,0,0,139,123,1,0,0,0,139,126,1,0,0,0,139,129,1,
  	0,0,0,139,130,1,0,0,0,139,131,1,0,0,0,139,132,1,0,0,0,139,135,1,0,0,0,
  	139,138,1,0,0,0,140,13,1,0,0,0,141,142,5,2,0,0,142,143,3,34,17,0,143,
  	15,1,0,0,0,144,145,5,4,0,0,145,146,5,41,0,0,146,147,3,34,17,0,147,148,
  	5,42,0,0,148,150,3,6,3,0,149,151,3,18,9,0,150,149,1,0,0,0,150,151,1,0,
  	0,0,151,17,1,0,0,0,152,155,5,5,0,0,153,156,3,16,8,0,154,156,3,6,3,0,155,
  	153,1,0,0,0,155,154,1,0,0,0,156,19,1,0,0,0,157,158,5,9,0,0,158,159,5,
  	41,0,0,159,160,3,34,17,0,160,161,5,42,0,0,161,162,3,6,3,0,162,21,1,0,
  	0,0,163,164,5,10,0,0,164,168,5,41,0,0,165,169,3,10,5,0,166,169,3,32,16,
  	0,167,169,3,34,17,0,168,165,1,0,0,0,168,166,1,0,0,0,168,167,1,0,0,0,168,
  	169,1,0,0,0,169,170,1,0,0,0,170,172,5,40,0,0,171,173,3,34,17,0,172,171,
  	1,0,0,0,172,173,1,0,0,0,173,174,1,0,0,0,174,177,5,40,0,0,175,178,3,32,
  	16,0,176,178,3,34,17,0,177,175,1,0,0,0,177,176,1,0,0,0,177,178,1,0,0,
  	0,178,179,1,0,0,0,179,180,5,42,0,0,180,181,3,6,3,0,181,23,1,0,0,0,182,
  	183,5,11,0,0,183,25,1,0,0,0,184,185,5,12,0,0,185,27,1,0,0,0,186,187,5,
  	47,0,0,187,189,5,41,0,0,188,190,3,30,15,0,189,188,1,0,0,0,189,190,1,0,
  	0,0,190,191,1,0,0,0,191,192,5,42,0,0,192,29,1,0,0,0,193,198,3,34,17,0,
  	194,195,5,45,0,0,195,197,3,34,17,0,196,194,1,0,0,0,197,200,1,0,0,0,198,
  	196,1,0,0,0,198,199,1,0,0,0,199,31,1,0,0,0,200,198,1,0,0,0,201,202,5,
  	47,0,0,202,203,7,0,0,0,203,204,3,34,17,0,204,33,1,0,0,0,205,206,3,36,
  	18,0,206,35,1,0,0,0,207,212,3,38,19,0,208,209,5,38,0,0,209,211,3,38,19,
  	0,210,208,1,0,0,0,211,214,1,0,0,0,212,210,1,0,0,0,212,213,1,0,0,0,213,
  	37,1,0,0,0,214,212,1,0,0,0,215,220,3,40,20,0,216,217,5,37,0,0,217,219,
  	3,40,20,0,218,216,1,0,0,0,219,222,1,0,0,0,220,218,1,0,0,0,220,221,1,0,
  	0,0,221,39,1,0,0,0,222,220,1,0,0,0,223,228,3,42,21,0,224,225,5,52,0,0,
  	225,227,3,42,21,0,226,224,1,0,0,0,227,230,1,0,0,0,228,226,1,0,0,0,228,
  	229,1,0,0,0,229,41,1,0,0,0,230,228,1,0,0,0,231,236,3,44,22,0,232,233,
  	5,53,0,0,233,235,3,44,22,0,234,232,1,0,0,0,235,238,1,0,0,0,236,234,1,
  	0,0,0,236,237,1,0,0,0,237,43,1,0,0,0,238,236,1,0,0,0,239,244,3,46,23,
  	0,240,241,5,51,0,0,241,243,3,46,23,0,242,240,1,0,0,0,243,246,1,0,0,0,
  	244,242,1,0,0,0,244,245,1,0,0,0,245,45,1,0,0,0,246,244,1,0,0,0,247,252,
  	3,48,24,0,248,249,5,34,0,0,249,251,3,48,24,0,250,248,1,0,0,0,251,254,
  	1,0,0,0,252,250,1,0,0,0,252,253,1,0,0,0,253,47,1,0,0,0,254,252,1,0,0,
  	0,255,260,3,50,25,0,256,257,7,1,0,0,257,259,3,50,25,0,258,256,1,0,0,0,
  	259,262,1,0,0,0,260,258,1,0,0,0,260,261,1,0,0,0,261,49,1,0,0,0,262,260,
  	1,0,0,0,263,268,3,52,26,0,264,265,7,2,0,0,265,267,3,52,26,0,266,264,1,
  	0,0,0,267,270,1,0,0,0,268,266,1,0,0,0,268,269,1,0,0,0,269,51,1,0,0,0,
  	270,268,1,0,0,0,271,276,3,54,27,0,272,273,7,3,0,0,273,275,3,54,27,0,274,
  	272,1,0,0,0,275,278,1,0,0,0,276,274,1,0,0,0,276,277,1,0,0,0,277,53,1,
  	0,0,0,278,276,1,0,0,0,279,284,3,56,28,0,280,281,7,4,0,0,281,283,3,56,
  	28,0,282,280,1,0,0,0,283,286,1,0,0,0,284,282,1,0,0,0,284,285,1,0,0,0,
  	285,55,1,0,0,0,286,284,1,0,0,0,287,295,3,58,29,0,288,289,5,39,0,0,289,
  	295,3,56,28,0,290,291,5,54,0,0,291,295,3,56,28,0,292,293,5,15,0,0,293,
  	295,3,56,28,0,294,287,1,0,0,0,294,288,1,0,0,0,294,290,1,0,0,0,294,292,
  	1,0,0,0,295,57,1,0,0,0,296,302,3,60,30,0,297,298,5,47,0,0,298,302,5,16,
  	0,0,299,300,5,47,0,0,300,302,5,17,0,0,301,296,1,0,0,0,301,297,1,0,0,0,
  	301,299,1,0,0,0,302,59,1,0,0,0,303,311,3,62,31,0,304,311,3,28,14,0,305,
  	311,5,47,0,0,306,307,5,41,0,0,307,308,3,34,17,0,308,309,5,42,0,0,309,
  	311,1,0,0,0,310,303,1,0,0,0,310,304,1,0,0,0,310,305,1,0,0,0,310,306,1,
  	0,0,0,311,61,1,0,0,0,312,313,7,5,0,0,313,63,1,0,0,0,27,67,75,88,95,106,
  	112,139,150,155,168,172,177,189,198,212,220,228,236,244,252,260,268,276,
  	284,294,301,310
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
      ((1ULL << _la) & 8266) != 0));
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
      ((1ULL << _la) & 8266) != 0)) {
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
      ((1ULL << _la) & 18510828009471966) != 0)) {
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
    setState(106);
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
    setState(108);
    typeSpecifier();
    setState(109);
    match(RyntraParser::IDENTIFIER);
    setState(112);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ASSIGN) {
      setState(110);
      match(RyntraParser::ASSIGN);
      setState(111);
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
    setState(139);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(114);
      functionCall();
      setState(115);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(117);
      expression();
      setState(118);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(120);
      variableDeclaration();
      setState(121);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(123);
      returnStatement();
      setState(124);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(126);
      assignment();
      setState(127);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(129);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(130);
      whileStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(131);
      forStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(132);
      breakStatement();
      setState(133);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(135);
      continueStatement();
      setState(136);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(138);
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
    setState(141);
    match(RyntraParser::RETURN);
    setState(142);
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
    setState(144);
    match(RyntraParser::IF);
    setState(145);
    match(RyntraParser::LPAREN);
    setState(146);
    expression();
    setState(147);
    match(RyntraParser::RPAREN);
    setState(148);
    block();
    setState(150);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ELSE) {
      setState(149);
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
    setState(152);
    match(RyntraParser::ELSE);
    setState(155);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::IF: {
        setState(153);
        ifStatement();
        break;
      }

      case RyntraParser::LBRACE: {
        setState(154);
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
    setState(157);
    match(RyntraParser::WHILE);
    setState(158);
    match(RyntraParser::LPAREN);
    setState(159);
    expression();
    setState(160);
    match(RyntraParser::RPAREN);
    setState(161);
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
    setState(163);
    match(RyntraParser::FOR);
    setState(164);
    match(RyntraParser::LPAREN);
    setState(168);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(165);
      variableDeclaration();
      break;
    }

    case 2: {
      setState(166);
      assignment();
      break;
    }

    case 3: {
      setState(167);
      expression();
      break;
    }

    default:
      break;
    }
    setState(170);
    match(RyntraParser::SEMICOLON);
    setState(172);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 18509728497828224) != 0)) {
      setState(171);
      expression();
    }
    setState(174);
    match(RyntraParser::SEMICOLON);
    setState(177);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(175);
      assignment();
      break;
    }

    case 2: {
      setState(176);
      expression();
      break;
    }

    default:
      break;
    }
    setState(179);
    match(RyntraParser::RPAREN);
    setState(180);
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
    setState(182);
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
    setState(184);
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
    setState(186);
    match(RyntraParser::IDENTIFIER);
    setState(187);
    match(RyntraParser::LPAREN);

    setState(189);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 18509728497828224) != 0)) {
      setState(188);
      argumentList();
    }
    setState(191);
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
    setState(193);
    expression();
    setState(198);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(194);
      match(RyntraParser::COMMA);
      setState(195);
      expression();
      setState(200);
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

tree::TerminalNode* RyntraParser::AssignmentContext::IDENTIFIER() {
  return getToken(RyntraParser::IDENTIFIER, 0);
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
    setState(201);
    match(RyntraParser::IDENTIFIER);
    setState(202);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4292870144) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(203);
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
    setState(205);
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
    setState(207);
    logicalAndExpression();
    setState(212);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_OR) {
      setState(208);
      match(RyntraParser::LOGIC_OR);
      setState(209);
      logicalAndExpression();
      setState(214);
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
    setState(215);
    inclusiveOrExpression();
    setState(220);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_AND) {
      setState(216);
      match(RyntraParser::LOGIC_AND);
      setState(217);
      inclusiveOrExpression();
      setState(222);
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
    setState(223);
    exclusiveOrExpression();
    setState(228);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::BIT_OR) {
      setState(224);
      match(RyntraParser::BIT_OR);
      setState(225);
      exclusiveOrExpression();
      setState(230);
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
    setState(231);
    andExpression();
    setState(236);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::BIT_XOR) {
      setState(232);
      match(RyntraParser::BIT_XOR);
      setState(233);
      andExpression();
      setState(238);
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
    setState(239);
    equalityExpression();
    setState(244);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::BIT_AND) {
      setState(240);
      match(RyntraParser::BIT_AND);
      setState(241);
      equalityExpression();
      setState(246);
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
    setState(247);
    relationalExpression();
    setState(252);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COND_EQUAL) {
      setState(248);
      match(RyntraParser::COND_EQUAL);
      setState(249);
      relationalExpression();
      setState(254);
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
    setState(255);
    shiftExpression();
    setState(260);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 115964116992) != 0)) {
      setState(256);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 115964116992) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(257);
      shiftExpression();
      setState(262);
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
    setState(263);
    additiveExpression();
    setState(268);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LSHIFT

    || _la == RyntraParser::RSHIFT) {
      setState(264);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::LSHIFT

      || _la == RyntraParser::RSHIFT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(265);
      additiveExpression();
      setState(270);
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
    setState(271);
    multiplicativeExpression();
    setState(276);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::PLUS

    || _la == RyntraParser::MINUS) {
      setState(272);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::PLUS

      || _la == RyntraParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(273);
      multiplicativeExpression();
      setState(278);
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
    setState(279);
    unaryExpression();
    setState(284);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1835008) != 0)) {
      setState(280);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1835008) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(281);
      unaryExpression();
      setState(286);
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
    setState(294);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::TRUE:
      case RyntraParser::FALSE:
      case RyntraParser::LPAREN:
      case RyntraParser::STRING_LITERAL:
      case RyntraParser::IDENTIFIER:
      case RyntraParser::INTEGER_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(287);
        postfixExpression();
        break;
      }

      case RyntraParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(288);
        match(RyntraParser::NOT);
        setState(289);
        unaryExpression();
        break;
      }

      case RyntraParser::BIT_NOT: {
        enterOuterAlt(_localctx, 3);
        setState(290);
        match(RyntraParser::BIT_NOT);
        setState(291);
        unaryExpression();
        break;
      }

      case RyntraParser::MINUS: {
        enterOuterAlt(_localctx, 4);
        setState(292);
        match(RyntraParser::MINUS);
        setState(293);
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

tree::TerminalNode* RyntraParser::PostfixExpressionContext::IDENTIFIER() {
  return getToken(RyntraParser::IDENTIFIER, 0);
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
  PostfixExpressionContext *_localctx = _tracker.createInstance<PostfixExpressionContext>(_ctx, getState());
  enterRule(_localctx, 58, RyntraParser::RulePostfixExpression);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(296);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(297);
      match(RyntraParser::IDENTIFIER);
      setState(298);
      match(RyntraParser::INC);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(299);
      match(RyntraParser::IDENTIFIER);
      setState(300);
      match(RyntraParser::DEC);
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
    setState(310);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(303);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(304);
      functionCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(305);
      match(RyntraParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(306);
      match(RyntraParser::LPAREN);
      setState(307);
      expression();
      setState(308);
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
    setState(312);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 351843720888704) != 0))) {
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

void RyntraParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ryntraParserInitialize();
#else
  ::antlr4::internal::call_once(ryntraParserOnceFlag, ryntraParserInitialize);
#endif
}
