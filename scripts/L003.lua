-- No leading and no trailing empty lines

for file in input_files() do
    if string.match(file:get_line(1), "^%s*$") then
        vera.report(1, "leading empty line(s)")
    end
    if string.match(file:get_line(file.line_count), "^%s*$") then
        file:report(file.line_count, "trailing empty line(s)")
    end
end
