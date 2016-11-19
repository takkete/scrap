set pagination off

file a.out

break 60

run

# Black scanf x y
set x=3
set y=4
jump 61

# White scanf x y
set x=3
set y=5
jump 61

# Black scanf x y
set x=3
set y=6
jump 61

quit
