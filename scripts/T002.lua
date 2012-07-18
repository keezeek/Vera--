-- Reserved names should not be used for preprocessor macros

keywords = {
    "asm",
    "auto",
    "bool",
    "break",
    "case",
    "catch",
    "char",
    "class",
    "const",
    "const_cast",
    "continue",
    "default",
    "delete",
    "goto",
    "do",
    "double",
    "dynamic_cast",
    "else",
    "enum",
    "explicit",
    "export",
    "extern",
    "false",
    "float",
    "for",
    "friend",
    "if",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "new",
    "operator",
    "private",
    "protected",
    "public",
    "register",
    "reinterpret_cast",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_cast",
    "struct",
    "switch",
    "template",
    "this",
    "throw",
    "true",
    "try",
    "typedef",
    "typeid",
    "typename",
    "union",
    "unsigned",
    "using",
    "virtual",
    "void",
    "volatile",
    "wchar_t",
    "while",
    "and",
    "and_eq",
    "bitand",
    "bitor",
    "compl",
    "not",
    "not_eq",
    "or",
    "or_eq",
    "xor",
    "xor_eq"
}

for file in vera.input_files() do
    for token in vera.get_tokens(file, 1, 0, -1, -1, {"pp_define"}) do
        local line = vera.get_line(file, token.line)
        local macro = string.match(line, "#%s*define%s*(%S+)")

        if string.match(macro, "^_%u") or string.match(macro, "__") then
            vera.report(file, token.line, "reserved name used for macro (incorrect use of underscore)")
        end

        for _, value in pairs(keywords) do
            if value == macro then
                vera.report(file, token.line, "reserved name used for macro (keyword or alternative token redefined)")
                break
            end
        end
    end
end
