
#!/usr/bin/tclsh
set fp [open "spice_final.sp" r]
set rfp [open "spice_final.sp.tmp" w+]

set i 10
#while {[gets $fp line]> -1} {incr i}
#	return i }
#	puts $i


#set count [llength [split [read -nonewline $fp] "\n"]]

set fp [open "spice_final.sp" r]

while {[gets $fp line] >= 0} {
        set newline [string map {vdd 1 out 5}  $line]
        puts $rfp $newline
}


close $fp
close $rfp

#set a [open "spice_final.sp.tmp" a]
#
#puts $a $count
#close $a
#
#
#
# Read lines of file (name in “filename” variable) into variable “lines”
#set f [open "spice_final.sp.tmp" "r"]
#set lines [split [read $f] "\n"]
#close $f
#
## Find the insertion index in the reversed list
#set idx [lsearch -regexp [lreverse $lines] "^#define "]
#if {$idx < 0} {
#    error "did not find insertion point in $f"
#}
#
## Insert the lines (I'm assuming they're listed in the variable “linesToInsert”)
#set lines [linsert $lines end-$idx {*}$count]
#
## Write the lines back to the file
#set f [open "spice_final.sp.tmp" "w"]
#puts $f [join $lines "\n"]
#close $f

file rename -force "spice_final.sp.tmp" "spice_final.sp"

