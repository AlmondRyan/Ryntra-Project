#include "Module.h"
#include <sstream>

namespace Ryntra::Compiler {
    Module::Module(const std::string &name) : name(name) {}

    void Module::addFunction(std::unique_ptr<Function> func) {
        functions.push_back(std::move(func));
    }

    void Module::addConstantObject(std::unique_ptr<ConstantObject> global) {
        constantObjects.push_back(std::move(global));
    }

    Function *Module::getFunction(const std::string &name) {
        for (const auto &func : functions) {
            if (func->getName() == name)
                return func.get();
        }
        return nullptr;
    }

    ConstantObject *Module::getConstantObject(const std::string &name) {
        for (const auto &global : constantObjects) {
            if (global->getName() == name)
                return global.get();
        }
        return nullptr;
    }

    std::string Module::print() const {
        std::stringstream ss;
        ss << "module " << name << " {\n";

        // 1. External functions (declarations)
        for (const auto &func : functions) {
            if (func->isDeclaration()) {
                ss << "    " << func->print() << "\n";
            }
        }

        // 2. Constants
        for (const auto &c : constantObjects) {
            // @str0 = constant string "..."
            // Ensure constant string is quoted
            ss << "    @" << c->getName() << " = constant " << c->getType()->toString() << " " << c->getInitValue() << "\n";
        }

        // 3. Defined functions
        for (const auto &func : functions) {
            if (!func->isDeclaration()) {
                std::string funcStr = func->print();
                std::stringstream fss(funcStr);
                std::string line;
                while (std::getline(fss, line)) {
                    ss << "    " << line << "\n";
                }
            }
        }

        ss << "}";
        return ss.str();
    }
} // namespace Ryntra::Compiler
