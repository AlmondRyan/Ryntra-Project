add_executable(
        rasm
        rasm.cpp
        assembler/asm.h
        assembler/utils/targetPlat.h
        assembler/instruction.h
        assembler/parser.h
        assembler/parser.cpp
        assembler/objectfile.h
        assembler/Error/errorhandling.h

        assembler/instruction/instruction_base.h
        assembler/instruction/instruction_info.h
        assembler/instruction/instruction_types.h
        assembler/instruction/instructions.h
        assembler/instruction/registers.h
        assembler/instruction/instruction_sets/arithmetic.h
)

include_directories(rasm/assembler)
include_directories(.)