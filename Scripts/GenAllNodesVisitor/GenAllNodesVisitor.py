def main():
    with open('NodesList.txt', 'r', encoding='utf-8') as f:
        node_names = [line.strip() for line in f if line.strip()]

    if not node_names:
        print("Warning: NodesList.txt is empty or cannot be properly read")
        return

    inheritance_lines = ["public IVisitor"]
    for name in node_names:
        inheritance_lines.append(f"public Visitor<{name}>")

    inheritance = ",\n".join(inheritance_lines)

    visit_methods = []
    for name in node_names:
        visit_methods.append(f"virtual void visit({name} &node) override {{}}")

    visit_block = "\n".join(visit_methods)

    code = f"""#pragma once
#include "ASTVisitor.h"
#include "ASTNodes.h"
namespace Ryntra::Compiler {{
class AllNodesVisitor : {inheritance}
{{
public:
virtual ~AllNodesVisitor() = default;
{visit_block}
}};
}}
"""

    with open('AllNodesVisitor.h', 'w', encoding='utf-8') as out_file:
        out_file.write(code)

if __name__ == '__main__':
    main()