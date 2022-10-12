#############################################################################
# Visual Tcl v1.20 Project
#

#################################
# GLOBAL VARIABLES
#
global InPlayBackplayBack; 
global KinematicActuatorName; 
global KinematicActuatorTimeplayBack; 
global widget; 

#################################
# USER DEFINED PROCEDURES
#
proc init {argc argv} {
global KinematicActuatorName;
set KinematicActuatorName "playBack"

global KinematicActuatorTime$KinematicActuatorName ;
global InPlayBack$KinematicActuatorName;

set InPlayBack$KinematicActuatorName 0
set KinematicActuatorTime$KinematicActuatorName 0
}

init $argc $argv


proc {KinActRecord} {action name} {
actuator $name record $action
}

proc {KinActRewind} {action name} {
actuator $name  $action
all view redisplay
}

proc {KinActSetPlayTimeStep} {name time} {
global PlayTimeStep$name
set PlayTimeStep$name $time
}

proc {KinActSetRecordTimeStep} {name time} {
global RecordTimeStep$name
set RecordTimeStep$name $time
}

proc {KinematicActuatorDeleteAllFrames} {name} {
actuator $name delete all
}

proc {KinematicActuatorDeleteFrame} {name} {
actuator $name delete key_frame
}

proc {KinematicActuatorLoadAnimFile} {name} {
set LoadFile [tk_getOpenFile -title  "Select file anim file" -defaultextension .ani -filetypes  {{ "Animation files" {.ani}}} -initialdir .]

if { $LoadFile != "" } {
    actuator $name load_anim $LoadFile
}
}

proc {KinematicActuatorPlay} {mode name} {
if { $mode == 0 } {
    actuator $name play stop
}  elseif { $mode == 1 } {
    actuator $name play start
} elseif { $mode == 3 } {
     actuator $name show_next_key_frame
}
return
}

proc {KinematicActuatorPlayOld} {mode name} {
upvar InPlayBack$name inPlayBack
set  afterTimeStep 1 ;

all view redisplay
if { $mode == 0 } {
    puts "Stopping play back"
    set inPlayBack 0
    return
} elseif { $mode == 1 } {
    if { $inPlayBack == 1 } {
	puts "stop the one running first"
	return 
    }
    actuator $name rewind
    set inPlayBack 1
    actuator $name show_next_key_frame
    after $afterTimeStep KinematicActuatorPlay 2 $name
} elseif { $mode == 2 } {
    if { $inPlayBack == 0 } { return }
    actuator $name show_next_key_frame
    all view redisplay
    after $afterTimeStep KinematicActuatorPlay  2 $name
} elseif { $mode == 3 } {
    actuator $name show_next_key_frame
    all view redisplay
} else {
    puts "Wrong mode"
}
}

proc {KinematicActuatorRecordFrame} {name} {
upvar  KinematicActuatorTime$name KinematicActuatorTime
    actuator $name record key_frame $KinematicActuatorTime
}

proc {KinematicActuatorSaveAnimFile} {name} {
set SaveFile [tk_getSaveFile -title  "Select file anim file" -defaultextension .ani -filetypes  {{ "Animation files" {.ani}}} -initialdir .]

if { $SaveFile != "" } {
    actuator $name save_anim $SaveFile
}
}

proc {SetKinematicActuatorTime} {name time} {
upvar KinematicActuatorTime$name KinematicActuatorTime

set KinematicActuatorTime $time
if [catch { actuator $name show_key_frame $time } result] {
#    tkMessageBox -message "No keyframes present"
    return ;
}
all view redisplay
}

proc {SetKinematicPingPong} {name} {
upvar KinematicPingPong$name KinematicPingPong

actuator $name pingpong $KinematicPingPong
}

proc {editKinematicActuator} {name type} {
global KinematicActuatorName
    global widget
    
    set KinematicActuatorName $name

    global InPlayBack$KinematicActuatorName
#    global KinematicActuatorTime$KinematicActuatorName
    set InPlayBack$KinematicActuatorName 0
#    set KinematicActuatorTime$KinematicActuatorName 0.0
    Window show  .editKinematicActuator .editKinematicActuator$name $name
    Window focus .editKinematicActuator$name
}

proc {main} {argc argv} {

}

proc {Window} {args} {
global vTcl
    set cmd [lindex $args 0]
    set name [lindex $args 1]
    set newname [lindex $args 2]
    set actName [lindex $args 3]
    set rest [lrange $args 4 end]
    if {$name == "" || $cmd == ""} {return}
    if {$newname == ""} {
        set newname $name
    }
    set exists [winfo exists $newname]
    switch $cmd {
        show {
            if {$exists == "1" && $name != "."} {wm deiconify $name; return}
            if {[info procs vTclWindow(pre)$name] != ""} {
                eval "vTclWindow(pre)$name $newname $rest $actName"
            }
            if {[info procs vTclWindow$name] != ""} {
                eval "vTclWindow$name $newname $rest $actName"
            }
            if {[info procs vTclWindow(post)$name] != ""} {
                eval "vTclWindow(post)$name $newname $rest $actName"
            }
        }
        hide    { if $exists {wm withdraw $newname; return} }
        iconify { if $exists {wm iconify $newname; return} }
        destroy { if $exists {destroy $newname; return} }
    }
}

#################################
# VTCL GENERATED GUI PROCEDURES
#

proc vTclWindow. {base} {
    if {$base == ""} {
        set base .
    }
    ###################
    # CREATING WIDGETS
    ###################
    wm focusmodel $base passive
    wm geometry $base 1x1+0+0
    wm maxsize $base 1265 994
    wm minsize $base 104 1
    wm overrideredirect $base 0
    wm resizable $base 1 1
    wm withdraw $base
    wm title $base "vt.tcl"
    ###################
    # SETTING GEOMETRY
    ###################
}

proc vTclWindow.editKinematicActuator {base actName} {
    if {$base == ""} {
        set base .editKinematicActuator
    }
    if {[winfo exists $base]} {
        wm deiconify $base; return
    }
    ###################
    # CREATING WIDGETS
    ###################
    toplevel $base -class Toplevel
    wm focusmodel $base passive
    wm geometry $base 342x345+324+172
    wm maxsize $base 1265 994
    wm minsize $base 104 1
    wm overrideredirect $base 0
    wm resizable $base 1 1
    wm title $base "Actuator $actName"
    button $base.but21 \
        -command "KinematicActuatorPlay 3 $actName" -padx 11 -pady 4 \
        -text NextFrame 
    button $base.but22 \
        -command "KinematicActuatorPlay 1 $actName" -padx 11 -pady 4 \
        -text Play 
    button $base.but23 \
        -command "KinematicActuatorPlay 0 $actName" -padx 11 -pady 4 \
        -text Stop 
    scale $base.sca24 \
        -command "KinActSetPlayTimeStep $actName" -from 0.001 \
        -label {Play time step} -orient horiz -resolution 0.001 -to 0.1 \
        -variable playTimeStep$actName 
    button $base.but25 \
        -command "KinActRewind rewind $actName" -padx 11 -pady 4 -text Rewind 
    label $base.lab26 \
        -background #fed202 -borderwidth 1 -relief raised \
        -text "Playback Menu"
    button $base.but20 \
        -command "KinActRecord start $actName" -padx 11 -pady 4 -text START 
    label $base.lab21 \
        -background #e0c000 -borderwidth 1 -relief raised -text {Record Menu} 
    button $base.but24 \
        -command "KinActRecord stop $actName" -padx 11 -pady 4 -text STOP 
    menu $base.m20 \
        -cursor {} 
    scale $base.sca21 \
        -command "KinActSetRecordTimeStep $actName" -from 0.001 \
        -label {Record time step} -orient horiz -resolution 0.001 -to 0.1 \
        -variable recordTimeStep$actName 
    button $base.but26 \
        -command "KinematicActuatorSaveAnimFile $actName" -padx 11 -pady 4 \
        -text {Save on file} 
    button $base.but27 \
        -command "KinematicActuatorLoadAnimFile $actName" -padx 11 -pady 4 \
        -text Load 
    button $base.but28 \
        -command "KinematicActuatorRecordFrame $actName" -padx 11 -pady 4 \
        -text {Record Frame} 
    button $base.but30 \
        -command "KinematicActuatorDeleteFrame $actName" -padx 11 -pady 4 \
        -text Delete 
    button $base.but31 \
        -command "KinematicActuatorDeleteAllFrames $actName" -padx 11 -pady 4 \
        -text {Delete all} 
    menu $base.m21 \
        -cursor {} 
    scale $base.sca22 \
        -command "SetKinematicActuatorTime $actName" -orient horiz \
        -resolution 0.1 -to 15.0 -variable KinematicActuatorTime$actName 
    checkbutton $base.che20 \
        -command "SetKinematicPingPong $actName" \
        -indicatoron 0 -text PingPong -variable KinematicPingPong$actName
    ###################
    # SETTING GEOMETRY
    ###################
    place $base.but21 \
        -x 5 -y 30 -width 61 -height 34 -anchor nw -bordermode ignore 
    place $base.but22 \
        -x 140 -y 30 -anchor nw -bordermode ignore 
    place $base.but23 \
        -x 200 -y 30 -anchor nw -bordermode ignore 
    place $base.sca24 \
        -x 5 -y 65 -anchor nw -bordermode ignore 
    place $base.but25 \
        -x 260 -y 30 -anchor nw -bordermode ignore 
    place $base.lab26 \
        -x 0 -y 5 -width 331 -height 18 -anchor nw -bordermode ignore 
    place $base.but20 \
        -x 10 -y 165 -anchor nw -bordermode ignore 
    place $base.lab21 \
        -x -15 -y 125 -width 346 -height 18 -anchor nw -bordermode ignore 
    place $base.but24 \
        -x 85 -y 165 -anchor nw -bordermode ignore 
    place $base.sca21 \
        -x 170 -y 150 -width 116 -height 59 -anchor nw -bordermode ignore 
    place $base.but26 \
        -x 130 -y 70 -anchor nw -bordermode ignore 
    place $base.but27 \
        -x 225 -y 70 -anchor nw -bordermode ignore 
    place $base.but28 \
        -x 10 -y 235 -anchor nw -bordermode ignore 
    place $base.but30 \
        -x 140 -y 235 -anchor nw -bordermode ignore 
    place $base.but31 \
        -x 225 -y 235 -anchor nw -bordermode ignore 
    place $base.sca22 \
        -x 20 -y 275 -width 291 -height 43 -anchor nw -bordermode ignore 
    place $base.che20 \
        -x 70 -y 30 -width 63 -height 32 -anchor nw -bordermode ignore 
}

Window show .

main $argc $argv
