-- Keywords catch, for, if and while should be followed by a single space

keywords = {"catch", "for", "if", "switch", "while"}

for file in vera.input_files() do
    tokens = vera.get_tokens(file, 1, 0, -1, -1, keywords)
    for _, token in ipairs(tokens) do
        following = vera.get_tokens(file, token.line, token.column + string.len(token.value), token.line + 1, -1, {})
        if #following < 2 or following[1].value ~= " " or following[2].value ~= "(" then
            vera.report(file, token.line, "keyword '"..token.name.."' not followed by a single space")
        end
    end
end
