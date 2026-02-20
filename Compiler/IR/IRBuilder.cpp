#include "IRBuilder.h"
#include <sstream>

namespace Ryntra::Compiler {
    // --- Type ---
    Type *Type::getVoidTy() {
        static Type voidTy(TypeID::Void);
        return &voidTy;
    }

    Type *Type::getInt32Ty() {
        static Type int32Ty(TypeID::Integer32);
        return &int32Ty;
    }

    Type *Type::getStringTy() {
        static Type stringTy(TypeID::String);
        return &stringTy;
    }

    std::string Type::toString() const {
        switch (id) {
        case TypeID::Void:
            return "void";
        case TypeID::Integer32:
            return "i32";
        case TypeID::String:
            return "string";
        default:
            return "unknown";
        }
    }

    // --- Value ---
    std::string Value::toString() const {
        return name;
    }

    // --- ConstantInt ---
    ConstantInt::ConstantInt(int val) : Constant(Type::getInt32Ty(), std::to_string(val)), value(val) {}

    std::string ConstantInt::toString() const {
        return std::to_string(value);
    }

    // --- ConstantObject ---
    ConstantObject::ConstantObject(Type *ty, const std::string &name, const std::string &initVal)
        : Constant(ty, name), initVal(initVal) {}

    std::string ConstantObject::toString() const {
        return getName();
    }

    // --- Instruction ---
    Instruction::Instruction(Type *ty, OpCode op, const std::string &name)
        : Value(ty, name), opcode(op) {}

    std::string Instruction::toString() const {
        if (opcode == OpCode::Call) {
            std::stringstream ss;
            if (type->getID() != TypeID::Void) {
                ss << name << " = ";
            }
            ss << "call " << operands[0]->getName() << "(";
            for (size_t i = 1; i < operands.size(); ++i) {
                if (i > 1)
                    ss << ", ";
                ss << operands[i]->getName();
            }
            ss << ")";
            return ss.str();
        }

        if (opcode == OpCode::Ret) {
            return "ret " + operands[0]->toString();
        }

        std::string opName;
        switch (opcode) {
        case OpCode::LoadC:
            opName = "loadc";
            break;
        case OpCode::Syscall:
            opName = "syscall";
            break;
        case OpCode::Halt:
            opName = "halt";
            break;
        default:
            opName = "unknown";
        }

        std::string res = opName;
        for (auto *op : operands) {
            res += " " + op->toString();
        }
        return res;
    }

    // --- BasicBlock ---
    BasicBlock::BasicBlock(const std::string &name, Function *parent)
        : Value(Type::getVoidTy(), name), parent(parent) {}

    Instruction *BasicBlock::addInstruction(std::unique_ptr<Instruction> inst) {
        Instruction *ptr = inst.get();
        instructions.push_back(std::move(inst));
        return ptr;
    }

    std::string BasicBlock::toString() const {
        std::stringstream ss;
        if (!name.empty()) {
            ss << name << ":\n";
        }

        for (const auto &inst : instructions) {
            ss << "    " << inst->toString() << "\n";
        }
        return ss.str();
    }

    // --- Function ---
    Function::Function(const std::string &name, Type *retType, Module *parent, std::vector<Type *> argTypes)
        : Value(retType, name), parent(parent), argTypes(argTypes) {}

    BasicBlock *Function::addBasicBlock(std::unique_ptr<BasicBlock> bb) {
        BasicBlock *ptr = bb.get();
        basicBlocks.push_back(std::move(bb));
        return ptr;
    }

    std::string Function::toString() const {
        std::stringstream ss;
        if (isDeclaration()) {
            ss << "declare " << name << "(";
            for (size_t i = 0; i < argTypes.size(); ++i) {
                if (i > 0)
                    ss << ", ";
                ss << argTypes[i]->toString();
            }
            ss << ") -> " << type->toString();
        } else {
            ss << "define " << name << "() -> " << type->toString() << " {\n";
            for (const auto &bb : basicBlocks) {
                ss << bb->toString();
            }
            ss << "}";
        }
        return ss.str();
    }

    // --- Module ---
    Module::Module(const std::string &name) : name(name) {}

    void Module::addFunction(std::unique_ptr<Function> func) {
        functions.push_back(std::move(func));
    }

    void Module::addConstantObject(std::unique_ptr<ConstantObject> global) {
        constantObjects.push_back(std::move(global));
    }

    Function *Module::getFunction(const std::string &name) {
        for (const auto &f : functions) {
            if (f->getName() == name)
                return f.get();
        }
        return nullptr;
    }

    ConstantObject *Module::getConstantObject(const std::string &name) {
        for (const auto &g : constantObjects) {
            if (g->getName() == name)
                return g.get();
        }
        return nullptr;
    }

    std::string Module::print() const {
        std::stringstream ss;

        // Print declarations first (declarations are functions with no body)
        for (const auto &f : functions) {
            if (f->isDeclaration()) {
                ss << f->toString() << "\n";
            }
        }
        if (!functions.empty())
            ss << "\n";

        for (const auto &g : constantObjects) {
            ss << "global " << g->getName() << " : " << g->getType()->toString() << " = " << g->getInitValue() << "\n";
        }
        if (!constantObjects.empty())
            ss << "\n";

        for (const auto &f : functions) {
            if (!f->isDeclaration()) {
                ss << f->toString() << "\n";
            }
        }
        return ss.str();
    }

    // --- IRBuilder ---

    Function *IRBuilder::CreateFunction(const std::string &name, Type *retType, std::vector<Type *> argTypes) {
        std::string finalName = name;
        if (name == "main")
            finalName = "@main";
        auto func = std::make_unique<Function>(finalName, retType, module, argTypes);
        Function *ptr = func.get();
        module->addFunction(std::move(func));
        return ptr;
    }

    BasicBlock *IRBuilder::CreateBasicBlock(const std::string &name, Function *parent) {
        auto bb = std::make_unique<BasicBlock>(name, parent);
        BasicBlock *ptr = bb.get();
        parent->addBasicBlock(std::move(bb));
        return ptr;
    }

    ConstantObject *IRBuilder::CreateConstantString(const std::string &name, const std::string &val) {
        // val is passed as raw string e.g. "Hello World!", we need to wrap it in quotes for IR
        // Automatically add '@' prefix if not present
        std::string finalName = name;
        if (finalName.empty() || finalName[0] != '@') {
            finalName = "@" + finalName;
        }

        auto g = std::make_unique<ConstantObject>(Type::getStringTy(), finalName, "\"" + val + "\"");
        ConstantObject *ptr = g.get();
        module->addConstantObject(std::move(g));
        return ptr;
    }

    ConstantObject *IRBuilder::CreateConstantString(const std::string &val) {
        // Auto-generate name: @str0, @str1, etc.
        // The '@' will be added by the named overload.
        std::string name = "str" + std::to_string(module->getNextStringConstantId());
        return CreateConstantString(name, val);
    }

    Instruction *IRBuilder::CreateLoadC(ConstantObject *global, const std::string &destName) {
        auto inst = std::make_unique<Instruction>(Type::getVoidTy(), OpCode::LoadC, destName);
        inst->addOperand(global);
        return insertBlock->addInstruction(std::move(inst));
    }

    Instruction *IRBuilder::CreateSyscall(int code) {
        auto inst = std::make_unique<Instruction>(Type::getVoidTy(), OpCode::Syscall);
        auto constInt = std::make_unique<ConstantInt>(code);
        inst->addOperand(constInt.get());
        module->addConstant(std::move(constInt));
        return insertBlock->addInstruction(std::move(inst));
    }

    Instruction *IRBuilder::CreateHalt() {
        auto inst = std::make_unique<Instruction>(Type::getVoidTy(), OpCode::Halt);
        return insertBlock->addInstruction(std::move(inst));
    }

    Instruction *IRBuilder::CreateCall(Function *func, const std::vector<Value *> &args, const std::string &destName) {
        std::string name = destName;
        if (func->getType()->getID() != TypeID::Void && name.empty()) {
            name = "%" + std::to_string(tempVarCounter++);
        }

        auto inst = std::make_unique<Instruction>(func->getType(), OpCode::Call, name);
        inst->addOperand(func);
        for (auto *arg : args) {
            inst->addOperand(arg);
        }
        return insertBlock->addInstruction(std::move(inst));
    }

    Instruction *IRBuilder::CreateRet(Value *val) {
        auto inst = std::make_unique<Instruction>(Type::getVoidTy(), OpCode::Ret);
        inst->addOperand(val);
        return insertBlock->addInstruction(std::move(inst));
    }
} // namespace Ryntra::Compiler
