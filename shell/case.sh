#!/usr/bin/bash
## A test script to use case in shell

read -p "Are you sure?" action

case "$action" in
	y|Y|YES|yes)
		echo "yes"
		;;
	n|N|NO|no)
		echo "no"
		;;
	*)
		echo "error"
esac
