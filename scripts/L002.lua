-- Don't use tab characters

for file in vera.input_files() do
    local line_number = 1
    for line in vera.get_lines(file) do
        if string.match(line, '\t') then
            vera.report(file, line_number, "horizontal tab used")
        end
        line_number = line_number + 1
    end
end
