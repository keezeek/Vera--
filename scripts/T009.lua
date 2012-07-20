-- Comma should not be preceded by whitespace, but should be followed by one

for file in vera.input_files() do
    tokens = vera.get_tokens(file, 1, 0, -1, -1, {"comma"})
    for _, comma in ipairs(tokens) do

        preceding = vera.get_tokens(file, comma.line, 0, comma.line, comma.column, {})
        if #preceding == 0 then 
            vera.report(file, comma.line, "comma should not be preceded by whitespace")
        else
            last_preceding = preceding[#preceding-1].name
            if last_preceding == "space" then
                vera.report(file, comma.line, "comma should not be preceded by whitespace")
            end
        end
        
        following = vera.get_tokens(file, comma.line, comma.column + 1, comma.line + 1, -1, {})
        if #following ~= 0 then
            local first_following = following[1].name
            if first_following ~= "space" and first_following ~= "newline" and not(last_preceding == "operator" and first_following == "leftparen") then
                vera.report(file, comma.line, "comma should be followed by whitespace")
            end
        end
    end
end
