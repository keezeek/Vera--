-- Calls to min/max should be protected against accidental macro substitution

for file in vera.input_files() do
    tokens = vera.get_tokens(file, 1, 0, -1, -1, {"identifier"})
    for _, identifier in ipairs(tokens) do
        if identifier.value == "min" or identifier.value == "max" then
            line = vera.get_line(file, identifier.line);
            line = string.sub(line, identifier.column + 4)
            if string.match(line, "^%s*[(]") then
                vera.report(file, identifier.line, "min/max potential macro substitution problem")
            end
        end
    end
end
