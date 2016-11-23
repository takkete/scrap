set game "a"
image create photo img("f") -file "dra/dra-f.ppm"
image create photo img("p") -file "dra/dra-p.ppm"
image create photo img("m") -file "dra/dra-m.ppm"
image create photo img("t") -file "dra/dra-t.ppm"
image create photo img("h") -file "dra/dra-h.ppm"
image create photo img("s") -file "dra/dra-s.ppm"
image create photo img("c") -file "dra/dra-c.ppm"
image create photo img("v") -file "dra/dra-v.ppm"
proc update_board { pipe } {
	global game
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
		if {$bw == "P"} { .b$xy configure -text "P"  -fg blue }
		if {$bw == "R"} { .b$xy configure -text "R"  -fg blue }
		if {$bw == "I"} { .b$xy configure -text "I"  -fg blue }
		if {$bw == "N"} { .b$xy configure -text "N"  -fg blue }
		if {$bw == "Q"} { .b$xy configure -text "Q"  -fg blue }
		if {$bw == "K"} { .b$xy configure -text "K"  -fg blue }
		if {$bw == "p"} { .b$xy configure -text "p"  -fg blue }
		if {$bw == "r"} { .b$xy configure -text "r"  -fg blue }
		if {$bw == "i"} { .b$xy configure -text "i"  -fg blue }
		if {$bw == "n"} { .b$xy configure -text "n"  -fg blue }
		if {$bw == "q"} { .b$xy configure -text "q"  -fg blue }
		if {$bw == "k"} { .b$xy configure -text "k"  -fg blue }
		if {$game == "dra"} {
		if {$bw == "p"} { .b$xy configure -image img("p") }
		if {$bw == "f"} { .b$xy configure -image img("f") }
		if {$bw == "s"} { .b$xy configure -image img("s") }
		if {$bw == "v"} { .b$xy configure -image img("v") }
		if {$bw == "c"} { .b$xy configure -image img("c") }
		if {$bw == "m"} { .b$xy configure -image img("m") }
		if {$bw == "h"} { .b$xy configure -image img("h") }
		if {$bw == "t"} { .b$xy configure -image img("t") }
		}
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
	if { $color == "map" } {
		set game "dra"
		set boxsize 32
		set boxsize 32
	} else {
		set boxsize 60
		set boxsize 60
	}
}

set turnsw 0
for {set i 1} {$i <= $xmax} {incr i} {
	for {set j 1} {$j <= $ymax} {incr j} {
		if { $color == "check" } {
			if { [expr ($i + $j) % 2] == 0 } {
				set bgcolor(${i}_${j}) black
			} else {
				set bgcolor(${i}_${j}) white
			}
		} else {
			set bgcolor(${i}_${j}) $color
		}
		if {$game == "dra"} {
		button .b${i}_${j} -font {FreeMono 40 bold} -image img("f")  -activebackground yellow -activeforeground red -bd 0  -relief flat
		} else {
		button .b${i}_${j} -font {FreeMono 40 bold} -bg $bgcolor(${i}_${j}) -activebackground yellow -activeforeground red
		}
		grid .b${i}_${j} -in . -row $j -column $i -sticky nsew -ipadx 0 -padx 0 -pady 0 -ipady 0
		grid columnconfigure . all -weight 1 -minsize $boxsize
		grid rowconfigure . all -weight 1 -minsize $boxsize

		bind .b${i}_${j} <Button> {
			set x [string range %W 2 2]
			set y [string range %W 4 4]
			puts $pipe "$x,$y\n";flush $pipe

			update_board $pipe

			set turnsw [expr 1 - $turnsw]
		}
	}
}

update_board $pipe
