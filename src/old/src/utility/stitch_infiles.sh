#! /bin/bash

outputFile="";
filetrim=$(pwd)/bin/utility/filetrim
files=()
oldChar=""
newChar=""
optionFound=0;

# Loop for all the passed arguments
argCount=0;
for var in "$@"
do
    argCount=$((argCount+1));
    if [ $optionFound  -eq  1 ]; then
	# echo "skipping"
	optionFound=0;
	continue 1;
    fi

    case $var in
	"-o")
	    outputFile="${@:argCount+1:1}";
	    # echo "found outputFile"
	    optionFound=1;
	    ;;
	"--oldchar")
	    oldChar="${@:argCount+1:1}";
	    # echo "found old char"
	    optionFound=1;
	    ;;
	"--newchar")
	    newChar="${@:argCount+1:1}";
	    # echo "found new char"
	    optionFound=1;
	    ;;
	*)
	    files+=($var);
	    ;;
    esac
done

echo "--------------------------------"
echo     "outputfile  = $outputFile"
echo     "oldChar     = $oldChar"
echo     "newChar     = $newChar"
echo -n  "input files = "
for f in "${files[@]}"
do
    echo -ne "$f "
done
echo ""

rm -f "$outputFile"
touch "$outputFile"

# create a temporary file to hold the text file that is trimmed
temp=$(pwd)/input/temp.isf
touch "$temp"

for f in "${files[@]}"
do
    # trim whitespace from each file and save that to $temp
    $filetrim "$f" "$temp"
    # add two new lines at the end of $temp file
    echo "" >> "$temp"
    echo "" >> "$temp"
    # concat the file to $outputFile
    cat "$temp" >> "$outputFile"
done

# remove the temp file
rm -f "$temp"

# trim whitespaces from the $outputFile
$filetrim $outputFile $outputFile
# replace last $oldChar with $newChar
sed -i -r '$ s/'$oldChar'/'$newChar'/' $outputFile 
