#!/bin/sh


#for i in {1..1000};
#do cp fn.sp "fn$i.sp";
#done

echo "********************Spice File Extractor********************"
echo -e "\n"
echo -e "Invoking spice file extractor"
for file in *.sp
do
echo -e "Converting $file to readable spice format"

#grep 'M\|D\|R' *.sp | grep -v '.include\|.end\|.dc\|.control\|.endc\|.model\|plot\|*\|run\|Vd_\|cload\|pulse\|Rl'> $file.tmp 
grep 'M\|D\|R' $file | grep -v '.include\|.end\|.dc\|.control\|.endc\|.model\|plot\|*\|run\|Vd_\|cload\|pulse\|Rl'> $file.tmp 
awk '{print $2,$4}' $file.tmp > $file.spice_final
sed -i 's/vdd/1/g' $file.spice_final
echo -e "Converted $file to $file.spice_final"
rm -rf $file.tmp
echo -e "\n"
done
echo -e "Converted all the spice files"
