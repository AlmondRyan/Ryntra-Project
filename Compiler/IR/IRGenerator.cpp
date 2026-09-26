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

        case Sem::TypeKind::STRUCT: {
            const auto &structType = static_cast<const Sem::StructType &>(*semType);
            auto it = structTypeMap_.find(structType.getName());
            if (it != structTypeMap_.end())
                return it->second;

            // Struct types are normally pre-created in registerStructFunctions;
            // fall back to building one on demand (fields in declaration order).
            auto irStruct = std::make_shared<IR::StructType>(structType.getName());
            structTypeMap_[structType.getName()] = irStruct;
            for (const auto &field : structType.getOrderedFields()) {
                irStruct->addField(field.first, toIRType(field.second));
            }
            return irStruct;
        }

        default:
            return Type::getVoidType();
        }
    }
} // namespace Ryntra::IR
