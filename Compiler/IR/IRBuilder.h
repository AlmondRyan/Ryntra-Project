#pragma once

#include <string>
#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <variant>

namespace Ryntra::Compiler {

// Forward declarations
class Type;
class Value;
class Instruction;
class BasicBlock;
class Function;
class Module;

// --- Type System ---
enum class TypeID {
    Void,
    Integer32,
    String
};

class Type {
public:
    Type(TypeID id) : id(id) {}
    TypeID getID() const { return id; }
    
    static Type* getVoidTy();
    static Type* getInt32Ty();
    static Type* getStringTy();

    std::string toString() const;

private:
    TypeID id;
};

// --- Value System ---
class Value {
public:
    virtual ~Value() = default;
    Type* getType() const { return type; }
    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    virtual std::string toString() const;

protected:
    Value(Type* ty, const std::string& name = "") : type(ty), name(name) {}
    Type* type;
    std::string name;
};

class Constant : public Value {
protected:
    Constant(Type* ty, const std::string& name = "") : Value(ty, name) {}
};

class ConstantInt : public Constant {
public:
    ConstantInt(int val);
    int getValue() const { return value; }
    std::string toString() const override;
private:
    int value;
};

class ConstantObject : public Constant {
public:
    ConstantObject(Type* ty, const std::string& name, const std::string& initVal);
    std::string getInitValue() const { return initVal; }
    std::string toString() const override;
private:
    std::string initVal;
};

// --- Instruction System ---
enum class OpCode {
    LoadC,
    Syscall,
    Halt,
    Call,
    Ret
};

class Instruction : public Value {
public:
    Instruction(Type* ty, OpCode op, const std::string& name = "");
    
    OpCode getOpCode() const { return opcode; }
    const std::vector<Value*>& getOperands() const { return operands; }
    void addOperand(Value* v) { operands.push_back(v); }
    
    std::string toString() const override;

private:
    OpCode opcode;
    std::vector<Value*> operands;
};

// --- Structure ---
class BasicBlock : public Value {
public:
    BasicBlock(const std::string& name, Function* parent);
    
    Function* getParent() const { return parent; }
    const std::list<std::unique_ptr<Instruction>>& getInstructions() const { return instructions; }
    
    Instruction* addInstruction(std::unique_ptr<Instruction> inst);
    
    std::string toString() const override;

private:
    Function* parent;
    std::list<std::unique_ptr<Instruction>> instructions;
};

class Function : public Value {
public:
    Function(const std::string& name, Type* retType, Module* parent, std::vector<Type*> argTypes = {});
    
    Module* getParent() const { return parent; }
    const std::vector<std::unique_ptr<BasicBlock>>& getBasicBlocks() const { return basicBlocks; }
    const std::vector<Type*>& getArgTypes() const { return argTypes; }

    BasicBlock* addBasicBlock(std::unique_ptr<BasicBlock> bb);
    
    bool isDeclaration() const { return basicBlocks.empty(); }

    std::string toString() const override;

private:
    Module* parent;
    std::vector<std::unique_ptr<BasicBlock>> basicBlocks;
    std::vector<Type*> argTypes;
};

class Module {
public:
    Module(const std::string& name);
    
    void addFunction(std::unique_ptr<Function> func);
    void addConstantObject(std::unique_ptr<ConstantObject> global);
    
    Function* getFunction(const std::string& name);
    ConstantObject* getConstantObject(const std::string& name);

    // Helpers for auto-naming
    size_t getNextStringConstantId() { return stringConstantCounter++; }
    
    // Manage constants (integers, etc.)
    void addConstant(std::unique_ptr<Constant> c) { constants.push_back(std::move(c)); }

    std::string print() const;

private:
    std::string name;
    std::vector<std::unique_ptr<Function>> functions;
    std::vector<std::unique_ptr<ConstantObject>> constantObjects;
    std::vector<std::unique_ptr<Constant>> constants;
    size_t stringConstantCounter = 0;
};

// --- IRBuilder ---
class IRBuilder {
public:
    IRBuilder(Module* m) : module(m), insertBlock(nullptr) {}

    void SetInsertPoint(BasicBlock* bb) { insertBlock = bb; }
    BasicBlock* GetInsertBlock() const { return insertBlock; }

    // Helpers to create structural elements
    Function* CreateFunction(const std::string& name, Type* retType, std::vector<Type*> argTypes = {});
    BasicBlock* CreateBasicBlock(const std::string& name, Function* parent);
    
    // Create a string constant.
    // If name is provided, it will be prefixed with '@' automatically if not present.
    ConstantObject* CreateConstantString(const std::string& name, const std::string& val);
    // Overload for auto-naming (str0, str1, ...).
    ConstantObject* CreateConstantString(const std::string& val);

    // Helpers to create instructions
    Instruction* CreateLoadC(ConstantObject* global, const std::string& destName = "");
    Instruction* CreateSyscall(int code);
    Instruction* CreateHalt();
    Instruction* CreateCall(Function* func, const std::vector<Value*>& args, const std::string& destName = "");
    Instruction* CreateRet(Value* val);

private:
    Module* module;
    BasicBlock* insertBlock;
    size_t tempVarCounter = 0;
};

}
