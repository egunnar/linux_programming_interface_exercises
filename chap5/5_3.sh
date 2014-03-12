#!/bin/bash 
./atomic_append f1 1000000 & ./atomic_append f1 1000000 
./atomic_append f2 1000000 do_append & ./atomic_append f2 1000000 do_append

# results
# egartz@eriks-computer:~/programming/linux_programming_interface/my_programs/chap5$ ls -l f1 f2
# -rw-rw-r-- 1 egartz egartz 1868511 Mar 11 21:54 f1
# -rw-rw-r-- 1 egartz egartz 2000002 Mar 11 21:54 f2
# egartz@eriks-computer:~/programming/linux_programming_interface/my_programs/chap5$

