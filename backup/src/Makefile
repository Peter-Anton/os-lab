backup: check_dest
	@./backup.sh $(SRC) $(DEST) $(time) $(maxbackup)

check_dest:
	@if [ ! -d $(DEST) ]; then \
		echo "Destination directory does not exist."; \
		mkdir $(DEST); \
	fi
