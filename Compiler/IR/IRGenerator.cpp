#include "IRGenerator.h"
#include "Compiler/Semantic/TypeSystem.h"
#include "ImmediateValue.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    IRGenerator::IRGenerator() = default;

    std::shared_ptr<Module> IRGenerator::generate(Sem::TypedProgramNode &program,
                                                   const std::string &moduleName) {
        builder_.createModule(moduleName);
        program.accept(*this);
        return builder_.getModule();
    }

    std::shared_ptr<Type> IRGenerator::toIRType(const std::shared_ptr<Sem::Type> &semType) {
        if (!semType)
            return Type::getVoidType();

        switch (semType->getKind()) {
        case Sem::TypeKind::VOID:
            return Type::getVoidType();

        case Sem::TypeKind::PRIMITIVE: {
            const auto &name = static_cast<const Sem::PrimitiveType &>(*semType).getName();
            if (name == "i32" || name == "int")
                return Type::getInt32Type();
            if (name == "i64" || name == "long")
                return Type::getInt64Type();
            if (name == "string" || name == "str")
                return Type::getStringType();
            if (name == "bool")
                return Type::getBoolType();
            return Type::getInt32Type();
        }

        case Sem::TypeKind::FUNCTION: {
            const auto &ft = static_cast<const Sem::FunctionType &>(*semType);
            auto retIR = toIRType(ft.getReturnType());
            std::vector<std::shared_ptr<Type>> params;
            for (const auto &p : ft.getParamTypes())
                params.push_back(toIRType(p));
            return std::make_shared<IR::FunctionType>(retIR, params);
        }

        case Sem::TypeKind::ARRAY: {
            const auto &arrType = static_cast<const Sem::ArrayType &>(*semType);
            return std::make_shared<IR::ArrayType>(toIRType(arrType.getElementType()));
        }

        case Sem::TypeKind::REFERENCE: {
            const auto &refType = static_cast<const Sem::ReferenceType &>(*semType);
            return std::make_shared<IR::RefType>(toIRType(refType.getElementType()));
        }

        case Sem::TypeKind::POINTER: {
            const auto &ptrType = static_cast<const Sem::PointerType &>(*semType);
            return std::make_shared<IR::PtrType>(toIRType(ptrType.getElementType()));
        }

        default:
            return Type::getVoidType();
        }
    }
} // namespace Ryntra::IR
