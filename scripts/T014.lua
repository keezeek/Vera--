-- Source files should refer the Boost Software License

for file in vera.input_files() do
    found = false
    for token in vera.get_tokens(file, 1, 0, -1, -1, {"ccomment", "cppcomment"}) do
        if string.match(token.value, "Boost Software License") then
            found = true
            break
        end
    end
    if not found then
        vera.report(file, 1, "no reference to the Boost Software License found")
    end
end
