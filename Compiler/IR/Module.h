#pragma once

#include "Constant.h"
#include "Function.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Ryntra::IR {
    class Module {
    public:
        Module(const std::string &name) : name_(name) {}

        const std::string &getName() const { return name_; }
        void setName(const std::string &name) { name_ = name; }

        void addFunction(std::shared_ptr<Function> function) {
            functions_.push_back(function);
            if (!function->getName().empty()) {
                functionMap_[function->getName()] = function;
            }
        }

        void addConstant(std::shared_ptr<Constant> constant) {
            constants_.push_back(constant);
            if (!constant->getName().empty()) {
                constantMap_[constant->getName()] = constant;
            }
        }

        // Register a named aggregate type so it can be printed as a type definition.
        void addType(std::shared_ptr<StructType> type) {
            if (!type)
                return;
            for (const auto &existing : types_) {
                if (existing.get() == type.get())
                    return;
            }
            types_.push_back(std::move(type));
        }

        const std::vector<std::shared_ptr<StructType>> &getTypes() const { return types_; }

        const std::vector<std::shared_ptr<Function>> &getFunctions() const {
            return functions_;
        }

        const std::vector<std::shared_ptr<Constant>> &getConstants() const {
            return constants_;
        }

        std::shared_ptr<Function> getFunction(const std::string &name) const {
            auto it = functionMap_.find(name);
            return it != functionMap_.end() ? it->second : nullptr;
        }

        std::shared_ptr<Constant> getConstant(const std::string &name) const {
            auto it = constantMap_.find(name);
            return it != constantMap_.end() ? it->second : nullptr;
        }

        std::string toString() const {
            std::string result = "module " + name_ + " {\n\n";

            // 0. Aggregate type definitions
            for (const auto &type : types_) {
                result += "    " + type->toString() + " = struct { ";
                const auto &fields = type->getFields();
                for (size_t i = 0; i < fields.size(); ++i) {
                    if (i > 0)
                        result += ", ";
                    result += fields[i].type->toString();
                }
                result += " }\n";
            }
            if (!types_.empty())
                result += "\n";

            // 1. External function declarations first
            bool hasExternals = false;
            for (const auto &function : functions_) {
                if (function->isExternal()) {
                    result += "    " + function->toString() + "\n";
                    hasExternals = true;
                }
            }
            if (hasExternals)
                result += "\n";

            // 2. Global constants
            for (const auto &constant : constants_) {
                result += "    " + constant->toString() + "\n";
            }
            if (!constants_.empty())
                result += "\n";

            // 3. Defined functions
            for (const auto &function : functions_) {
                if (!function->isExternal())
                    result += "    " + function->toString() + "\n\n";
            }

            result += "}\n";
            return result;
        }

    private:
        std::string name_;
        std::vector<std::shared_ptr<Function>> functions_;
        std::vector<std::shared_ptr<Constant>> constants_;
        std::vector<std::shared_ptr<StructType>> types_;
        std::unordered_map<std::string, std::shared_ptr<Function>> functionMap_;
        std::unordered_map<std::string, std::shared_ptr<Constant>> constantMap_;
    };
} // namespace Ryntra::IR