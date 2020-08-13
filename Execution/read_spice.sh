grep 'M\|D\|R' *.sp | grep -v '.include\|.end\|.dc\|.control\|.endc\|.model\|plot\|*\|run\|Vd_\|cload\|pulse\|Rl'> temp 
#sed -i '.include\|.end\|.dc\|.control\|.endc\|.model\|plot\|*\|run\|Vd_/d' | grep 'M\|D\|R' analog.sp
#grep M analog.sp> analog.sp1 
awk '{print $2,$4}' temp > spice_final.sp
sed -i 's/vdd/1/g' spice_final.sp
