
list mpts 
set mpts ""

#jaw 445-629
for { set i 445} { $i < 629} {incr i 7} {
    puts $i
    lappend mpts $i
}

#left upper part
for { set i 400} { $i < 445} {incr i 6} {
    puts $i
    lappend mpts $i
}
for { set i 350} { $i < 400} {incr i 3} {
    puts $i
    lappend mpts $i
}

#front to back left side
for { set i 342} { $i < 350} {incr i 1} {
    puts $i
    lappend mpts $i
}

#front to back middle 200 - 300
for { set i 250} { $i < 300} {incr i 4} {
    puts $i
    lappend mpts $i
}
for { set i 200} { $i < 220} {incr i 3} {
    puts $i
    lappend mpts $i
}
for { set i 221} { $i < 235} {incr i 2} {
    puts $i
    lappend mpts $i
}


#middle right 100-200
for { set i 100} { $i < 150} {incr i 3} {
    puts $i
    lappend mpts $i
}

# right side
for { set i 10} { $i < 100} {incr i 5} {
    puts $i
    lappend mpts $i
}
for { set i 0} { $i < 10} {incr i 4} {
    puts $i
    lappend mpts $i
}


eval "geometry Head_comp monitor_points [split $mpts " "]"
system skel18 link Head_comp update_monitor_points



