-- Comma should not be preceded by whitespace, but should be followed by one

for file in vera.input_files() do
    for comma in vera.get_tokens(file, 1, 0, -1, -1, {"comma"}) do
        set line [lindex $t 1]
        set column [lindex $t 2]
        preceding = vera.get_tokens(file, comma.line, 0, comma.line, comma.column, {})
        if {$preceding == {}} {
            report $f $line "comma should not be preceded by whitespace"
        } else {
            set lastPreceding [lindex [lindex $preceding end] 3]
            if {$lastPreceding == "space"} {
                report $f $line "comma should not be preceded by whitespace"
            }
        }
        following = vera.get_tokens(file, comma.line, comma.column + 1, comma.line + 1, -1, {})
        if {$following != {}} {
            set firstFollowing [lindex [lindex $following 0] 3]
            if {$firstFollowing != "space" && $firstFollowing != "newline" &&
                !($lastPreceding == "operator" && $firstFollowing == "leftparen")} {
                report $f $line "comma should be followed by whitespace"
            }
        }
    end
end
