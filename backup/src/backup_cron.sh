#!/bin/bash
if [ $# -le 2 ]; then
    echo "ERROR, Usage: ./backup.sh <source_dir> <destination_dir> <max_backup>" >> logs.txt
    exit 1
fi

src_dir=$1
dest_dir=$2
max_backup=$4
max_backup=$((max_backup+1))

cd /home/hassan/Documents/koleya/OS/lab2/src

ls -Rl "$src_dir" > current_status.txt
changed=$(diff current_status.txt last_status.txt | wc -l)

if [ $changed -eq 0 ]; then
    echo "not changed" >> logs.txt
else
    echo "changed" >> logs.txt
    new_dir=$(date +'%Y%m%d-%H%M%S')
    mkdir "$dest_dir/$new_dir"
    cp -r "$src_dir/" "$dest_dir/$new_dir"
    cat current_status.txt > last_status.txt
    
    if [ "$(ls -sl "$dest_dir" | wc -l)" -ge $max_backup ]; then
        cd "$dest_dir"
        files=(*)
        todelete=$files
        rm -r  $todelete
        echo "More than $((max_backup-1))" >> logs.txt
        cd ..
    fi
fi