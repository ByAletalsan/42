# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    monitoring.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 10:53:18 by atalaver          #+#    #+#              #
#    Updated: 2022/10/30 13:13:00 by atalaver         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

#Requisitos
#sudo apt install net-tools
#sudo apt install sysstat
#sudo apt install bc
#Tener /var/log/sudo/sudo_logs

ARCHITECTURE=$(uname -a)

CPUPHY=$(lscpu -p | egrep -v '^#' | wc -l)

CPUVIR=$(lscpu -p | egrep -v '^#' | sort -u -t, -k 2,4 | wc -l)

MEMORY_TOTAL=$(($(vmstat -s | awk '{ if (NR == 1) print $1 }') / 1024))
MEMORY_USE=$(($(vmstat -s | awk '{ if (NR == 2) print $1 }') / 1024))
MEMORY_PERCENT=$(($MEMORY_USE * 100  / $MEMORY_TOTAL))

DISK_TOTAL=$(df -h --total --output=size | awk 'END { print $NF }')
DISK_USE=$(df -h --total --output=used | awk 'END { print $NF }')
DISK_PERCENT=$(df -h --total | awk ' END { print $(NF - 1) }')

CPU=$(mpstat | awk 'END { print $NF }' | tr , .)
CPU_IDLE=$(echo "100 - $CPU" | bc)

LAST_BOOT=$(who -b | awk '{ print $(NF - 1), $NF }')

LVM=$(lsblk -o type | grep lvm | awk '{ if (NR == 1) print $NF }')

CONEXION=$(netstat -ant | grep ESTABLISHED | wc -l)

USERS=$(who | wc -l)

IP=$(hostname -I)
MAC=$(ip addr | grep link/ether | awk '{print $(NF -2)}')

SUDO=$(cat /var/log/sudo/sudo_logs | grep COMMAND | wc -l)

echo "#Architecture: $ARCHITECTURE"
echo "#CPU physical: $CPUPHY"
echo "#vCPU: $CPUVIR"
echo "#Memory Usage: $MEMORY_USE/$MEMORY_TOTAL MB ($MEMORY_PERCENT%)"
echo "#Disk Usage: $DISK_USE/$DISK_TOTAL ($DISK_PERCENT)"
echo "#CPU Load: $CPU_IDLE%"
echo "#Last Boot: $LAST_BOOT"
if test -n $LVM; then
	echo "#LVM use: yes"
else
	echo "#LVM use: no"
fi
echo "#Connexions TCP: $CONEXION ESTABLISHED"
echo "#User Log: $USERS"
echo "#Network: IP $IP ($MAC)"
if test -e '/var/log/sudo/sudo_logs'; then
	echo "#Sudo: $SUDO cmd"
else
	echo "#Sudo: No existe /var/log/sudo/sudo_logs"
fi