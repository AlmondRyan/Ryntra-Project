#include "Type.h"

namespace Ryntra::Compiler {

Type* Type::getVoidTy() {
    static Type voidTy(TypeID::Void);
    return &voidTy;
}

Type* Type::getInt32Ty() {
    static Type int32Ty(TypeID::Integer32);
    return &int32Ty;
}

Type* Type::getStringTy() {
    static Type stringTy(TypeID::String);
    return &stringTy;
}

std::string Type::toString() const {
    switch (id) {
        case TypeID::Void: return "void";
        case TypeID::Integer32: return "i32";
        case TypeID::String: return "string";
        default: return "unknown";
    }
}

}
