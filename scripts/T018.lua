-- using namespace are not allowed in header files

function is_header(file)
    for _, ext in pairs({"h", "hh", "hpp", "hxx", "ipp"}) do
        if string.match(file, "[^%.]+$") == ext then
            return true
        end
    end
end

for file in vera.input_files() do
    if is_header(file) then
        state = "start"
        tokens = vera.get_tokens(file, 1, 0, -1, -1, {"using", "namespace", "identifier"})
        for _, token in ipairs(tokens) do
            if state == "using" and token.name == "namespace" then
                vera.report(file, line, "using namespace not allowed in header file")
            end
            if token.name == "using" then
                line = token.line
            end
            state = token.name
        end
    end
end
