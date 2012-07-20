-- Keywords return and throw should be immediately followed by a semicolon or a single space

for file in vera.input_files() do
    tokens = vera.get_tokens(file, 1, 0, -1, -1, {"return", "throw"})
    for _, token in ipairs(tokens) do
        following = vera.get_tokens(file, token.line, token.column + string.len(token.value), token.line + 1, 0, {})[1]
        if not following or (following.value ~= ";" and following.value ~= " ") then
            vera.report(file, token.line, "keyword '"..token.value.."' not immediately followed by a semicolon or a single space")
        end
    end
end
