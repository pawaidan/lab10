#!/bin/bash

BASETEMP=$(./tempread)
CBASETEMP=$(($BASETEMP/1000))
TWO=$(($CBASETEMP+1))
THREE=$(($CBASETEMP+2))

RED=1
YELLOW=2
GREEN=3

while [ true ]
do
  CURTEMP=$(./tempread)
  STATE=$?
  CONVERT=$(($CURTEMP/1000))
  
  echo $CONVERT
  
  if [ $CONVERT -gt $CBASETEMP ] && [ $CONVERT -lt $TWO ] && [ $STATE -eq 0 ]
  then 
    gpio write $GREEN 1
    gpio write $YELLOW 0
    gpio write $RED 0

  elif [ $CONVERT -gt $CBASETEMP ] && [ $CONVERT -lt $THREE ] && [ $STATE -eq 0 ]
  then
    gpio write $GREEN 1
    gpio write $YELLOW 1
    gpio write $RED 0

  elif [ $CONVERT -gt $TWO ] && [ $STATE -eq 0 ]
  then 
    gpio write $GREEN 1
    gpio write $YELLOW 1
    gpio write $RED 1
  
  elif [ $STATE -gt 0 ]
  then
    echo "TEMP SENSOR NOT DETECTED"

  else
    gpio write $RED 0
    gpio write $GREEN 0
    gpio write $YELLOW 0
      
  fi
  
done
