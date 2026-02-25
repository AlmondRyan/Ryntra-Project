#pragma once

#include "RuntimeValue.h"
#include <vector>
#include <stdexcept>

namespace Ryntra::Compiler::VM {
    class Stack {
    public:
        void push(RuntimeValue val) {
            data.push_back(std::move(val));
        }

        RuntimeValue pop() {
            if (data.empty()) {
                throw std::runtime_error("Stack underflow");
            }
            RuntimeValue val = std::move(data.back());
            data.pop_back();
            return val;
        }

        RuntimeValue& peek() {
            if (data.empty()) {
                throw std::runtime_error("Stack is empty");
            }
            return data.back();
        }

        bool empty() const { return data.empty(); }
        size_t size() const { return data.size(); }
        void clear() { data.clear(); }

    private:
        std::vector<RuntimeValue> data;
    };
} // namespace Ryntra::Compiler::VM
