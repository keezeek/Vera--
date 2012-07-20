# Semicolons should not be isolated by spaces or comments from the rest of the code

for file in vera.input_files() do
    tokens = vera.get_tokens(file, 1, 0, -1, -1, {"semicolon"})
    for _, token in ipairs(tokens) do
        previous = vera.get_tokens(file, token.line, 0, token.line, token.column, {})
        if #previous == 0 then
            vera.report(file, token.line, "semicolon is isolated from other tokens")
        else
            last = previous[#previous - 1]
            if last.name == "space" or last.name == "ccomment" then
                for_tokens = vera.get_tokens(file, token.line, 0, token.line, token.column, {"for", "leftparen"})
                if #for_tokens < 2 or not(for_tokens[1].name == "for" and for_tokens[2].name == "leftparen") then
                    vera.report(file, token.line, "semicolon is isolated from other tokens")
                end
            end
        end
    end
end
