-- Source files should contain the copyright notice

for file in vera.input_files() do
    found = false
    tokens = vera.get_tokens(file, 1, 0, -1, -1, {"ccomment", "cppcomment"})
    for _, token in ipairs(tokens) do
        if string.match(token.value, "[Cc]opyright") then
            found = true
            break
        end
    end
    if not found then
        vera.report(file, 1, "no copyright notice found")
    end
end
