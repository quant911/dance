#!/usr/local/bin/bltwish
#############################################################################
# Visual Tcl v1.20 Project
#

#################################
# GLOBAL VARIABLES
#
global widget; 
global PlaneGroundName ; set PlaneGroundName "Ground"

#################################
# USER DEFINED PROCEDURES
#
proc init {argc argv} {

}

init $argc $argv

proc {main} {argc argv} {

}

proc {editPlaneGround} {name type} {
global PlaneGroundName
global widget

set PlaneGroundName $name
Window show .editPlaneGround .editPlaneGround$name
Window focus .editPlaneGround$name
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
    wm geometry $base 1x1+0+0
    wm maxsize $base 1265 994
    wm minsize $base 1 1
    wm overrideredirect $base 0
    wm resizable $base 1 1
    wm withdraw $base
    wm title $base "vt.tcl"
    ###################
    # SETTING GEOMETRY
    ###################
}

proc vTclWindow.editPlaneGround {base} {
global PlaneGroundName
    if {$base == ""} {
        set base .editPlaneGround
    }
    if {[winfo exists $base]} {
        wm deiconify $base; return
    }
    ###################
    # CREATING WIDGETS
    ###################
    toplevel $base -class Toplevel
    wm focusmodel $base passive
    wm geometry $base 122x227+1044+241
    wm maxsize $base 1265 994
    wm minsize $base 1 1
    wm overrideredirect $base 0
    wm resizable $base 1 1
    wm deiconify $base
    wm title $base "$PlaneGroundName"
    scale $base.sca21 \
        -label Stiffness -orient horiz -to 25000.0 \
        -variable "stiffness$PlaneGroundName"
    scale $base.sca22 \
        -label Damping -orient horiz -to 1500.0 \
        -variable "damping$PlaneGroundName"
    scale $base.sca23 \
        -label Friction -orient horiz -to 1.0 \
	-resolution 0.05 \
        -variable "friction$PlaneGroundName" 
    ###################
    # SETTING GEOMETRY
    ###################
    place $base.sca21 \
        -x 5 -y 5 -anchor nw -bordermode ignore 
    place $base.sca22 \
        -x 5 -y 75 -anchor nw -bordermode ignore 
    place $base.sca23 \
        -x 10 -y 140 -anchor nw -bordermode ignore 
}

Window show .

main $argc $argv

