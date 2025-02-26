#include <iostream>
#include <iomanip>
#include "assembler/asm.h"

using namespace Ryntra::rasm;

int main() {
    RAssembler assembler;

//    std::string testCode = R"(
//        add rax, rbx        ; Register to Register
//        sub rcx, #42        ; Immediate
//        mul rdx             ; Single Operand
//        div r8              ; Divide Operation
//        and rsi, rdi        ; And Operation
//        or  r9, r10         ; Or Operation
//        xor r11, [rbx]      ; Exclusive Or Operation
//    )";

    std::string IntelSyntaxAssemblyTest, curLine;
    std::ifstream isat("D:\\RyntraProject\\rasm\\test\\HelloWorld.asm", std::ios_base::in);

    if (!isat.is_open()) {
        std::cout << "Cannot open source file." << std::endl;
    }

    while (std::getline(isat, curLine)) {
        IntelSyntaxAssemblyTest += curLine + "\n";
    }

    if (!IntelSyntaxAssemblyTest.empty()) {
        std::cout << IntelSyntaxAssemblyTest << std::endl;
    }

    isat.close();
    bool res = assembler.assembleFromString(IntelSyntaxAssemblyTest, TargetPlatform::x64);
    
//    bool res = assembler.assembleFromString(testCode, TargetPlatform::x64);
//
//    if (res) {
//        std::cout << "Assemble Success!" << std::endl;
//    } else {
//        std::cout << "Assemble Fail!" << std::endl;
//    }

    return 0;
}