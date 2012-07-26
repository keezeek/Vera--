-- Line cannot be too long

for file in input_files() do
    for line = 1, file.line_count do
        if string.len(file:get_line(line)) > 80 then
            file:report(line, "line is longer than 80 characters")
        end
    end
end
