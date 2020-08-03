#grep -v "*" analog.sp

#grep -v '.include\|.end\|.dc\|.control\|.endc\|.model\|plot\|*\|run\|Vd_' | grep 'M\|D\|R' analog.sp > analog.sp1
grep 'M\|D\|R' *.sp | grep -v '.include\|.end\|.dc\|.control\|.endc\|.model\|plot\|*\|run\|Vd_\|cload\|pulse'> temp 
#sed -i '.include\|.end\|.dc\|.control\|.endc\|.model\|plot\|*\|run\|Vd_/d' | grep 'M\|D\|R' analog.sp
#grep M analog.sp> analog.sp1 
awk '{print $1,$2,$3,$4,$5,$6,$7,$8}' temp > spice_final.sp
