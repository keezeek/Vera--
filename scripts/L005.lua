-- There should not be too many consecutive empty lines

for file in vera.input_files() do
    local line_number = 1
    local empty_count = 0
    local reported = false
    for line in vera.get_lines(file) do
        if string.match(line, "^%s*$") then
            empty_count = empty_count + 1
            if empty_count > 2 and not reported then
                vera.report(file, line_number, "too many consecutive empty lines")
                reported = true
            end
        else
            empty_count = 0
            reported = false
        end
        line_number = line_number + 1
    end
end
