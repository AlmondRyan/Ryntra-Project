#pragma once

#include "BasicBlock.h"
#include "Type.h"
#include "Value.h"
#include <memory>
#include <string>
#include <vector>

namespace Ryntra::IR {
    class Function : public Value {
    public:
        struct Parameter {
            std::string name;
            std::shared_ptr<Type> type;

            Parameter(const std::string &name, std::shared_ptr<Type> type)
                : name(name), type(type) {}
        };

        Function(const std::string &name,
                 std::shared_ptr<Type> returnType,
                 const std::vector<Parameter> &parameters = {},
                 bool isExternal = false)
            : Value(std::make_shared<FunctionType>(returnType, extractParamTypes(parameters)), name),
              returnType_(returnType),
              parameters_(parameters),
              isExternal_(isExternal) {}

        std::shared_ptr<Type> getReturnType() const { return returnType_; }
        const std::vector<Parameter> &getParameters() const { return parameters_; }
        bool isExternal() const { return isExternal_; }

        void addBasicBlock(std::shared_ptr<BasicBlock> block) {
            basicBlocks_.push_back(block);
        }

        const std::vector<std::shared_ptr<BasicBlock>> &getBasicBlocks() const {
            return basicBlocks_;
        }

        std::shared_ptr<BasicBlock> getEntryBlock() const {
            return basicBlocks_.empty() ? nullptr : basicBlocks_[0];
        }

        std::string toString() const override {
            std::string result;

            if (isExternal_) {
                result = "external ";
            }

            result += "func @" + name_ + "(";

            for (size_t i = 0; i < parameters_.size(); ++i) {
                if (i > 0)
                    result += ", ";
                result += parameters_[i].type->toString();
            }

            result += ") -> " + returnType_->toString();

            if (!isExternal_ && !basicBlocks_.empty()) {
                result += " {\n";
                for (const auto &block : basicBlocks_) {
                    result += block->toString();
                }
                result += "}";
            }

            return result;
        }

    private:
        static std::vector<std::shared_ptr<Type>> extractParamTypes(const std::vector<Parameter> &params) {
            std::vector<std::shared_ptr<Type>> types;
            for (const auto &param : params) {
                types.push_back(param.type);
            }
            return types;
        }

    private:
        std::shared_ptr<Type> returnType_;
        std::vector<Parameter> parameters_;
        std::vector<std::shared_ptr<BasicBlock>> basicBlocks_;
        bool isExternal_;
    };
} // namespace Ryntra::IR
