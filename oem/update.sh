dd if=/dev/mtdblock3 of=/tmp/temp bs=1024 count=8
if [ $? -eq 0 ];then
	sed -e "s/\(<$1>\)\([^<]*\)/\1$2/" /tmp/temp | tee /tmp/temp2 > /dev/null
	if [ $? -eq 0 ];then
		dd if=/tmp/temp2 of=/dev/mtdblock3 bs=1024 count=8
		if [ $? -ne 0 ];then
			dd if=/dev/zero of=/dev/mtdblock3
			READ_INFO
			echo "update para finish failed"
			exit 0
		fi	
		rm /tmp/temp2
	else
		dd if=/dev/zero of=/dev/mtdblock3
		READ_INFO
		echo "update para finish failed"
		exit 0
	fi
	rm /tmp/temp
else
	echo "update para finish failed"
	exit 0
fi
echo "update para finish ok"
exit 0
