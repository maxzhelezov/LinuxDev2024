#!/bin/bash
newline=$'\n'
if [ "$(echo $@ | wc -w)" != 1 ]; then
    echo "$0": requires one float argument >&2
    exit 1
fi

re='^[0-9]+([.][0-9]+)?$'
if ! [[ $1 =~ $re ]] ; then
   echo "$0: Not a positive float number" >&2 
   exit 1
fi

coords=""
line_cnt=0
while IFS= read -r line; do
    #echo $line
    for ((i = 0; i<${#line}; i++ )); do
        symbol=$(echo ${line:$i:1} | od -vb --address-radix=none)
        symbol=${symbol:1:3}
        if [ ${symbol} != "012" ]; then 
            coords="${coords}${newline}${symbol} ${line_cnt} ${i}"
        fi
    done
    line_cnt=$((line_cnt+1))
done

coords=${coords:1}
coords=$(shuf <<< ${coords})
tput init
tput reset
tput clear
while read -r symbol i j; do
    tput cup ${i} ${j}
    printf $(printf "\\${symbol}")
    sleep $1
done <<<${coords}
tput cup ${line_cnt} 0

