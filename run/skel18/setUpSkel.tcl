instance ArticulatedObject skel18
system skel18 load sdfast $env(DANCE_DIR)/sdfastObjs/skel18/skel18.sd


set LinkList [system skel18 show links]
set NumLinks [system skel18 show number_of_links]

for { set i 0} { $i < $NumLinks} { incr i} {
    set linkName [lindex $LinkList $i]
    set fileName  $env(DANCE_DIR)/data/models/skel18/${linkName}_center.wrl
    if { [string first "Foot" $linkName] != -1 } {
	set fileName  $env(DANCE_DIR)/data/models/skel18/${linkName}_center_fix.wrl
    } 
    if { [string first "Head" $linkName] != -1 } {
	set fileName  $env(DANCE_DIR)/data/models/skel18/${linkName}_center_fix.wrl
    } 
    if { [string first "Hand" $linkName] != -1 } {
	set fileName  $env(DANCE_DIR)/data/models/skel18/${linkName}_center_fix.wrl
    } 
    if { [string first "Hip" $linkName] != -1 } {
	set fileName  $env(DANCE_DIR)/data/models/skel18/${linkName}_center_fix.wrl
    } 
    
    if { [file exists $fileName] } {
	puts "loading $fileName"
	instance IndexedFaceSet $linkName $fileName
    } else {
	puts "Link |$linkName| File $fileName doesn't exit"
    }
}

set GeomList [show geometry]

# we run through geometries instead of links to avoid the links that do not have geometries
# such as neckDummy
#set collisions 1
for {set i 0} { $i < [llength $GeomList] } { incr i} {
    set linkName [lindex $GeomList $i]
    set geomName [lindex $GeomList $i]

    system skel18 link $linkName geometry $geomName
    system skel18 link $linkName scale 2.6
    # geometry $geomName setupCollision
    system skel18 link $linkName geometry $geomName
    #    system skel18 link $linkName assign_monitor_points 10
}

system skel18 link Left_Foot assign_monitor_points 0 0 -0.1 -0.02 0 -0.095 0.0 -0.02 -0.09 -0.028 -0.02 -0.08 -0.01 -0.025 0.135 0.06 -0.025 0.1
system skel18 link Right_Foot assign_monitor_points 0 0 -0.1 0.02 0 -0.095 0.0 -0.02 -0.09 0.028 -0.02 -0.08 0.01 -0.025 0.135 -0.06 -0.025 0.1
system skel18 link Left_Hand assign_monitor_points 0.09 -0.03 -0.05 0.11 -0.03 0.04 0.05 -0.055 0.06 -0.05 -0.01 0.03 -0.05 -0.01 -0.03
system skel18 link Right_Hand assign_monitor_points -0.09 -0.03 -0.05 -0.11 -0.03 0.04 -0.05 -0.055 0.06 0.05 -0.01 0.03 0.05 -0.01 -0.03
system skel18 link Hip assign_monitor_points 0.03 -0.11 -0.03 -0.03 -0.11 -0.03 -0.045 -0.065 -0.041 0.045 -0.065 -0.041 -0.032 0.07 -0.041 0.032 0.07 -0.041 0.1 0.1 0.025 -0.1 0.1 0.025 0.12 0.09 0.04 -0.12 0.09 0.04 0.135 0.04 0.075 -0.135 0.04 0.075 
system skel18 link Head_comp assign_monitor_points 10
system skel18 link Left_Shoulder assign_monitor_points 10
system skel18 link Right_Shoulder assign_monitor_points 10
system skel18 link Left_Forearm assign_monitor_points 10
system skel18 link Right_Forearm assign_monitor_points 10
system skel18 link Left_Thigh assign_monitor_points 10
system skel18 link Right_Thigh assign_monitor_points 10
system skel18 link Left_Shin assign_monitor_points 10
system skel18 link Right_Shin assign_monitor_points 10
system skel18 link Trunk_comp assign_monitor_points 0.125 -0.08 0.11 -0.125 -0.08 0.11 0.0 0.1 0.09 0.13 0.041 0.050 -0.13 0.041 0.05 0.12 0.06 -0.095 -0.12 0.06 -0.095 0.0 0.09 -0.1 0.07 0.18 -0.09 -0.07 0.18 -0.09 0.14 0.13 -0.07 -0.14 0.13 -0.07
< $env(DANCE_DIR)/run/skel18/skullMonitorPoints.tcl

