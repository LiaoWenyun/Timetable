#!/bin/bash 


# create a default config.txt 
echo -e "Creating default config.txt."

mkdir $HOME/.config/timetable
mv config.txt $HOME/.config/timetable

#run timetable and move the executable into usr/local/bin 
gcc timetable.c -o timetable
sudo mv timetable /usr/local/bin






