-- Don't use tab characters

for file in input_files() do
    for line = 1, file.line_count do
        if string.match(file:get_line(line), '\t') then
            file:report(line, "horizontal tab used")
        end
    end
end
