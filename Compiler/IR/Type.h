#pragma once

#include <string>

namespace Ryntra::Compiler {
    enum class TypeID {
        Void,
        Integer32,
        String
    };

    class Type {
    public:
        Type(TypeID id) : id(id) {}
        TypeID getID() const { return id; }

        static Type *getVoidTy();
        static Type *getInt32Ty();
        static Type *getStringTy();

        std::string toString() const;

    private:
        TypeID id;
    };
} // namespace Ryntra::Compiler
