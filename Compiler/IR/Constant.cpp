#include "Constant.h"
#include "Type.h"

namespace Ryntra::Compiler {
    ConstantInt::ConstantInt(int val) : Constant(Type::getInt32Ty(), std::to_string(val)), value(val) {}

    std::string ConstantInt::toString() const {
        return std::to_string(value);
    }

    ConstantObject::ConstantObject(Type *ty, const std::string &name, const std::string &initVal)
        : Constant(ty, name), initVal(initVal) {}

    std::string ConstantObject::toString() const {
        if (getName().empty())
            return "@unnamed";
        if (getName()[0] == '@')
            return getName();
        return "@" + getName();
    }
} // namespace Ryntra::Compiler
