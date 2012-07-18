-- No leading and no trailing empty lines

for file in vera.input_files() do
    local line_count = vera.line_count(file)
    if line_count > 0 then
        local first_line = vera.get_line(file, 1)
        if string.match(first_line, "^%s*$") then
            vera.report(file, 1, "leading empty line(s)")
        end

        local last_line = vera.get_line(file, line_count)
        if string.match(last_line, "^%s*$") then
            vera.report(file, line_count, "trailing empty line(s)")
        end
    end
end
