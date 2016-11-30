#!/bin/bash
interf=`ifconfig | grep "inet" | wc -l`
echo "Tenemos $interf interfaces activas, cuyas IP son: "
nombre=`ifconfig | cut -d " " -f1`
IP=`ifconfig | grep "inet" | cut -d ":" -f2 | cut -d " " -f1`
echo "$IP"

