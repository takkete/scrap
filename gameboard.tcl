proc update_board { pipe } {
	while {[gets $pipe str] >= 0} {
		set first_char [string range $str 0 0]

		if { $first_char == "Y" } {	;# Y in YOU
			break
		}	

		set arr [split $str ","]
		set xy [lindex $arr 0]
		set bw [lindex $arr 1]

		if {$bw == "B"} { .b$xy configure -text "●"  -fg black }
		if {$bw == "W"} { .b$xy configure -text "●"  -fg white }
		if {$bw == "f"} { .b$xy configure -text "歩"  -fg black }
		if {$bw == "o"} { .b$xy configure -text "王"  -fg black }
		if {$bw == "a"} { .b$xy configure -text "金"  -fg black }
		if {$bw == "g"} { .b$xy configure -text "銀"  -fg black }
		if {$bw == "u"} { .b$xy configure -text "桂"  -fg black }
		if {$bw == "s"} { .b$xy configure -text "香"  -fg black }
		if {$bw == "t"} { .b$xy configure -text "飛"  -fg black }
		if {$bw == "x"} { .b$xy configure -text "角"  -fg black }
	}
}

set pipe [open "| ./a.out" r+]

gets $pipe str
set arr [split $str ","]
set cmd [lindex $arr 0]
if { $cmd == "INIT" } {
	set xmax [lindex $arr 1]
	set ymax [lindex $arr 2]
	set color [lindex $arr 3]
}

set turnsw 0
for {set i 1} {$i <= $xmax} {incr i} {
	for {set j 1} {$j <= $ymax} {incr j} {
		button .b$i$j -font {FreeMono 40 bold} -bg $color -activebackground yellow -activeforeground red
		grid .b$i$j -in . -row $j -column $i -sticky nsew
		grid columnconfigure . all -weight 1 -minsize 60
		grid rowconfigure . all -weight 1 -minsize 60

		bind .b$i$j <Enter> {
			%W configure -bg red
		}
		bind .b$i$j <Leave> {
			%W configure -bg $color
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
