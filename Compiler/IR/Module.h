#pragma once

#include "Function.h"
#include "Constant.h"
#include <vector>
#include <memory>
#include <string>

namespace Ryntra::Compiler {

class Module {
public:
    Module(const std::string& name);
    
    void addFunction(std::unique_ptr<Function> func);
    void addConstantObject(std::unique_ptr<ConstantObject> global);
    
    Function* getFunction(const std::string& name);
    ConstantObject* getConstantObject(const std::string& name);
    
    const std::vector<std::unique_ptr<Function>>& getFunctions() const { return functions; }
    const std::vector<std::unique_ptr<ConstantObject>>& getConstantObjects() const { return constantObjects; }

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

}
