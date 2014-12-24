####TDD : doing some tests

The makefile has been designed to tests features automatically.
It builds the project, and then run it several times with specific arguments
corresponding to specific allocations and specific assertions :
./executable [methodeOfAllocation requestedSize] [assert [usedLengthInEachFinalMemoryBlock]]

Standard output is redirected to /dev/null for most orders.
In case an assertion fails, the program shows the menu, and asks the user what to do. If ever that happens while the standard output has been redirected to /dev/null, an error pops on the screen (because /dev/null can't provide the program with user inputs). Hence, would it happen to you, delete "> /dev/null" at the end of the line in the makefile.

