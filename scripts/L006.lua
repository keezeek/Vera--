-- Source file should not be too long

for file in vera.input_files() do
    local length = vera.line_count(file)
    if length > 2000 then
        vera.report(file, length, "source file is too long")
    end
end
