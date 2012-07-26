-- Source files should not use the '\r' (CR) character

for file in input_files() do
    line_number = 1
    for line in io.lines(file.path) do
        found = string.find(line, "\r")
        if found then
            vera.report(file, line_number, "\\r (CR) detected in isolation at position "..found)
        end
        line_number = line_number + 1
    end
end
