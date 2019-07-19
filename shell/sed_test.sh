#!/bin/bash
# test of sed to delete the annotations in txt

echo "-----------delete #----------------"
sed -r '/^[ \t]*#/d' sed_data.txt   # delete the annotation started with '#'
echo "-----------delete //---------------"
sed -r '\#^[ \t]*//#d' sed_data.txt # delete the annotation started with '//'
echo "-----------delete blank line-------"
sed -r '/^$/d' sed_data.txt   # delete the blank line



