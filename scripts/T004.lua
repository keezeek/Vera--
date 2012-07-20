-- Some keywords should be immediately followed by a colon

keywords = {"default", "private", "protected", "public"}

proc isKeyword {s} {
    global keywords
    return [expr [lsearch $keywords $s] != -1]
}

for file in vera.input_files() do
    last_keyword_line = 0
    last_keyword_column = 0
    last_keyword_value = ""
    last = ""
    tokens = vera.get_tokens(file, 1, 0, -1, -1, keywords)
    for _, token in ipairs(tokens) do
        if token.name == "colon" then
            if last == "keyword" and last_keyword_line ~= 0 then
                if token.line ~= last_keyword_line or token.column ~= last_keyword_column + string.len(last_keyword_value) then
                    non_white_found = false
                    tb = 
                    foreach tb [getTokens $f $lastKeywordLine [expr $lastKeywordColumn + 1] $line $column {}] {
                        set tbName [lindex $tb 3]
                        if {[lsearch {space newline ccomment cppcomment} $tbName] == -1} {
                            non_white_found = true
                            break
                        end
                    end
                    if non_white_found then
                        vera.report(file, token.line, "colon not immediately after the '"$..last_keyword_value.."' keyword")
                    end
                end
            end
            last = "colon"
        else
            last_keyword_line = token.line
            last_keyword_column = token.column
            last_keyword_value = token.value
            last = "keyword"
        end
    end
end
