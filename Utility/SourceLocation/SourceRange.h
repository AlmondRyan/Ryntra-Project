#pragma once

#include "SourceLocation.h"

namespace Ryntra::Compiler {
    struct SourceRange {
        SourceLocation begin;
        SourceLocation end;
    };
}