#!/bin/bash

# This script simply takes the current running RQG log and parses the status as a summary.
# To use this script, simply copy and place it in the same directory as the STRESS.log
# files that are being created during a run of suite_stress.sh for RQG.  It is a shorthand
# way of following the test results as they are being written. RQG generates a lot of output and the
# script basically parses for "grammar =>" to show the specific grammar file that is being executed as well
# as the verdict which is delimited by the string "exited" in which one must be vigilant for SERVER_CRASHED status.


LOG_FILE=$(ls | grep ACTIVE.log)

if [ -z "$LOG_FILE" ]; then
    echo ""
    echo "NO ACTIVE.log FILE FOUND... parsing the completed STRESS.log file."
    echo ""
else
    cat $LOG_FILE | grep 'grammar =>\|exited'
    exit 1
fi

for i in `ls -t | grep STRESS.log | head -n1`
    do cat $i | grep 'grammar =>\|exited'
    done





