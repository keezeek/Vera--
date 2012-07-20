-- File names should be well-formed

max_directory_depth = 8
max_dirname_length = 31
max_filename_length  = 31
max_path_length = 100

for file in vera.input_files() do
    if string.len(file) > max_path_length then
        vera.report(file, 1, "path name too long")
    end

    dir_depth = 0
    for dir in string.gmatch(file, "([^\\/]*)[\\/]") do
        dir_depth = dir_depth + 1

        if string.len(dir) > max_dirname_length then
            vera.report(file, 1, "directory name component too long")
            break
        end

        if not string.match(dir, "^[_%a]") then
            vera.report(file, 1, "directory name should start with alphabetic character or underscore")
            break
        end
            
        if string.find(dir, ".", 1, true) then
            vera.report(file, 1, "directory name should not contain dots")
            break
        end
    end

    if dir_depth >= max_directory_depth then
        vera.report(file, 1, "directory structure too deep")
    end

    filename = string.match(file, "[^\\/]+$")
    if string.len(filename) > max_filename_length then
        vera.report(file, 1, "file name too long")
    end

    if not string.match(filename, "^[_%a]") then
        vera.report(file, 1, "file name should start with alphabetic character or underscore")
    end

    firstdot = string.find(filename, ".", 1, true)
    if firstdot and string.find(filename, ".", firstdot, true) then
        vera.report(file, 1, "file name should not contain more than one dot")
    end
end
