-- One-line comments should not have forced continuation

for file in vera.input_files() do
    local tokens = vera.get_tokens(file, 1, 0, -1, -1, {"cppcomment"})
    for _, token in ipairs(tokens) do
        local line = vera.get_line(file, token.line)
        if string.match(line, "\\$") then
            vera.report(file, token.line, "line-continuation in one-line comment")
        end
    end
end
