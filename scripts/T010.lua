-- Identifiers should not be composed of 'l' and 'O' characters only

for file in vera.input_files() do
    local tokens = vera.get_tokens(file, 1, 0, -1, -1, {"identifier"})
    for _, token in ipairs(tokens) do
        if string.match(token.value, "^[lO]+$") then
            vera.report(file, token.line, "identifier should not be composed of only 'l' and 'O'")
        end
    end
end
