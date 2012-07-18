-- Line cannot be too long

for file in vera.input_files() do
    local line_number = 1
    for line in vera.get_lines(file) do
        if string.len(line) > 80 then
            vera.report(file, line_number, "line is longer than 80 characters")
        end
        line_number = line_number + 1
    end
end
