-- Some keywords should be followed by a single space

function Set(list)
    local set = {}
    for _, l in ipairs(list) do set[l] = true end
    return set
end

keywords = Set{
    "case",
    "class",
    "delete",
    "enum",
    "explicit",
    "extern",
    "goto",
    "new",
    "struct",
    "union",
    "using"
}

state = "other"

for file in vera.input_files() do
    local tokens = vera.get_tokens(file, 1, 0, -1, -1, {})
    for _, token in ipairs(tokens) do
        if state == "keyword" then
            if token.name == "space" and token.value == " " then
                state = "space"
            else
                vera.report(file, line_number, "keyword '"..keyword.."' not followed by a single space")
                state = "other"
            end
        elseif state == "space" then
            if token.name == "newline" then
                vera.report(file, line_number, "keyword '"..keyword.."' not followed by a single space")
            end
            state = "other"
        else
            if keywords[token.name] then
                state = "keyword"
                line_number = token.line
                keyword = token.value
            end
        end
    end
end
