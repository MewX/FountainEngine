ePath=..
file=`find $ePath/*.cpp $ePath/include/*.h $ePath/include/fountain/*.h| grep -v '~'| grep -v main`
wc $file
co=`sed '/^$/d' $file| wc -l`
echo -e "\nNon-empty lines: $co\n"