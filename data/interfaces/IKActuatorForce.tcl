#############################################################################
# Visual Tcl v1.20 Project
#

#################################
# GLOBAL VARIABLES
#
global widget; 

#################################
# USER DEFINED PROCEDURES
#
proc init {argc argv} {

}

init $argc $argv


proc {main} {argc argv} {

}

proc {editIKActuatorForce} {name type} {
global IKActuatorForceName
set IKActuatorForceName $name
Window show .editIKActuatorForce .editIKActuatorForce$name
Window focus .editIKActuatorForce$name
}

proc {Window} {args} {
global vTcl
    set cmd [lindex $args 0]
    set name [lindex $args 1]
    set newname [lindex $args 2]
    set rest [lrange $args 3 end]
    if {$name == "" || $cmd == ""} {return}
    if {$newname == ""} {
        set newname $name
    }
    set exists [winfo exists $newname]
    switch $cmd {
        show {
            if {$exists == "1" && $name != "."} {wm deiconify $name; return}
            if {[info procs vTclWindow(pre)$name] != ""} {
                eval "vTclWindow(pre)$name $newname $rest"
            }
            if {[info procs vTclWindow$name] != ""} {
                eval "vTclWindow$name $newname $rest"
            }
            if {[info procs vTclWindow(post)$name] != ""} {
                eval "vTclWindow(post)$name $newname $rest"
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
    wm geometry $base 200x200+0+0
    wm maxsize $base 1604 1185
    wm minsize $base 104 1
    wm overrideredirect $base 0
    wm resizable $base 1 1
    wm withdraw $base
    wm title $base "vt"
    ###################
    # SETTING GEOMETRY
    ###################
}

proc vTclWindow.editIKActuatorForce {base} {
global IKActuatorForceName
    if {$base == ""} {
        set base .editIKActuatorForce
    }
    if {[winfo exists $base]} {
        wm deiconify $base; return
    }
    ###################
    # CREATING WIDGETS
    ###################
    toplevel $base -class Toplevel \
        -relief raised 
    wm focusmodel $base passive
    wm geometry $base 195x270+630+305
    wm maxsize $base 1604 1185
    wm minsize $base 104 1
    wm overrideredirect $base 0
    wm resizable $base 1 1
    wm deiconify $base
    wm title $base "$IKActuatorForceName"
    menubutton $base.men21 \
        -menu $base.men21.m -padx 5 -pady 4 -relief groove -text Constraints 
    menu $base.men21.m \
        -activeborderwidth 1 -borderwidth 1 -cursor {} -font {Tahoma 8} 
    $base.men21.m add command \
        -command "actuator $IKActuatorForceName addConstraint position" \
        -label {Add position constraint} 
    $base.men21.m add command \
        -command "actuator $IKActuatorForceName addConstraint orientation" \
        -label {Add orientation constraint} 
    $base.men21.m add command \
        -command "actuator $IKActuatorForceName removeConstraint" \
        -label {Remove constraint} 
    $base.men21.m add command \
        -command "actuator $IKActuatorForceName reset" -label {Reset all} 
    scale $base.sca22 \
        -label {Joint weight} -orient horizontal -resolution 0.1 -to 2.0 \
        -variable JointWeight$IKActuatorForceName 
    scale $base.sca23 \
        -label {Constraint weight} -orient horizontal -resolution 0.1 -to 2.0 \
        -variable ConstraintWeight$IKActuatorForceName 
    button $base.but24 \
        -padx 9 -pady 3 -text {Toggle IK algorithm} -command "actuator $IKActuatorForceName solveMode" 
    ###################
    # SETTING GEOMETRY
    ###################
    place $base.men21 \
        -x 10 -y 15 -anchor nw -bordermode ignore 
    place $base.sca22 \
        -x 15 -y 50 -anchor nw -bordermode ignore 
    place $base.sca23 \
        -x 15 -y 115 -anchor nw -bordermode ignore 
    place $base.but24 \
        -x 25 -y 235 -anchor nw -bordermode ignore 
}

Window show .

main $argc $argv
