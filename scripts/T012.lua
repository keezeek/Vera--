-- Negation operator should not be used in its short form

for file in vera.input_files() do
    for token in vera.get_tokens(file, 1, 0, -1, -1, {"not"}) do
        if token.value == "!" then
            vera.report(file, token.line, "negation operator used in its short form")
        end
    end
end
