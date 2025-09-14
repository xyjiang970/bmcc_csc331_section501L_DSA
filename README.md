# bmcc_csc311_section501L_DSA

## Mac terminal commands:
```bash
g++ main.cpp personType.cpp -o program
./program > output.txt
``` 
Output.txt file containing:
1. Any compilation errors or warnings
2. All program output (cout, printf, etc.)
3. Any runtime error messages
```bash
# Using semicolon (runs second command even if first fails)
(g++ main.cpp personType.cpp -o program 2>&1; ./program 2>&1) > output.txt
```
### Part-by-part Breakdown:
1. The Parentheses `bash ()`
    - Creates a subshell (a new shell process)
    - Everything inside the parenthese is treated as a single unit
    - The final `bash > output` applies to all outputs from everything inside
    
2. `bash g++ main.cpp personType.cpp -o program`
    - Compile the C++ files
    - Output: Creates executable named `program` (if successful)
    
3. `2>&1` (First occurence)
    - `2` = stderr (standard error stream)
    - `1` = stdout (standard output stream)
    - `&1` = whereever stdout is currently going
    - `2>&1` = redirect stderr to the same place as stdout
    
So compilation erros that normally go to stderr will be merged with stdout.

4. The semicolon `;`
    - Command separator meaning "run this command, then run the next command"
    - Always runs the second command, regardless of whether the first succeeded or failed
    - Different from `&&` which only runs second command if first succeeds

5. `./program`
    - Execute the compiled program
    - `./` means "in current directory"
    
6. `2>&1` (Second occurence)
    - Same as before: redirect any runtime errors from the program to stdout
    - So, runtime errors get merged with program output

7. `> output.txt`
    - Redirects all output from the entire subshell to output.txt
    - Overwrites the file if it exists

### Visual Flow:
Compilation errors ──┐
Compilation output ──┼── stdout ──┐
Program output ──────┘            ├── output.txt
Runtime errors ───────────────────┘


## Windows command prompt commands:
```bash

```
<img src="images/windows_sample_output1.png" alt="windows_sample_output1" width="700"/>
<img src="images/windows_sample_output2.png" alt="windows_sample_output2" width="700"/>
