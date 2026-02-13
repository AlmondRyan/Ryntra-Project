#pragma once

namespace Ryntra::Compiler {
    class IVisitor {
    public:
        virtual ~IVisitor() = default;
    };

    template <typename T>
    class Visitor {
    public:
        virtual ~Visitor() = default;
        virtual void visit(T &node) = 0;
    };
} // namespace Ryntra::Compiler
