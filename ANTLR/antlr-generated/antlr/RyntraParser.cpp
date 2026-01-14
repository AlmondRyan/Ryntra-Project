
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
      "program", "functionDefinition", "parameterList", "block", "variableDeclaration", 
      "statement", "returnStatement", "ifStatement", "elseClause", "functionCall", 
      "argumentList", "assignment", "expression", "logicalOrExpression", 
      "logicalAndExpression", "equalityExpression", "relationalExpression", 
      "additiveExpression", "multiplicativeExpression", "unaryExpression", 
      "primaryExpression", "literal"
    },
    std::vector<std::string>{
      "", "'int'", "'return'", "'string'", "'if'", "'else'", "'bool'", "'true'", 
      "'false'", "'+'", "'-'", "'*'", "'/'", "'='", "'>'", "'<'", "'=='", 
      "'>='", "'<='", "'&&'", "'||'", "'!'", "';'", "'('", "')'", "'{'", 
      "'}'", "','"
    },
    std::vector<std::string>{
      "", "INT", "RETURN", "STRING", "IF", "ELSE", "BOOL", "TRUE", "FALSE", 
      "PLUS", "MINUS", "MULT", "DIV", "ASSIGN", "GREATER", "LESS", "COND_EQUAL", 
      "GREATER_EQ", "LESS_EQ", "LOGIC_AND", "LOGIC_OR", "NOT", "SEMICOLON", 
      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "STRING_LITERAL", 
      "IDENTIFIER", "INTEGER_LITERAL", "LINE_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,32,222,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,1,0,4,0,46,8,0,11,0,12,0,47,1,0,1,0,1,1,1,1,1,1,1,1,3,1,56,8,1,1,1,
  	1,1,1,1,1,2,1,2,1,2,1,2,1,2,5,2,66,8,2,10,2,12,2,69,9,2,1,3,1,3,5,3,73,
  	8,3,10,3,12,3,76,9,3,1,3,1,3,1,4,1,4,1,4,1,4,3,4,84,8,4,1,4,1,4,1,4,1,
  	4,3,4,90,8,4,1,4,1,4,1,4,1,4,3,4,96,8,4,3,4,98,8,4,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,117,8,5,1,6,1,6,
  	1,6,1,7,1,7,1,7,1,7,1,7,1,7,3,7,128,8,7,1,8,1,8,1,8,3,8,133,8,8,1,9,1,
  	9,1,9,3,9,138,8,9,1,9,1,9,1,10,1,10,1,10,5,10,145,8,10,10,10,12,10,148,
  	9,10,1,11,1,11,1,11,1,11,1,12,1,12,1,13,1,13,1,13,5,13,159,8,13,10,13,
  	12,13,162,9,13,1,14,1,14,1,14,5,14,167,8,14,10,14,12,14,170,9,14,1,15,
  	1,15,1,15,5,15,175,8,15,10,15,12,15,178,9,15,1,16,1,16,1,16,5,16,183,
  	8,16,10,16,12,16,186,9,16,1,17,1,17,1,17,5,17,191,8,17,10,17,12,17,194,
  	9,17,1,18,1,18,1,18,5,18,199,8,18,10,18,12,18,202,9,18,1,19,1,19,1,19,
  	1,19,1,19,3,19,209,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,218,8,
  	20,1,21,1,21,1,21,0,0,22,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,
  	34,36,38,40,42,0,4,2,0,14,15,17,18,1,0,9,10,1,0,11,12,3,0,7,8,28,28,30,
  	30,229,0,45,1,0,0,0,2,51,1,0,0,0,4,60,1,0,0,0,6,70,1,0,0,0,8,97,1,0,0,
  	0,10,116,1,0,0,0,12,118,1,0,0,0,14,121,1,0,0,0,16,129,1,0,0,0,18,134,
  	1,0,0,0,20,141,1,0,0,0,22,149,1,0,0,0,24,153,1,0,0,0,26,155,1,0,0,0,28,
  	163,1,0,0,0,30,171,1,0,0,0,32,179,1,0,0,0,34,187,1,0,0,0,36,195,1,0,0,
  	0,38,208,1,0,0,0,40,217,1,0,0,0,42,219,1,0,0,0,44,46,3,2,1,0,45,44,1,
  	0,0,0,46,47,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,49,1,0,0,0,49,50,5,
  	0,0,1,50,1,1,0,0,0,51,52,5,1,0,0,52,53,5,29,0,0,53,55,5,23,0,0,54,56,
  	3,4,2,0,55,54,1,0,0,0,55,56,1,0,0,0,56,57,1,0,0,0,57,58,5,24,0,0,58,59,
  	3,6,3,0,59,3,1,0,0,0,60,61,5,1,0,0,61,67,5,29,0,0,62,63,5,27,0,0,63,64,
  	5,1,0,0,64,66,5,29,0,0,65,62,1,0,0,0,66,69,1,0,0,0,67,65,1,0,0,0,67,68,
  	1,0,0,0,68,5,1,0,0,0,69,67,1,0,0,0,70,74,5,25,0,0,71,73,3,10,5,0,72,71,
  	1,0,0,0,73,76,1,0,0,0,74,72,1,0,0,0,74,75,1,0,0,0,75,77,1,0,0,0,76,74,
  	1,0,0,0,77,78,5,26,0,0,78,7,1,0,0,0,79,80,5,1,0,0,80,83,5,29,0,0,81,82,
  	5,13,0,0,82,84,3,24,12,0,83,81,1,0,0,0,83,84,1,0,0,0,84,98,1,0,0,0,85,
  	86,5,3,0,0,86,89,5,29,0,0,87,88,5,13,0,0,88,90,3,24,12,0,89,87,1,0,0,
  	0,89,90,1,0,0,0,90,98,1,0,0,0,91,92,5,6,0,0,92,95,5,29,0,0,93,94,5,13,
  	0,0,94,96,3,24,12,0,95,93,1,0,0,0,95,96,1,0,0,0,96,98,1,0,0,0,97,79,1,
  	0,0,0,97,85,1,0,0,0,97,91,1,0,0,0,98,9,1,0,0,0,99,100,3,18,9,0,100,101,
  	5,22,0,0,101,117,1,0,0,0,102,103,3,24,12,0,103,104,5,22,0,0,104,117,1,
  	0,0,0,105,106,3,8,4,0,106,107,5,22,0,0,107,117,1,0,0,0,108,109,3,12,6,
  	0,109,110,5,22,0,0,110,117,1,0,0,0,111,112,3,22,11,0,112,113,5,22,0,0,
  	113,117,1,0,0,0,114,117,3,14,7,0,115,117,5,22,0,0,116,99,1,0,0,0,116,
  	102,1,0,0,0,116,105,1,0,0,0,116,108,1,0,0,0,116,111,1,0,0,0,116,114,1,
  	0,0,0,116,115,1,0,0,0,117,11,1,0,0,0,118,119,5,2,0,0,119,120,3,24,12,
  	0,120,13,1,0,0,0,121,122,5,4,0,0,122,123,5,23,0,0,123,124,3,24,12,0,124,
  	125,5,24,0,0,125,127,3,6,3,0,126,128,3,16,8,0,127,126,1,0,0,0,127,128,
  	1,0,0,0,128,15,1,0,0,0,129,132,5,5,0,0,130,133,3,14,7,0,131,133,3,6,3,
  	0,132,130,1,0,0,0,132,131,1,0,0,0,133,17,1,0,0,0,134,135,5,29,0,0,135,
  	137,5,23,0,0,136,138,3,20,10,0,137,136,1,0,0,0,137,138,1,0,0,0,138,139,
  	1,0,0,0,139,140,5,24,0,0,140,19,1,0,0,0,141,146,3,24,12,0,142,143,5,27,
  	0,0,143,145,3,24,12,0,144,142,1,0,0,0,145,148,1,0,0,0,146,144,1,0,0,0,
  	146,147,1,0,0,0,147,21,1,0,0,0,148,146,1,0,0,0,149,150,5,29,0,0,150,151,
  	5,13,0,0,151,152,3,24,12,0,152,23,1,0,0,0,153,154,3,26,13,0,154,25,1,
  	0,0,0,155,160,3,28,14,0,156,157,5,20,0,0,157,159,3,28,14,0,158,156,1,
  	0,0,0,159,162,1,0,0,0,160,158,1,0,0,0,160,161,1,0,0,0,161,27,1,0,0,0,
  	162,160,1,0,0,0,163,168,3,30,15,0,164,165,5,19,0,0,165,167,3,30,15,0,
  	166,164,1,0,0,0,167,170,1,0,0,0,168,166,1,0,0,0,168,169,1,0,0,0,169,29,
  	1,0,0,0,170,168,1,0,0,0,171,176,3,32,16,0,172,173,5,16,0,0,173,175,3,
  	32,16,0,174,172,1,0,0,0,175,178,1,0,0,0,176,174,1,0,0,0,176,177,1,0,0,
  	0,177,31,1,0,0,0,178,176,1,0,0,0,179,184,3,34,17,0,180,181,7,0,0,0,181,
  	183,3,34,17,0,182,180,1,0,0,0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,
  	1,0,0,0,185,33,1,0,0,0,186,184,1,0,0,0,187,192,3,36,18,0,188,189,7,1,
  	0,0,189,191,3,36,18,0,190,188,1,0,0,0,191,194,1,0,0,0,192,190,1,0,0,0,
  	192,193,1,0,0,0,193,35,1,0,0,0,194,192,1,0,0,0,195,200,3,38,19,0,196,
  	197,7,2,0,0,197,199,3,38,19,0,198,196,1,0,0,0,199,202,1,0,0,0,200,198,
  	1,0,0,0,200,201,1,0,0,0,201,37,1,0,0,0,202,200,1,0,0,0,203,209,3,40,20,
  	0,204,205,5,21,0,0,205,209,3,38,19,0,206,207,5,10,0,0,207,209,3,38,19,
  	0,208,203,1,0,0,0,208,204,1,0,0,0,208,206,1,0,0,0,209,39,1,0,0,0,210,
  	218,3,42,21,0,211,218,3,18,9,0,212,218,5,29,0,0,213,214,5,23,0,0,214,
  	215,3,24,12,0,215,216,5,24,0,0,216,218,1,0,0,0,217,210,1,0,0,0,217,211,
  	1,0,0,0,217,212,1,0,0,0,217,213,1,0,0,0,218,41,1,0,0,0,219,220,7,3,0,
  	0,220,43,1,0,0,0,21,47,55,67,74,83,89,95,97,116,127,132,137,146,160,168,
  	176,184,192,200,208,217
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
    setState(45); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(44);
      functionDefinition();
      setState(47); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == RyntraParser::INT);
    setState(49);
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

tree::TerminalNode* RyntraParser::FunctionDefinitionContext::INT() {
  return getToken(RyntraParser::INT, 0);
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
    setState(51);
    match(RyntraParser::INT);
    setState(52);
    match(RyntraParser::IDENTIFIER);
    setState(53);
    match(RyntraParser::LPAREN);
    setState(55);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::INT) {
      setState(54);
      parameterList();
    }
    setState(57);
    match(RyntraParser::RPAREN);
    setState(58);
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

std::vector<tree::TerminalNode *> RyntraParser::ParameterListContext::INT() {
  return getTokens(RyntraParser::INT);
}

tree::TerminalNode* RyntraParser::ParameterListContext::INT(size_t i) {
  return getToken(RyntraParser::INT, i);
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
    setState(60);
    match(RyntraParser::INT);
    setState(61);
    match(RyntraParser::IDENTIFIER);
    setState(67);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(62);
      match(RyntraParser::COMMA);
      setState(63);
      match(RyntraParser::INT);
      setState(64);
      match(RyntraParser::IDENTIFIER);
      setState(69);
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
    setState(70);
    match(RyntraParser::LBRACE);
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1893729758) != 0)) {
      setState(71);
      statement();
      setState(76);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(77);
    match(RyntraParser::RBRACE);
   
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

tree::TerminalNode* RyntraParser::VariableDeclarationContext::INT() {
  return getToken(RyntraParser::INT, 0);
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

tree::TerminalNode* RyntraParser::VariableDeclarationContext::STRING() {
  return getToken(RyntraParser::STRING, 0);
}

tree::TerminalNode* RyntraParser::VariableDeclarationContext::BOOL() {
  return getToken(RyntraParser::BOOL, 0);
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
  enterRule(_localctx, 8, RyntraParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(97);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(79);
        match(RyntraParser::INT);
        setState(80);
        match(RyntraParser::IDENTIFIER);
        setState(83);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == RyntraParser::ASSIGN) {
          setState(81);
          match(RyntraParser::ASSIGN);
          setState(82);
          expression();
        }
        break;
      }

      case RyntraParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(85);
        match(RyntraParser::STRING);
        setState(86);
        match(RyntraParser::IDENTIFIER);
        setState(89);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == RyntraParser::ASSIGN) {
          setState(87);
          match(RyntraParser::ASSIGN);
          setState(88);
          expression();
        }
        break;
      }

      case RyntraParser::BOOL: {
        enterOuterAlt(_localctx, 3);
        setState(91);
        match(RyntraParser::BOOL);
        setState(92);
        match(RyntraParser::IDENTIFIER);
        setState(95);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == RyntraParser::ASSIGN) {
          setState(93);
          match(RyntraParser::ASSIGN);
          setState(94);
          expression();
        }
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
  enterRule(_localctx, 10, RyntraParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(116);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(99);
      functionCall();
      setState(100);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(102);
      expression();
      setState(103);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(105);
      variableDeclaration();
      setState(106);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(108);
      returnStatement();
      setState(109);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(111);
      assignment();
      setState(112);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(114);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(115);
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
  enterRule(_localctx, 12, RyntraParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(RyntraParser::RETURN);
    setState(119);
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
  enterRule(_localctx, 14, RyntraParser::RuleIfStatement);
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
    setState(121);
    match(RyntraParser::IF);
    setState(122);
    match(RyntraParser::LPAREN);
    setState(123);
    expression();
    setState(124);
    match(RyntraParser::RPAREN);
    setState(125);
    block();
    setState(127);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ELSE) {
      setState(126);
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
  enterRule(_localctx, 16, RyntraParser::RuleElseClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    match(RyntraParser::ELSE);
    setState(132);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::IF: {
        setState(130);
        ifStatement();
        break;
      }

      case RyntraParser::LBRACE: {
        setState(131);
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
  enterRule(_localctx, 18, RyntraParser::RuleFunctionCall);
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
    setState(134);
    match(RyntraParser::IDENTIFIER);
    setState(135);
    match(RyntraParser::LPAREN);

    setState(137);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1889535360) != 0)) {
      setState(136);
      argumentList();
    }
    setState(139);
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
  enterRule(_localctx, 20, RyntraParser::RuleArgumentList);
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
    setState(141);
    expression();
    setState(146);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(142);
      match(RyntraParser::COMMA);
      setState(143);
      expression();
      setState(148);
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
  enterRule(_localctx, 22, RyntraParser::RuleAssignment);

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
    match(RyntraParser::IDENTIFIER);
    setState(150);
    match(RyntraParser::ASSIGN);
    setState(151);
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
  enterRule(_localctx, 24, RyntraParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
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
  enterRule(_localctx, 26, RyntraParser::RuleLogicalOrExpression);
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
    logicalAndExpression();
    setState(160);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_OR) {
      setState(156);
      match(RyntraParser::LOGIC_OR);
      setState(157);
      logicalAndExpression();
      setState(162);
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
  enterRule(_localctx, 28, RyntraParser::RuleLogicalAndExpression);
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
    equalityExpression();
    setState(168);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_AND) {
      setState(164);
      match(RyntraParser::LOGIC_AND);
      setState(165);
      equalityExpression();
      setState(170);
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
  enterRule(_localctx, 30, RyntraParser::RuleEqualityExpression);
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
    setState(171);
    relationalExpression();
    setState(176);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COND_EQUAL) {
      setState(172);
      match(RyntraParser::COND_EQUAL);
      setState(173);
      relationalExpression();
      setState(178);
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
  enterRule(_localctx, 32, RyntraParser::RuleRelationalExpression);
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
    setState(179);
    additiveExpression();
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 442368) != 0)) {
      setState(180);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 442368) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(181);
      additiveExpression();
      setState(186);
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
  enterRule(_localctx, 34, RyntraParser::RuleAdditiveExpression);
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
    setState(187);
    multiplicativeExpression();
    setState(192);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::PLUS

    || _la == RyntraParser::MINUS) {
      setState(188);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::PLUS

      || _la == RyntraParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(189);
      multiplicativeExpression();
      setState(194);
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
  enterRule(_localctx, 36, RyntraParser::RuleMultiplicativeExpression);
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
    setState(195);
    unaryExpression();
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::MULT

    || _la == RyntraParser::DIV) {
      setState(196);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::MULT

      || _la == RyntraParser::DIV)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(197);
      unaryExpression();
      setState(202);
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

RyntraParser::PrimaryExpressionContext* RyntraParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<RyntraParser::PrimaryExpressionContext>(0);
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
  enterRule(_localctx, 38, RyntraParser::RuleUnaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(208);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::TRUE:
      case RyntraParser::FALSE:
      case RyntraParser::LPAREN:
      case RyntraParser::STRING_LITERAL:
      case RyntraParser::IDENTIFIER:
      case RyntraParser::INTEGER_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(203);
        primaryExpression();
        break;
      }

      case RyntraParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(204);
        match(RyntraParser::NOT);
        setState(205);
        unaryExpression();
        break;
      }

      case RyntraParser::MINUS: {
        enterOuterAlt(_localctx, 3);
        setState(206);
        match(RyntraParser::MINUS);
        setState(207);
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
  enterRule(_localctx, 40, RyntraParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(217);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(210);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(211);
      functionCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(212);
      match(RyntraParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(213);
      match(RyntraParser::LPAREN);
      setState(214);
      expression();
      setState(215);
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
  enterRule(_localctx, 42, RyntraParser::RuleLiteral);
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
    setState(219);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1342177664) != 0))) {
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
