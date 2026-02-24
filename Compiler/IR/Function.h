#pragma once

#include "Value.h"
#include "BasicBlock.h"
#include <vector>
#include <memory>
#include <string>

namespace Ryntra::Compiler {

class Module; // Forward declaration

class Function : public Value {
public:
    Function(const std::string& name, Type* retType, Module* parent, std::vector<Type*> argTypes = {});
    
    Module* getParent() const { return parent; }
    Type* getReturnType() const { return getType(); }
    const std::vector<std::unique_ptr<BasicBlock>>& getBasicBlocks() const { return basicBlocks; }
    const std::vector<Type*>& getArgTypes() const { return argTypes; }

    BasicBlock* addBasicBlock(std::unique_ptr<BasicBlock> bb);
    
    bool isDeclaration() const { return basicBlocks.empty(); }

    // Print the function definition
    std::string print() const;

    // Returns function name as operand (e.g. "@main")
    std::string toString() const override { return "@" + getName(); }

private:
    Module* parent;
    std::vector<std::unique_ptr<BasicBlock>> basicBlocks;
    std::vector<Type*> argTypes;
};

}
