-- No trailing whitespace

for file in vera.input_files() do
    local line_number = 1
    for line in vera.get_lines(file) do
        if string.match(line, "%s+$") then
            vera.report(file, line_number, "trailing whitespace")
        end
        line_number = line_number + 1
    end
end
