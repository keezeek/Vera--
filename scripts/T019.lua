-- control structures should have complete curly-braced block of code

filter = {
    "for",
    "if",
    "while",
    "leftparen",
    "rightparen",
    "leftbrace",
    "semicolon"
    }

for file in vera.input_files() do
    for token in vera.get_tokens(file, 1, 0, -1, -1, filter) do

        if state == "control" then
            if token.name == "leftparen" then
                parens = parens + 1
            elseif token.name == "rightparen" then
                parens = parens - 1
                if parens == 0 then
                    state = "expectedblock"
                end
            end
        elseif state == "expectedblock" then
            if token.name ~= "leftbrace" then
                vera.report(file, token.line, "full block {} expected in the control structure")
            end
            state = "block"
        end

        if token.name == "for" or token.name == "if" or token.name == "while" then
            parens = 0
            state = "control"
        end
    end
end
