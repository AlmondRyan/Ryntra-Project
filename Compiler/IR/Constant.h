#pragma once

#include "Value.h"

namespace Ryntra::Compiler {

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

}
