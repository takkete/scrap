proc update_board { pipe } {
	while {[gets $pipe str] >= 0} {
		set first_char [string range $str 0 0]

		if { $first_char == "Y" } {	;# Y in YOU
			break
		}	

		set dst [split $str ","]
		set xy [lindex $dst 0]
		set bw [lindex $dst 1]
		if {$bw == "B"} {
			.b$xy configure -text "●"  -fg black
		} else {
			.b$xy configure -text "●"  -fg white
		}
	}
}

set pipe [open "| ./a.out" r+]

set turnsw 0
for {set i 1} {$i <= 8} {incr i} {
	for {set j 1} {$j <= 8} {incr j} {
		button .b$i$j -font {FreeMono 40 bold} -bg green -activebackground yellow -activeforeground red
		grid .b$i$j -in . -row $i -column $j -sticky nsew
		grid columnconfigure . {1 2 3 4 5 6 7 8} -weight 1 -minsize 60
		grid rowconfigure . {1 2 3 4 5 6 7 8} -weight 1 -minsize 60

		bind .b$i$j <Enter> {
			%W configure -bg red
		}
		bind .b$i$j <Leave> {
			%W configure -bg green
		}
		bind .b$i$j <Button> {
			set x [string range %W 2 2]
			set y [string range %W 3 3]
			puts $pipe "$x,$y\n";flush $pipe

			update_board $pipe

			set turnsw [expr 1 - $turnsw]
		}
	}
}

update_board $pipe
