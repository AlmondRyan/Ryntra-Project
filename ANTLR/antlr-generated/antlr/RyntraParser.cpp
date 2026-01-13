
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
      "statement", "returnStatement", "functionCall", "argumentList", "assignment", 
      "expression", "assignmentExpression", "additiveExpression", "multiplicativeExpression", 
      "primaryExpression", "literal"
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
  	4,1,18,149,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,1,0,4,0,34,8,0,11,0,12,0,35,1,0,1,0,1,1,1,1,1,1,1,1,3,1,
  	44,8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,5,2,54,8,2,10,2,12,2,57,9,2,1,
  	3,1,3,5,3,61,8,3,10,3,12,3,64,9,3,1,3,1,3,1,4,1,4,1,4,1,4,3,4,72,8,4,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,90,
  	8,5,1,6,1,6,1,6,1,7,1,7,1,7,3,7,98,8,7,1,7,1,7,1,8,1,8,1,8,5,8,105,8,
  	8,10,8,12,8,108,9,8,1,9,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,11,1,11,3,11,
  	120,8,11,1,12,1,12,1,12,5,12,125,8,12,10,12,12,12,128,9,12,1,13,1,13,
  	1,13,5,13,133,8,13,10,13,12,13,136,9,13,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,3,14,145,8,14,1,15,1,15,1,15,0,0,16,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,0,3,1,0,3,4,1,0,5,6,2,0,14,14,16,16,150,0,33,1,0,0,0,2,
  	39,1,0,0,0,4,48,1,0,0,0,6,58,1,0,0,0,8,67,1,0,0,0,10,89,1,0,0,0,12,91,
  	1,0,0,0,14,94,1,0,0,0,16,101,1,0,0,0,18,109,1,0,0,0,20,113,1,0,0,0,22,
  	119,1,0,0,0,24,121,1,0,0,0,26,129,1,0,0,0,28,144,1,0,0,0,30,146,1,0,0,
  	0,32,34,3,2,1,0,33,32,1,0,0,0,34,35,1,0,0,0,35,33,1,0,0,0,35,36,1,0,0,
  	0,36,37,1,0,0,0,37,38,5,0,0,1,38,1,1,0,0,0,39,40,5,1,0,0,40,41,5,15,0,
  	0,41,43,5,9,0,0,42,44,3,4,2,0,43,42,1,0,0,0,43,44,1,0,0,0,44,45,1,0,0,
  	0,45,46,5,10,0,0,46,47,3,6,3,0,47,3,1,0,0,0,48,49,5,1,0,0,49,55,5,15,
  	0,0,50,51,5,13,0,0,51,52,5,1,0,0,52,54,5,15,0,0,53,50,1,0,0,0,54,57,1,
  	0,0,0,55,53,1,0,0,0,55,56,1,0,0,0,56,5,1,0,0,0,57,55,1,0,0,0,58,62,5,
  	11,0,0,59,61,3,10,5,0,60,59,1,0,0,0,61,64,1,0,0,0,62,60,1,0,0,0,62,63,
  	1,0,0,0,63,65,1,0,0,0,64,62,1,0,0,0,65,66,5,12,0,0,66,7,1,0,0,0,67,68,
  	5,1,0,0,68,71,5,15,0,0,69,70,5,7,0,0,70,72,3,20,10,0,71,69,1,0,0,0,71,
  	72,1,0,0,0,72,9,1,0,0,0,73,74,3,14,7,0,74,75,5,8,0,0,75,90,1,0,0,0,76,
  	77,3,20,10,0,77,78,5,8,0,0,78,90,1,0,0,0,79,80,3,8,4,0,80,81,5,8,0,0,
  	81,90,1,0,0,0,82,83,3,12,6,0,83,84,5,8,0,0,84,90,1,0,0,0,85,86,3,18,9,
  	0,86,87,5,8,0,0,87,90,1,0,0,0,88,90,5,8,0,0,89,73,1,0,0,0,89,76,1,0,0,
  	0,89,79,1,0,0,0,89,82,1,0,0,0,89,85,1,0,0,0,89,88,1,0,0,0,90,11,1,0,0,
  	0,91,92,5,2,0,0,92,93,3,20,10,0,93,13,1,0,0,0,94,95,5,15,0,0,95,97,5,
  	9,0,0,96,98,3,16,8,0,97,96,1,0,0,0,97,98,1,0,0,0,98,99,1,0,0,0,99,100,
  	5,10,0,0,100,15,1,0,0,0,101,106,3,20,10,0,102,103,5,13,0,0,103,105,3,
  	20,10,0,104,102,1,0,0,0,105,108,1,0,0,0,106,104,1,0,0,0,106,107,1,0,0,
  	0,107,17,1,0,0,0,108,106,1,0,0,0,109,110,5,15,0,0,110,111,5,7,0,0,111,
  	112,3,20,10,0,112,19,1,0,0,0,113,114,3,22,11,0,114,21,1,0,0,0,115,120,
  	3,24,12,0,116,117,5,15,0,0,117,118,5,7,0,0,118,120,3,20,10,0,119,115,
  	1,0,0,0,119,116,1,0,0,0,120,23,1,0,0,0,121,126,3,26,13,0,122,123,7,0,
  	0,0,123,125,3,26,13,0,124,122,1,0,0,0,125,128,1,0,0,0,126,124,1,0,0,0,
  	126,127,1,0,0,0,127,25,1,0,0,0,128,126,1,0,0,0,129,134,3,28,14,0,130,
  	131,7,1,0,0,131,133,3,28,14,0,132,130,1,0,0,0,133,136,1,0,0,0,134,132,
  	1,0,0,0,134,135,1,0,0,0,135,27,1,0,0,0,136,134,1,0,0,0,137,145,3,30,15,
  	0,138,145,3,14,7,0,139,145,5,15,0,0,140,141,5,9,0,0,141,142,3,20,10,0,
  	142,143,5,10,0,0,143,145,1,0,0,0,144,137,1,0,0,0,144,138,1,0,0,0,144,
  	139,1,0,0,0,144,140,1,0,0,0,145,29,1,0,0,0,146,147,7,2,0,0,147,31,1,0,
  	0,0,12,35,43,55,62,71,89,97,106,119,126,134,144
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
    setState(33); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(32);
      functionDefinition();
      setState(35); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == RyntraParser::INT);
    setState(37);
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
    setState(39);
    match(RyntraParser::INT);
    setState(40);
    match(RyntraParser::IDENTIFIER);
    setState(41);
    match(RyntraParser::LPAREN);
    setState(43);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::INT) {
      setState(42);
      parameterList();
    }
    setState(45);
    match(RyntraParser::RPAREN);
    setState(46);
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
    setState(48);
    match(RyntraParser::INT);
    setState(49);
    match(RyntraParser::IDENTIFIER);
    setState(55);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(50);
      match(RyntraParser::COMMA);
      setState(51);
      match(RyntraParser::INT);
      setState(52);
      match(RyntraParser::IDENTIFIER);
      setState(57);
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
    setState(58);
    match(RyntraParser::LBRACE);
    setState(62);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 115462) != 0)) {
      setState(59);
      statement();
      setState(64);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(65);
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
    enterOuterAlt(_localctx, 1);
    setState(67);
    match(RyntraParser::INT);
    setState(68);
    match(RyntraParser::IDENTIFIER);
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ASSIGN) {
      setState(69);
      match(RyntraParser::ASSIGN);
      setState(70);
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
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(73);
      functionCall();
      setState(74);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(76);
      expression();
      setState(77);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(79);
      variableDeclaration();
      setState(80);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(82);
      returnStatement();
      setState(83);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(85);
      assignment();
      setState(86);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(88);
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
    setState(91);
    match(RyntraParser::RETURN);
    setState(92);
    expression();
   
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
  enterRule(_localctx, 14, RyntraParser::RuleFunctionCall);
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
    setState(94);
    match(RyntraParser::IDENTIFIER);
    setState(95);
    match(RyntraParser::LPAREN);

    setState(97);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 115200) != 0)) {
      setState(96);
      argumentList();
    }
    setState(99);
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
  enterRule(_localctx, 16, RyntraParser::RuleArgumentList);
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
    setState(101);
    expression();
    setState(106);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(102);
      match(RyntraParser::COMMA);
      setState(103);
      expression();
      setState(108);
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
  enterRule(_localctx, 18, RyntraParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(RyntraParser::IDENTIFIER);
    setState(110);
    match(RyntraParser::ASSIGN);
    setState(111);
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

RyntraParser::AssignmentExpressionContext* RyntraParser::ExpressionContext::assignmentExpression() {
  return getRuleContext<RyntraParser::AssignmentExpressionContext>(0);
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
  enterRule(_localctx, 20, RyntraParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    assignmentExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

RyntraParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

RyntraParser::AdditiveExpressionContext* RyntraParser::AssignmentExpressionContext::additiveExpression() {
  return getRuleContext<RyntraParser::AdditiveExpressionContext>(0);
}

tree::TerminalNode* RyntraParser::AssignmentExpressionContext::IDENTIFIER() {
  return getToken(RyntraParser::IDENTIFIER, 0);
}

tree::TerminalNode* RyntraParser::AssignmentExpressionContext::ASSIGN() {
  return getToken(RyntraParser::ASSIGN, 0);
}

RyntraParser::ExpressionContext* RyntraParser::AssignmentExpressionContext::expression() {
  return getRuleContext<RyntraParser::ExpressionContext>(0);
}


size_t RyntraParser::AssignmentExpressionContext::getRuleIndex() const {
  return RyntraParser::RuleAssignmentExpression;
}

void RyntraParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void RyntraParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<RyntraListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}


std::any RyntraParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<RyntraVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}

RyntraParser::AssignmentExpressionContext* RyntraParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 22, RyntraParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(119);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(115);
      additiveExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(116);
      match(RyntraParser::IDENTIFIER);
      setState(117);
      match(RyntraParser::ASSIGN);
      setState(118);
      expression();
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
  enterRule(_localctx, 24, RyntraParser::RuleAdditiveExpression);
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
    multiplicativeExpression();
    setState(126);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::PLUS

    || _la == RyntraParser::MINUS) {
      setState(122);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::PLUS

      || _la == RyntraParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(123);
      multiplicativeExpression();
      setState(128);
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

std::vector<RyntraParser::PrimaryExpressionContext *> RyntraParser::MultiplicativeExpressionContext::primaryExpression() {
  return getRuleContexts<RyntraParser::PrimaryExpressionContext>();
}

RyntraParser::PrimaryExpressionContext* RyntraParser::MultiplicativeExpressionContext::primaryExpression(size_t i) {
  return getRuleContext<RyntraParser::PrimaryExpressionContext>(i);
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
  enterRule(_localctx, 26, RyntraParser::RuleMultiplicativeExpression);
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
    setState(129);
    primaryExpression();
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::MULT

    || _la == RyntraParser::DIV) {
      setState(130);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::MULT

      || _la == RyntraParser::DIV)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(131);
      primaryExpression();
      setState(136);
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
  enterRule(_localctx, 28, RyntraParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(144);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(137);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(138);
      functionCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(139);
      match(RyntraParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(140);
      match(RyntraParser::LPAREN);
      setState(141);
      expression();
      setState(142);
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
  enterRule(_localctx, 30, RyntraParser::RuleLiteral);
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
    setState(146);
    _la = _input->LA(1);
    if (!(_la == RyntraParser::STRING_LITERAL

    || _la == RyntraParser::INTEGER_LITERAL)) {
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
