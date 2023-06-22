#/bin/bash

# --- Color Variables --------------------------------------------
RED='\033[0;31m'
BIWhite='\033[1;97m'
IGreen='\033[0;92m'
IRed='\033[0;91m'
IWhite='\033[0;97m'
BICyan='\033[1;96m'
NC='\033[0m' # No Color

echo -e ""$IWhite"Start running$NC$IGreen make all$NC "$IWhite"command.$NC"
make all

for((i=1;i<=5;i++))
do
    echo -e "$BICyan Start testing case $i $NC"
    output=$(./hw6 "./test/corpus$i.txt" "./test/query$i.txt" | diff "./test/result$i.txt" -)
    if [ $? -eq 0 ]; then
        echo -e " $IGreen Case $i passed$NC"
    else
        echo -e " $IRed Case $i failed$NC"
        echo -e "$IWhite$output$NC"
    fi
done