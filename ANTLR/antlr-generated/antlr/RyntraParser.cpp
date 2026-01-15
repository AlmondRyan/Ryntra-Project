
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
      "statement", "returnStatement", "ifStatement", "elseClause", "whileStatement", 
      "forStatement", "functionCall", "argumentList", "assignment", "expression", 
      "logicalOrExpression", "logicalAndExpression", "equalityExpression", 
      "relationalExpression", "additiveExpression", "multiplicativeExpression", 
      "unaryExpression", "postfixExpression", "primaryExpression", "literal"
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
  	4,1,36,262,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,4,0,52,8,0,11,0,12,0,53,1,0,1,0,
  	1,1,1,1,1,1,1,1,3,1,62,8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,5,2,72,8,2,
  	10,2,12,2,75,9,2,1,3,1,3,5,3,79,8,3,10,3,12,3,82,9,3,1,3,1,3,1,4,1,4,
  	1,4,1,4,3,4,90,8,4,1,4,1,4,1,4,1,4,3,4,96,8,4,1,4,1,4,1,4,1,4,3,4,102,
  	8,4,3,4,104,8,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,3,5,125,8,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,
  	3,7,136,8,7,1,8,1,8,1,8,3,8,141,8,8,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,
  	1,10,1,10,1,10,3,10,154,8,10,1,10,1,10,3,10,158,8,10,1,10,1,10,1,10,3,
  	10,163,8,10,1,10,1,10,1,10,1,11,1,11,1,11,3,11,171,8,11,1,11,1,11,1,12,
  	1,12,1,12,5,12,178,8,12,10,12,12,12,181,9,12,1,13,1,13,1,13,1,13,1,14,
  	1,14,1,15,1,15,1,15,5,15,192,8,15,10,15,12,15,195,9,15,1,16,1,16,1,16,
  	5,16,200,8,16,10,16,12,16,203,9,16,1,17,1,17,1,17,5,17,208,8,17,10,17,
  	12,17,211,9,17,1,18,1,18,1,18,5,18,216,8,18,10,18,12,18,219,9,18,1,19,
  	1,19,1,19,5,19,224,8,19,10,19,12,19,227,9,19,1,20,1,20,1,20,5,20,232,
  	8,20,10,20,12,20,235,9,20,1,21,1,21,1,21,1,21,1,21,3,21,242,8,21,1,22,
  	1,22,1,22,1,22,1,22,3,22,249,8,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	3,23,258,8,23,1,24,1,24,1,24,0,0,25,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,0,4,2,0,18,19,21,22,1,0,11,12,1,0,
  	15,16,3,0,7,8,32,32,34,34,276,0,51,1,0,0,0,2,57,1,0,0,0,4,66,1,0,0,0,
  	6,76,1,0,0,0,8,103,1,0,0,0,10,124,1,0,0,0,12,126,1,0,0,0,14,129,1,0,0,
  	0,16,137,1,0,0,0,18,142,1,0,0,0,20,148,1,0,0,0,22,167,1,0,0,0,24,174,
  	1,0,0,0,26,182,1,0,0,0,28,186,1,0,0,0,30,188,1,0,0,0,32,196,1,0,0,0,34,
  	204,1,0,0,0,36,212,1,0,0,0,38,220,1,0,0,0,40,228,1,0,0,0,42,241,1,0,0,
  	0,44,248,1,0,0,0,46,257,1,0,0,0,48,259,1,0,0,0,50,52,3,2,1,0,51,50,1,
  	0,0,0,52,53,1,0,0,0,53,51,1,0,0,0,53,54,1,0,0,0,54,55,1,0,0,0,55,56,5,
  	0,0,1,56,1,1,0,0,0,57,58,5,1,0,0,58,59,5,33,0,0,59,61,5,27,0,0,60,62,
  	3,4,2,0,61,60,1,0,0,0,61,62,1,0,0,0,62,63,1,0,0,0,63,64,5,28,0,0,64,65,
  	3,6,3,0,65,3,1,0,0,0,66,67,5,1,0,0,67,73,5,33,0,0,68,69,5,31,0,0,69,70,
  	5,1,0,0,70,72,5,33,0,0,71,68,1,0,0,0,72,75,1,0,0,0,73,71,1,0,0,0,73,74,
  	1,0,0,0,74,5,1,0,0,0,75,73,1,0,0,0,76,80,5,29,0,0,77,79,3,10,5,0,78,77,
  	1,0,0,0,79,82,1,0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,83,1,0,0,0,82,80,
  	1,0,0,0,83,84,5,30,0,0,84,7,1,0,0,0,85,86,5,1,0,0,86,89,5,33,0,0,87,88,
  	5,17,0,0,88,90,3,28,14,0,89,87,1,0,0,0,89,90,1,0,0,0,90,104,1,0,0,0,91,
  	92,5,3,0,0,92,95,5,33,0,0,93,94,5,17,0,0,94,96,3,28,14,0,95,93,1,0,0,
  	0,95,96,1,0,0,0,96,104,1,0,0,0,97,98,5,6,0,0,98,101,5,33,0,0,99,100,5,
  	17,0,0,100,102,3,28,14,0,101,99,1,0,0,0,101,102,1,0,0,0,102,104,1,0,0,
  	0,103,85,1,0,0,0,103,91,1,0,0,0,103,97,1,0,0,0,104,9,1,0,0,0,105,106,
  	3,22,11,0,106,107,5,26,0,0,107,125,1,0,0,0,108,109,3,28,14,0,109,110,
  	5,26,0,0,110,125,1,0,0,0,111,112,3,8,4,0,112,113,5,26,0,0,113,125,1,0,
  	0,0,114,115,3,12,6,0,115,116,5,26,0,0,116,125,1,0,0,0,117,118,3,26,13,
  	0,118,119,5,26,0,0,119,125,1,0,0,0,120,125,3,14,7,0,121,125,3,18,9,0,
  	122,125,3,20,10,0,123,125,5,26,0,0,124,105,1,0,0,0,124,108,1,0,0,0,124,
  	111,1,0,0,0,124,114,1,0,0,0,124,117,1,0,0,0,124,120,1,0,0,0,124,121,1,
  	0,0,0,124,122,1,0,0,0,124,123,1,0,0,0,125,11,1,0,0,0,126,127,5,2,0,0,
  	127,128,3,28,14,0,128,13,1,0,0,0,129,130,5,4,0,0,130,131,5,27,0,0,131,
  	132,3,28,14,0,132,133,5,28,0,0,133,135,3,6,3,0,134,136,3,16,8,0,135,134,
  	1,0,0,0,135,136,1,0,0,0,136,15,1,0,0,0,137,140,5,5,0,0,138,141,3,14,7,
  	0,139,141,3,6,3,0,140,138,1,0,0,0,140,139,1,0,0,0,141,17,1,0,0,0,142,
  	143,5,9,0,0,143,144,5,27,0,0,144,145,3,28,14,0,145,146,5,28,0,0,146,147,
  	3,6,3,0,147,19,1,0,0,0,148,149,5,10,0,0,149,153,5,27,0,0,150,154,3,8,
  	4,0,151,154,3,26,13,0,152,154,3,28,14,0,153,150,1,0,0,0,153,151,1,0,0,
  	0,153,152,1,0,0,0,153,154,1,0,0,0,154,155,1,0,0,0,155,157,5,26,0,0,156,
  	158,3,28,14,0,157,156,1,0,0,0,157,158,1,0,0,0,158,159,1,0,0,0,159,162,
  	5,26,0,0,160,163,3,26,13,0,161,163,3,28,14,0,162,160,1,0,0,0,162,161,
  	1,0,0,0,162,163,1,0,0,0,163,164,1,0,0,0,164,165,5,28,0,0,165,166,3,6,
  	3,0,166,21,1,0,0,0,167,168,5,33,0,0,168,170,5,27,0,0,169,171,3,24,12,
  	0,170,169,1,0,0,0,170,171,1,0,0,0,171,172,1,0,0,0,172,173,5,28,0,0,173,
  	23,1,0,0,0,174,179,3,28,14,0,175,176,5,31,0,0,176,178,3,28,14,0,177,175,
  	1,0,0,0,178,181,1,0,0,0,179,177,1,0,0,0,179,180,1,0,0,0,180,25,1,0,0,
  	0,181,179,1,0,0,0,182,183,5,33,0,0,183,184,5,17,0,0,184,185,3,28,14,0,
  	185,27,1,0,0,0,186,187,3,30,15,0,187,29,1,0,0,0,188,193,3,32,16,0,189,
  	190,5,24,0,0,190,192,3,32,16,0,191,189,1,0,0,0,192,195,1,0,0,0,193,191,
  	1,0,0,0,193,194,1,0,0,0,194,31,1,0,0,0,195,193,1,0,0,0,196,201,3,34,17,
  	0,197,198,5,23,0,0,198,200,3,34,17,0,199,197,1,0,0,0,200,203,1,0,0,0,
  	201,199,1,0,0,0,201,202,1,0,0,0,202,33,1,0,0,0,203,201,1,0,0,0,204,209,
  	3,36,18,0,205,206,5,20,0,0,206,208,3,36,18,0,207,205,1,0,0,0,208,211,
  	1,0,0,0,209,207,1,0,0,0,209,210,1,0,0,0,210,35,1,0,0,0,211,209,1,0,0,
  	0,212,217,3,38,19,0,213,214,7,0,0,0,214,216,3,38,19,0,215,213,1,0,0,0,
  	216,219,1,0,0,0,217,215,1,0,0,0,217,218,1,0,0,0,218,37,1,0,0,0,219,217,
  	1,0,0,0,220,225,3,40,20,0,221,222,7,1,0,0,222,224,3,40,20,0,223,221,1,
  	0,0,0,224,227,1,0,0,0,225,223,1,0,0,0,225,226,1,0,0,0,226,39,1,0,0,0,
  	227,225,1,0,0,0,228,233,3,42,21,0,229,230,7,2,0,0,230,232,3,42,21,0,231,
  	229,1,0,0,0,232,235,1,0,0,0,233,231,1,0,0,0,233,234,1,0,0,0,234,41,1,
  	0,0,0,235,233,1,0,0,0,236,242,3,44,22,0,237,238,5,25,0,0,238,242,3,42,
  	21,0,239,240,5,12,0,0,240,242,3,42,21,0,241,236,1,0,0,0,241,237,1,0,0,
  	0,241,239,1,0,0,0,242,43,1,0,0,0,243,249,3,46,23,0,244,245,5,33,0,0,245,
  	249,5,13,0,0,246,247,5,33,0,0,247,249,5,14,0,0,248,243,1,0,0,0,248,244,
  	1,0,0,0,248,246,1,0,0,0,249,45,1,0,0,0,250,258,3,48,24,0,251,258,3,22,
  	11,0,252,258,5,33,0,0,253,254,5,27,0,0,254,255,3,28,14,0,255,256,5,28,
  	0,0,256,258,1,0,0,0,257,250,1,0,0,0,257,251,1,0,0,0,257,252,1,0,0,0,257,
  	253,1,0,0,0,258,47,1,0,0,0,259,260,7,3,0,0,260,49,1,0,0,0,25,53,61,73,
  	80,89,95,101,103,124,135,140,153,157,162,170,179,193,201,209,217,225,
  	233,241,248,257
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
    setState(51); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(50);
      functionDefinition();
      setState(53); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == RyntraParser::INT);
    setState(55);
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
    setState(57);
    match(RyntraParser::INT);
    setState(58);
    match(RyntraParser::IDENTIFIER);
    setState(59);
    match(RyntraParser::LPAREN);
    setState(61);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::INT) {
      setState(60);
      parameterList();
    }
    setState(63);
    match(RyntraParser::RPAREN);
    setState(64);
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
    setState(66);
    match(RyntraParser::INT);
    setState(67);
    match(RyntraParser::IDENTIFIER);
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(68);
      match(RyntraParser::COMMA);
      setState(69);
      match(RyntraParser::INT);
      setState(70);
      match(RyntraParser::IDENTIFIER);
      setState(75);
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
    setState(76);
    match(RyntraParser::LBRACE);
    setState(80);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30299658206) != 0)) {
      setState(77);
      statement();
      setState(82);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(83);
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
    setState(103);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(85);
        match(RyntraParser::INT);
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

      case RyntraParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(91);
        match(RyntraParser::STRING);
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

      case RyntraParser::BOOL: {
        enterOuterAlt(_localctx, 3);
        setState(97);
        match(RyntraParser::BOOL);
        setState(98);
        match(RyntraParser::IDENTIFIER);
        setState(101);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == RyntraParser::ASSIGN) {
          setState(99);
          match(RyntraParser::ASSIGN);
          setState(100);
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

RyntraParser::WhileStatementContext* RyntraParser::StatementContext::whileStatement() {
  return getRuleContext<RyntraParser::WhileStatementContext>(0);
}

RyntraParser::ForStatementContext* RyntraParser::StatementContext::forStatement() {
  return getRuleContext<RyntraParser::ForStatementContext>(0);
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
    setState(124);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(105);
      functionCall();
      setState(106);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(108);
      expression();
      setState(109);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(111);
      variableDeclaration();
      setState(112);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(114);
      returnStatement();
      setState(115);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(117);
      assignment();
      setState(118);
      match(RyntraParser::SEMICOLON);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(120);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(121);
      whileStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(122);
      forStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(123);
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
    setState(126);
    match(RyntraParser::RETURN);
    setState(127);
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
    setState(129);
    match(RyntraParser::IF);
    setState(130);
    match(RyntraParser::LPAREN);
    setState(131);
    expression();
    setState(132);
    match(RyntraParser::RPAREN);
    setState(133);
    block();
    setState(135);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RyntraParser::ELSE) {
      setState(134);
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
    setState(137);
    match(RyntraParser::ELSE);
    setState(140);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::IF: {
        setState(138);
        ifStatement();
        break;
      }

      case RyntraParser::LBRACE: {
        setState(139);
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
  enterRule(_localctx, 18, RyntraParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    match(RyntraParser::WHILE);
    setState(143);
    match(RyntraParser::LPAREN);
    setState(144);
    expression();
    setState(145);
    match(RyntraParser::RPAREN);
    setState(146);
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
  enterRule(_localctx, 20, RyntraParser::RuleForStatement);
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
    setState(148);
    match(RyntraParser::FOR);
    setState(149);
    match(RyntraParser::LPAREN);
    setState(153);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(150);
      variableDeclaration();
      break;
    }

    case 2: {
      setState(151);
      assignment();
      break;
    }

    case 3: {
      setState(152);
      expression();
      break;
    }

    default:
      break;
    }
    setState(155);
    match(RyntraParser::SEMICOLON);
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30232547712) != 0)) {
      setState(156);
      expression();
    }
    setState(159);
    match(RyntraParser::SEMICOLON);
    setState(162);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(160);
      assignment();
      break;
    }

    case 2: {
      setState(161);
      expression();
      break;
    }

    default:
      break;
    }
    setState(164);
    match(RyntraParser::RPAREN);
    setState(165);
    block();
   
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
  enterRule(_localctx, 22, RyntraParser::RuleFunctionCall);
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
    setState(167);
    match(RyntraParser::IDENTIFIER);
    setState(168);
    match(RyntraParser::LPAREN);

    setState(170);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30232547712) != 0)) {
      setState(169);
      argumentList();
    }
    setState(172);
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
  enterRule(_localctx, 24, RyntraParser::RuleArgumentList);
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
    setState(174);
    expression();
    setState(179);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COMMA) {
      setState(175);
      match(RyntraParser::COMMA);
      setState(176);
      expression();
      setState(181);
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
  enterRule(_localctx, 26, RyntraParser::RuleAssignment);

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
    match(RyntraParser::IDENTIFIER);
    setState(183);
    match(RyntraParser::ASSIGN);
    setState(184);
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
  enterRule(_localctx, 28, RyntraParser::RuleExpression);

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
  enterRule(_localctx, 30, RyntraParser::RuleLogicalOrExpression);
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
    setState(188);
    logicalAndExpression();
    setState(193);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_OR) {
      setState(189);
      match(RyntraParser::LOGIC_OR);
      setState(190);
      logicalAndExpression();
      setState(195);
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
  enterRule(_localctx, 32, RyntraParser::RuleLogicalAndExpression);
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
    setState(196);
    equalityExpression();
    setState(201);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::LOGIC_AND) {
      setState(197);
      match(RyntraParser::LOGIC_AND);
      setState(198);
      equalityExpression();
      setState(203);
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
  enterRule(_localctx, 34, RyntraParser::RuleEqualityExpression);
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
    setState(204);
    relationalExpression();
    setState(209);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::COND_EQUAL) {
      setState(205);
      match(RyntraParser::COND_EQUAL);
      setState(206);
      relationalExpression();
      setState(211);
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
  enterRule(_localctx, 36, RyntraParser::RuleRelationalExpression);
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
    setState(212);
    additiveExpression();
    setState(217);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7077888) != 0)) {
      setState(213);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 7077888) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(214);
      additiveExpression();
      setState(219);
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
  enterRule(_localctx, 38, RyntraParser::RuleAdditiveExpression);
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
    setState(220);
    multiplicativeExpression();
    setState(225);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::PLUS

    || _la == RyntraParser::MINUS) {
      setState(221);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::PLUS

      || _la == RyntraParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(222);
      multiplicativeExpression();
      setState(227);
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
  enterRule(_localctx, 40, RyntraParser::RuleMultiplicativeExpression);
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
    setState(228);
    unaryExpression();
    setState(233);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RyntraParser::MULT

    || _la == RyntraParser::DIV) {
      setState(229);
      _la = _input->LA(1);
      if (!(_la == RyntraParser::MULT

      || _la == RyntraParser::DIV)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(230);
      unaryExpression();
      setState(235);
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
  enterRule(_localctx, 42, RyntraParser::RuleUnaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(241);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RyntraParser::TRUE:
      case RyntraParser::FALSE:
      case RyntraParser::LPAREN:
      case RyntraParser::STRING_LITERAL:
      case RyntraParser::IDENTIFIER:
      case RyntraParser::INTEGER_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(236);
        postfixExpression();
        break;
      }

      case RyntraParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(237);
        match(RyntraParser::NOT);
        setState(238);
        unaryExpression();
        break;
      }

      case RyntraParser::MINUS: {
        enterOuterAlt(_localctx, 3);
        setState(239);
        match(RyntraParser::MINUS);
        setState(240);
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
  enterRule(_localctx, 44, RyntraParser::RulePostfixExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(248);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(243);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(244);
      match(RyntraParser::IDENTIFIER);
      setState(245);
      match(RyntraParser::INC);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(246);
      match(RyntraParser::IDENTIFIER);
      setState(247);
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
  enterRule(_localctx, 46, RyntraParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(257);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(250);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(251);
      functionCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(252);
      match(RyntraParser::IDENTIFIER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(253);
      match(RyntraParser::LPAREN);
      setState(254);
      expression();
      setState(255);
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
  enterRule(_localctx, 48, RyntraParser::RuleLiteral);
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
    setState(259);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 21474836864) != 0))) {
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
