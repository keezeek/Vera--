-- Source files should contain the copyright notice

for file in vera.input_files() do
    found = false
    for token in vera.get_tokens(file, 1, 0, -1, -1, {"ccomment", "cppcomment"}) do
        if string.match(token.value, "copyright") then
            found = true
            break
        end
    end
    if not found then
        vera.report(file, 1, "no copyright notice found")
    end
end
