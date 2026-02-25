#pragma once

#include "../IR/Function.h"
#include "../IR/Instruction.h"
#include "RuntimeValue.h"
#include <map>
#include <vector>

namespace Ryntra::Compiler::VM {
    class Frame {
    public:
        Frame(Function* func, std::vector<RuntimeValue> args) 
            : function(func), currentBlock(nullptr) {
            
            this->args = std::move(args);
            
            if (!func->getBasicBlocks().empty()) {
                currentBlock = func->getBasicBlocks()[0].get();
                instIterator = currentBlock->getInstructions().begin();
            }
        }

        Function* getFunction() const { return function; }
        
        void setLocal(const std::string& name, RuntimeValue val) {
            locals[name] = std::move(val);
        }

        RuntimeValue getLocal(const std::string& name) const {
            auto it = locals.find(name);
            if (it != locals.end()) {
                return it->second;
            }
            throw std::runtime_error("Undefined local variable: " + name);
        }

        bool hasLocal(const std::string& name) const {
            return locals.find(name) != locals.end();
        }

        Instruction* getNextInstruction() {
            if (!currentBlock) return nullptr;
            
            if (instIterator == currentBlock->getInstructions().end()) {
                return nullptr;
            }
            
            Instruction* inst = instIterator->get();
            ++instIterator;
            return inst;
        }

        const std::vector<RuntimeValue>& getArgs() const { return args; }

    private:
        Function* function;
        BasicBlock* currentBlock;
        std::list<std::unique_ptr<Instruction>>::const_iterator instIterator;
        std::vector<RuntimeValue> args;
        std::map<std::string, RuntimeValue> locals;
    };
} // namespace Ryntra::Compiler::VM
