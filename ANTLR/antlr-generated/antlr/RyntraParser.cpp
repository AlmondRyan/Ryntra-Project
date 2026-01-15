
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
      "expression", "logicalOrExpression", "logicalAndExpression", "equalityExpression", 
      "relationalExpression", "additiveExpression", "multiplicativeExpression", 
      "unaryExpression", "postfixExpression", "primaryExpression", "literal"
    },
    std::vector<std::string>{
      "", "'int'", "'return'", "'string'", "'if'", "'else'", "'bool'", "'true'", 
      "'false'", "'while'", "'for'", "'break'", "'continue'", "'long'", 
      "'+'", "'-'", "'++'", "'--'", "'*'", "'/'", "'='", "'>'", "'<'", "'=='", 
      "'>='", "'<='", "'&&'", "'||'", "'!'", "';'", "'('", "')'", "'{'", 
      "'}'", "','"
    },
    std::vector<std::string>{
      "", "INT", "RETURN", "STRING", "IF", "ELSE", "BOOL", "TRUE", "FALSE", 
      "WHILE", "FOR", "BREAK", "CONTINUE", "LONG", "PLUS", "MINUS", "INC", 
      "DEC", "MULT", "DIV", "ASSIGN", "GREATER", "LESS", "COND_EQUAL", "GREATER_EQ", 
      "LESS_EQ", "LOGIC_AND", "LOGIC_OR", "NOT", "SEMICOLON", "LPAREN", 
      "RPAREN", "LBRACE", "RBRACE", "COMMA", "STRING_LITERAL", "IDENTIFIER", 
      "INTEGER_LITERAL", "LINE_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,273,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,4,
  	0,58,8,0,11,0,12,0,59,1,0,1,0,1,1,1,1,1,1,1,1,3,1,68,8,1,1,1,1,1,1,1,
  	1,2,1,2,1,2,1,2,1,2,1,2,5,2,79,8,2,10,2,12,2,82,9,2,1,3,1,3,5,3,86,8,
  	3,10,3,12,3,89,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,99,8,4,1,5,1,5,
  	1,5,1,5,3,5,105,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,132,8,6,1,7,1,7,
  	1,7,1,8,1,8,1,8,1,8,1,8,1,8,3,8,143,8,8,1,9,1,9,1,9,3,9,148,8,9,1,10,
  	1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,3,11,161,8,11,1,11,
  	1,11,3,11,165,8,11,1,11,1,11,1,11,3,11,170,8,11,1,11,1,11,1,11,1,12,1,
  	12,1,13,1,13,1,14,1,14,1,14,3,14,182,8,14,1,14,1,14,1,15,1,15,1,15,5,
  	15,189,8,15,10,15,12,15,192,9,15,1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,
  	18,1,18,5,18,203,8,18,10,18,12,18,206,9,18,1,19,1,19,1,19,5,19,211,8,
  	19,10,19,12,19,214,9,19,1,20,1,20,1,20,5,20,219,8,20,10,20,12,20,222,
  	9,20,1,21,1,21,1,21,5,21,227,8,21,10,21,12,21,230,9,21,1,22,1,22,1,22,
  	5,22,235,8,22,10,22,12,22,238,9,22,1,23,1,23,1,23,5,23,243,8,23,10,23,
  	12,23,246,9,23,1,24,1,24,1,24,1,24,1,24,3,24,253,8,24,1,25,1,25,1,25,
  	1,25,1,25,3,25,260,8,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,269,8,
  	26,1,27,1,27,1,27,0,0,28,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,
  	34,36,38,40,42,44,46,48,50,52,54,0,4,2,0,21,22,24,25,1,0,14,15,1,0,18,
  	19,3,0,7,8,35,35,37,37,286,0,57,1,0,0,0,2,63,1,0,0,0,4,72,1,0,0,0,6,83,
  	1,0,0,0,8,98,1,0,0,0,10,100,1,0,0,0,12,131,1,0,0,0,14,133,1,0,0,0,16,
  	136,1,0,0,0,18,144,1,0,0,0,20,149,1,0,0,0,22,155,1,0,0,0,24,174,1,0,0,
  	0,26,176,1,0,0,0,28,178,1,0,0,0,30,185,1,0,0,0,32,193,1,0,0,0,34,197,
  	1,0,0,0,36,199,1,0,0,0,38,207,1,0,0,0,40,215,1,0,0,0,42,223,1,0,0,0,44,
  	231,1,0,0,0,46,239,1,0,0,0,48,252,1,0,0,0,50,259,1,0,0,0,52,268,1,0,0,
  	0,54,270,1,0,0,0,56,58,3,2,1,0,57,56,1,0,0,0,58,59,1,0,0,0,59,57,1,0,
  	0,0,59,60,1,0,0,0,60,61,1,0,0,0,61,62,5,0,0,1,62,1,1,0,0,0,63,64,3,8,
  	4,0,64,65,5,36,0,0,65,67,5,30,0,0,66,68,3,4,2,0,67,66,1,0,0,0,67,68,1,
  	0,0,0,68,69,1,0,0,0,69,70,5,31,0,0,70,71,3,6,3,0,71,3,1,0,0,0,72,73,3,
  	8,4,0,73,80,5,36,0,0,74,75,5,34,0,0,75,76,3,8,4,0,76,77,5,36,0,0,77,79,
  	1,0,0,0,78,74,1,0,0,0,79,82,1,0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,5,
  	1,0,0,0,82,80,1,0,0,0,83,87,5,32,0,0,84,86,3,12,6,0,85,84,1,0,0,0,86,
  	89,1,0,0,0,87,85,1,0,0,0,87,88,1,0,0,0,88,90,1,0,0,0,89,87,1,0,0,0,90,
  	91,5,33,0,0,91,7,1,0,0,0,92,99,5,1,0,0,93,99,5,3,0,0,94,99,5,6,0,0,95,
  	99,5,13,0,0,96,97,5,13,0,0,97,99,5,13,0,0,98,92,1,0,0,0,98,93,1,0,0,0,
  	98,94,1,0,0,0,98,95,1,0,0,0,98,96,1,0,0,0,99,9,1,0,0,0,100,101,3,8,4,
  	0,101,104,5,36,0,0,102,103,5,20,0,0,103,105,3,34,17,0,104,102,1,0,0,0,
  	104,105,1,0,0,0,105,11,1,0,0,0,106,107,3,28,14,0,107,108,5,29,0,0,108,
  	132,1,0,0,0,109,110,3,34,17,0,110,111,5,29,0,0,111,132,1,0,0,0,112,113,
  	3,10,5,0,113,114,5,29,0,0,114,132,1,0,0,0,115,116,3,14,7,0,116,117,5,
  	29,0,0,117,132,1,0,0,0,118,119,3,32,16,0,119,120,5,29,0,0,120,132,1,0,
  	0,0,121,132,3,16,8,0,122,132,3,20,10,0,123,132,3,22,11,0,124,125,3,24,
  	12,0,125,126,5,29,0,0,126,132,1,0,0,0,127,128,3,26,13,0,128,129,5,29,
  	0,0,129,132,1,0,0,0,130,132,5,29,0,0,131,106,1,0,0,0,131,109,1,0,0,0,
  	131,112,1,0,0,0,131,115,1,0,0,0,131,118,1,0,0,0,131,121,1,0,0,0,131,122,
  	1,0,0,0,131,123,1,0,0,0,131,124,1,0,0,0,131,127,1,0,0,0,131,130,1,0,0,
  	0,132,13,1,0,0,0,133,134,5,2,0,0,134,135,3,34,17,0,135,15,1,0,0,0,136,
  	137,5,4,0,0,137,138,5,30,0,0,138,139,3,34,17,0,139,140,5,31,0,0,140,142,
  	3,6,3,0,141,143,3,18,9,0,142,141,1,0,0,0,142,143,1,0,0,0,143,17,1,0,0,
  	0,144,147,5,5,0,0,145,148,3,16,8,0,146,148,3,6,3,0,147,145,1,0,0,0,147,
  	146,1,0,0,0,148,19,1,0,0,0,149,150,5,9,0,0,150,151,5,30,0,0,151,152,3,
  	34,17,0,152,153,5,31,0,0,153,154,3,6,3,0,154,21,1,0,0,0,155,156,5,10,
  	0,0,156,160,5,30,0,0,157,161,3,10,5,0,158,161,3,32,16,0,159,161,3,34,
  	17,0,160,157,1,0,0,0,160,158,1,0,0,0,160,159,1,0,0,0,160,161,1,0,0,0,
  	161,162,1,0,0,0,162,164,5,29,0,0,163,165,3,34,17,0,164,163,1,0,0,0,164,
  	165,1,0,0,0,165,166,1,0,0,0,166,169,5,29,0,0,167,170,3,32,16,0,168,170,
  	3,34,17,0,169,167,1,0,0,0,169,168,1,0,0,0,169,170,1,0,0,0,170,171,1,0,
  	0,0,171,172,5,31,0,0,172,173,3,6,3,0,173,23,1,0,0,0,174,175,5,11,0,0,
  	175,25,1,0,0,0,176,177,5,12,0,0,177,27,1,0,0,0,178,179,5,36,0,0,179,181,
  	5,30,0,0,180,182,3,30,15,0,181,180,1,0,0,0,181,182,1,0,0,0,182,183,1,
  	0,0,0,183,184,5,31,0,0,184,29,1,0,0,0,185,190,3,34,17,0,186,187,5,34,
  	0,0,187,189,3,34,17,0,188,186,1,0,0,0,189,192,1,0,0,0,190,188,1,0,0,0,
  	190,191,1,0,0,0,191,31,1,0,0,0,192,190,1,0,0,0,193,194,5,36,0,0,194,195,
  	5,20,0,0,195,196,3,34,17,0,196,33,1,0,0,0,197,198,3,36,18,0,198,35,1,
  	0,0,0,199,204,3,38,19,0,200,201,5,27,0,0,201,203,3,38,19,0,202,200,1,
  	0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,205,1,0,0,0,205,37,1,0,0,0,
  	206,204,1,0,0,0,207,212,3,40,20,0,208,209,5,26,0,0,209,211,3,40,20,0,
  	210,208,1,0,0,0,211,214,1,0,0,0,212,210,1,0,0,0,212,213,1,0,0,0,213,39,
  	1,0,0,0,214,212,1,0,0,0,215,220,3,42,21,0,216,217,5,23,0,0,217,219,3,
  	42,21,0,218,216,1,0,0,0,219,222,1,0,0,0,220,218,1,0,0,0,220,221,1,0,0,
  	0,221,41,1,0,0,0,222,220,1,0,0,0,223,228,3,44,22,0,224,225,7,0,0,0,225,
  	227,3,44,22,0,226,224,1,0,0,0,227,230,1,0,0,0,228,226,1,0,0,0,228,229,
  	1,0,0,0,229,43,1,0,0,0,230,228,1,0,0,0,231,236,3,46,23,0,232,233,7,1,
  	0,0,233,235,3,46,23,0,234,232,1,0,0,0,235,238,1,0,0,0,236,234,1,0,0,0,
  	236,237,1,0,0,0,237,45,1,0,0,0,238,236,1,0,0,0,239,244,3,48,24,0,240,
  	241,7,2,0,0,241,243,3,48,24,0,242,240,1,0,0,0,243,246,1,0,0,0,244,242,
  	1,0,0,0,244,245,1,0,0,0,245,47,1,0,0,0,246,244,1,0,0,0,247,253,3,50,25,
  	0,248,249,5,28,0,0,249,253,3,48,24,0,250,251,5,15,0,0,251,253,3,48,24,
  	0,252,247,1,0,0,0,252,248,1,0,0,0,252,250,1,0,0,0,253,49,1,0,0,0,254,
  	260,3,52,26,0,255,256,5,36,0,0,256,260,5,16,0,0,257,258,5,36,0,0,258,
  	260,5,17,0,0,259,254,1,0,0,0,259,255,1,0,0,0,259,257,1,0,0,0,260,51,1,
  	0,0,0,261,269,3,54,27,0,262,269,3,28,14,0,263,269,5,36,0,0,264,265,5,
  	30,0,0,265,266,3,34,17,0,266,267,5,31,0,0,267,269,1,0,0,0,268,261,1,0,
  	0,0,268,262,1,0,0,0,268,263,1,0,0,0,268,264,1,0,0,0,269,53,1,0,0,0,270,
  	271,7,3,0,0,271,55,1,0,0,0,23,59,67,80,87,98,104,131,142,147,160,164,
  	169,181,190,204,212,220,228,236,244,252,259,268
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
    setState(57); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(56);
      functionDefinition();
      setState(59); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8266) != 0));
    setState(61);
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
    setState(63);
    typeSpecifier();
    setState(64);
    match(RyntraParser::IDENTIFIER);
    setState(65);
    match(RyntraParser::LPAREN);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8266) != 0)) {
      setState(66);
      parameterList();
    }
    setState(69);
    match(RyntraParser::RPAREN);
    setState(70);
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
    setState(72);
    typeSpecifier();
    setState(73);
    match(RyntraParser::IDENTIFIER);
    setState(80);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(74);
      match(RyntraParser::COMMA);
      setState(75);
      typeSpecifier();
      setState(76);
      match(RyntraParser::IDENTIFIER);
      setState(82);
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
    setState(83);
    match(RyntraParser::LBRACE);
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 242397265886) != 0)) {
      setState(84);
      statement();
      setState(89);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(90);
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
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(92);
      match(RyntraParser::INT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(93);
      match(RyntraParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(94);
      match(RyntraParser::BOOL);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(95);
      match(RyntraParser::LONG);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(96);
      match(RyntraParser::LONG);
      setState(97);
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
    setState(100);
    typeSpecifier();
    setState(101);
    match(RyntraParser::IDENTIFIER);
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ASSIGN) {
      setState(102);
      match(RyntraParser::ASSIGN);
      setState(103);
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
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(106);
      functionCall();
      setState(107);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(109);
      expression();
      setState(110);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(112);
      variableDeclaration();
      setState(113);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(115);
      returnStatement();
      setState(116);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(118);
      assignment();
      setState(119);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(121);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(122);
      whileStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(123);
      forStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(124);
      breakStatement();
      setState(125);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(127);
      continueStatement();
      setState(128);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(130);
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
    setState(133);
    match(RyntraParser::RETURN);
    setState(134);
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
    setState(136);
    match(RyntraParser::IF);
    setState(137);
    match(RyntraParser::LPAREN);
    setState(138);
    expression();
    setState(139);
    match(RyntraParser::RPAREN);
    setState(140);
    block();
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ELSE) {
      setState(141);
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
    setState(144);
    match(RyntraParser::ELSE);
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::IF: {
        setState(145);
        ifStatement();
        break;
      }

      case RyntraParser::LBRACE: {
        setState(146);
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
    setState(149);
    match(RyntraParser::WHILE);
    setState(150);
    match(RyntraParser::LPAREN);
    setState(151);
    expression();
    setState(152);
    match(RyntraParser::RPAREN);
    setState(153);
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
    setState(155);
    match(RyntraParser::FOR);
    setState(156);
    match(RyntraParser::LPAREN);
    setState(160);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(157);
      variableDeclaration();
      break;
    }

    case 2: {
      setState(158);
      assignment();
      break;
    }

    case 3: {
      setState(159);
      expression();
      break;
    }

    default:
      break;
    }
    setState(162);
    match(RyntraParser::SEMICOLON);
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 241860379008) != 0)) {
      setState(163);
      expression();
    }
    setState(166);
    match(RyntraParser::SEMICOLON);
    setState(169);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(167);
      assignment();
      break;
    }

    case 2: {
      setState(168);
      expression();
      break;
    }

    default:
      break;
    }
    setState(171);
    match(RyntraParser::RPAREN);
    setState(172);
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
    setState(174);
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
    setState(176);
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
    setState(178);
    match(RyntraParser::IDENTIFIER);
    setState(179);
    match(RyntraParser::LPAREN);

    setState(181);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 241860379008) != 0)) {
      setState(180);
      argumentList();
    }
    setState(183);
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
    setState(185);
    expression();
    setState(190);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(186);
      match(RyntraParser::COMMA);
      setState(187);
      expression();
      setState(192);
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

tree::TerminalNode* RyntraParser::AssignmentContext::ASSIGN() {
  return getToken(RyntraParser::ASSIGN, 0);
}

RyntraParser::ExpressionContext* RyntraParser::AssignmentContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
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
    match(RyntraParser::ASSIGN);
    setState(195);
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
    setState(197);
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
    setState(199);
    logicalAndExpression();
    setState(204);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_OR) {
      setState(200);
      match(RyntraParser::LOGIC_OR);
      setState(201);
      logicalAndExpression();
      setState(206);
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

std::vector<RyntraParser::EqualityExpressionContext *> RyntraParser::LogicalAndExpressionContext::equalityExpression() {
  return getRuleContexts<RyntraParser::EqualityExpressionContext>();
}

RyntraParser::EqualityExpressionContext* RyntraParser::LogicalAndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<RyntraParser::EqualityExpressionContext>(i);
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
    setState(207);
    equalityExpression();
    setState(212);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_AND) {
      setState(208);
      match(RyntraParser::LOGIC_AND);
      setState(209);
      equalityExpression();
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
  enterRule(_localctx, 40, RyntraParser::RuleEqualityExpression);
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
    relationalExpression();
    setState(220);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COND_EQUAL) {
      setState(216);
      match(RyntraParser::COND_EQUAL);
      setState(217);
      relationalExpression();
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

//----------------- RelationalExpressionContext ------------------------------------------------------------------

RyntraParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RyntraParser::AdditiveExpressionContext *> RyntraParser::RelationalExpressionContext::additiveExpression() {
  return getRuleContexts<RyntraParser::AdditiveExpressionContext>();
}

RyntraParser::AdditiveExpressionContext* RyntraParser::RelationalExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<RyntraParser::AdditiveExpressionContext>(i);
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
  enterRule(_localctx, 42, RyntraParser::RuleRelationalExpression);
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
    additiveExpression();
    setState(228);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 56623104) != 0)) {
      setState(224);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 56623104) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(225);
      additiveExpression();
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
  enterRule(_localctx, 44, RyntraParser::RuleAdditiveExpression);
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
    multiplicativeExpression();
    setState(236);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::PLUS

    || _la == RyntraParser::MINUS) {
      setState(232);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::PLUS

      || _la == RyntraParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(233);
      multiplicativeExpression();
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
  enterRule(_localctx, 46, RyntraParser::RuleMultiplicativeExpression);
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
    unaryExpression();
    setState(244);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::MULT

    || _la == RyntraParser::DIV) {
      setState(240);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::MULT

      || _la == RyntraParser::DIV)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(241);
      unaryExpression();
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
  enterRule(_localctx, 48, RyntraParser::RuleUnaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(252);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::TRUE:
      case RyntraParser::FALSE:
      case RyntraParser::LPAREN:
      case RyntraParser::STRING_LITERAL:
      case RyntraParser::IDENTIFIER:
      case RyntraParser::INTEGER_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(247);
        postfixExpression();
        break;
      }

      case RyntraParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(248);
        match(RyntraParser::NOT);
        setState(249);
        unaryExpression();
        break;
      }

      case RyntraParser::MINUS: {
        enterOuterAlt(_localctx, 3);
        setState(250);
        match(RyntraParser::MINUS);
        setState(251);
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
  enterRule(_localctx, 50, RyntraParser::RulePostfixExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(259);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(254);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(255);
      match(RyntraParser::IDENTIFIER);
      setState(256);
      match(RyntraParser::INC);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(257);
      match(RyntraParser::IDENTIFIER);
      setState(258);
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
  enterRule(_localctx, 52, RyntraParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(268);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(261);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(262);
      functionCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(263);
      match(RyntraParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(264);
      match(RyntraParser::LPAREN);
      setState(265);
      expression();
      setState(266);
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
  enterRule(_localctx, 54, RyntraParser::RuleLiteral);
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
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 171798692224) != 0))) {
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
