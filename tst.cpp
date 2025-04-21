#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

int main() {
    llvm::LLVMContext cont;
    std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("TestMod", cont);

    llvm::FunctionType *functionType = llvm::FunctionType::get(llvm::Type::getInt32Ty(cont), false);
    llvm::Function *mainFunc = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, "main", module.get());

    llvm::BasicBlock *ent = llvm::BasicBlock::Create(cont, "entry", mainFunc);
    llvm::IRBuilder<> builder(ent);

    builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(cont), 32));
    module->print(llvm::outs(), nullptr);

    return 0;
}