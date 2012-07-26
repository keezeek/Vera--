-- No trailing whitespace

for file in input_files() do
    for line = 1, file.line_count do
        if string.match(file:get_line(line), "%s+$") then
            file:report(line, "trailing whitespace")
        end
    end
end
