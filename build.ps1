param([string]$file)
$ext = [System.IO.Path]::GetExtension($file)
$exe = [System.IO.Path]::ChangeExtension($file, ".exe")
if ($ext -eq ".cpp") {
    & "D:\Program Files\MSYS2\ucrt64\bin\g++.exe" -g $file -o $exe
} else {
    & "D:\Program Files\MSYS2\ucrt64\bin\gcc.exe" -g $file -o $exe
}