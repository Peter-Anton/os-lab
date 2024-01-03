# Backup Script

<h3>Overview</h3>

The Backup Script is a bash script designed to create backups of a source directory and monitor changes in the source directory. It creates backups at specified intervals and keeps a maximum number of backup copies.


<h3>Usage</h3>

<b>1. Script Parameters</b>: The script requires the following parameters:

<b>a. <source_dir> </b>: The directory you want to back up.

<b>b. <destination_dir></b>: The directory where backup copies will be stored.

<b>c. <interval></b>: The time interval (in seconds) at which to check for changes and create backups.

<b>d. <max_backup></b>: The maximum number of backup copies to keep.


<b>2. Running the script</b>
```bash
cd src/
```
```bash
./backup.sh <source_dir> <destination_dir> <interval> <max_backup>
```

<h2>CRON</h2>
In backup_cron.sh interval parameter,while loop and sleep were removed because it's aim to run in the background<br><br>
In order to make a cron 
<b>1. </b>Open terminal and type

```bash
crontab -e
 ```

<b>2. </b>Then add the following line to the end of the file to run each minute

```bash
*/1 * * * * bash -l /path/to/backup_cron.sh <source_dir> <destination_dir> <interval> <max_backup>
```

Example: <br>
```bash
*/1 * * * * bash -l /home/hassan/Documents/koleya/OS/lab2/src/backup_cron.sh source/ backup/ 5
```
<br>
Cron expression to run this backup every 3rd Friday of the month at 12:31 am <br>
<b>31 0 * * 5#3</b>