add_executable(
        rasm
        rasm.cpp
        assembler/asm.h
        assembler/utils/targetPlat.h
        assembler/utils/path_utils.h
        assembler/utils/string_table.h
        assembler/instruction.h
        assembler/parser.h
        assembler/parser.cpp
        assembler/objectfile.h
        assembler/error/errorhandling.h

        assembler/instruction/instruction_base.h
        assembler/instruction/instruction_info.h
        assembler/instruction/instruction_types.h
        assembler/instruction/instructions.h
        assembler/instruction/registers.h
        assembler/instruction/instruction_encoder.h
        assembler/instruction/instruction_sets/arithmetic.h
        assembler/objectfile.cpp
)

include_directories(rasm/assembler)
include_directories(.)

# 如果是Windows，添加shell32库的链接
if(WIN32)
    target_link_libraries(rasm shell32)
endif()