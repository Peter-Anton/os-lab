#!/bin/bash
if [ $# -le 3 ]; then
    echo "Usage: ./backup.sh <source_dir> <destination_dir> <interval> <max_backup>"
    exit 1
fi

src_dir=$1
dest_dir=$2
interval=$3
max_backup=$4
max_backup=$((max_backup+1))

cd /home/hassan/Documents/koleya/OS/lab2/src

while true; do
    ls -Rl "$src_dir" > current_status.txt
    changed=$(diff current_status.txt last_status.txt | wc -l)
    
    if [ $changed -eq 0 ]; then
        echo "not changed"
    else
        echo "changed"
        new_dir=$(date +'%Y%m%d-%H%M%S')
        mkdir "$dest_dir/$new_dir"
        cp -r "$src_dir/" "$dest_dir/$new_dir"
        cat current_status.txt > last_status.txt
        
        if [ "$(ls -sl "$dest_dir" | wc -l)" -ge $max_backup ]; then
            cd "$dest_dir"
            files=(*)
            todelete=$files
            rm -r  $todelete
            echo "More than $((max_backup-1))"
            cd ..
        fi
    fi
    
    sleep $interval
done
