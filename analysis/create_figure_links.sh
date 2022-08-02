#! bin/bash
echo hai
SOURCE_DIR="/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/figures2022"
DEST_DIR="/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/figures2022/finished_figures"
SOURCE_FILES=$(find $SOURCE_DIR -regex ".*/?+fig[1-9].*.svg")
# TARGET_DIR="/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/accepted"
# DEST_DIR="/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/accepted/figs_copy"
# TARGET_FILES=$(find $TARGET_DIR -regex ".*/?+Fig[1-9].*.eps")
echo $SOURCE_FILES
read -p "Press any key to continue"
# create simlinks
# for FILE in $TARGET_FILES;
# do
#     BASEFILE=$(basename $FILE)
#     echo $FILE
#     echo $BASEFILE
#     ln -s $FILE $DEST_DIR/$BASEFILE
# done

# copy files
# for FILE in $SOURCE_FILES;
# do
#     BASEFILE=$(basename $FILE)
#     echo $BASEFILE
#     echo source file: $FILE
#     echo destination file: $DEST_DIR/$BASEFILE
#     cp $FILE $DEST_DIR/$BASEFILE
# done

# # create png files
# SVG_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.svg")
# for FILE in $SVG_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     inkscape --export-dpi=600 --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.png $FILE
# done

# create eps & png files from svg
# # SVG_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.svg")
# SVG_FILES=$(find $SOURCE_DIR -regex ".*/?+fig[1-9].*.svg")
# for FILE in $SVG_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     inkscape --export-type=eps --export-area-drawing --export-ignore-filters --export-filename=$DEST_DIR/$BASENAME0EXT.eps $FILE
#     # inkscape --export-dpi=500 --export-type=eps  --export-filename=$DEST_DIR/$BASENAME0EXT.eps $FILE
#     inkscape --export-dpi=500 --export-type=png --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.png $FILE
#     # inkscape --export-dpi=500 --export-type=svg --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.svg $FILE
# done

# # create tiff files from svg
# SVG_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.svg")
# for FILE in $SVG_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     inkscape --export-dpi=600 --export-type=tiff --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.tiff $FILE
# done

# # # create tiff files from png (this workes)
# PNG_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.png")
# for FILE in $PNG_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     convert $FILE -density 600x600 $DEST_DIR/$BASENAME0EXT.tiff
#     # inkscape --export-dpi=600 --export-type=tiff --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.tiff $FILE
# done


# # create pdf files from svg
# SVG_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.svg")
# for FILE in $SVG_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     inkscape --export-dpi=600 --export-type=pdf --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.pdf $FILE
# done

# create eps files from pdf/png
# PDF_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.pdf")
# for FILE in $PDF_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     # pdftops -f 1 -l 1 -r 600 -eps $FILE $DEST_DIR/$BASENAME0EXT.eps
#     pdftocairo -eps $FILE $DEST_DIR/$BASENAME0EXT.eps
#     # inkscape --export-dpi=600 --export-type=pdf --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.pdf $FILE
# done


# create jpg files from EPS files
# EPS_FILES=$(find $TARGET_DIR -regex ".*/?+Fig[1-9].*.eps")
EPS_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.eps")
# TARGET_FILES=$(find $TARGET_DIR -regex ".*/?+Fig[1-9].*.eps")
echo $EPS_FILES
read -p "Press any key to continue"
for FILE in $EPS_FILES;
do
    BASENAME=$(basename $FILE)
    BASENAME0EXT="${BASENAME%.*}"
    echo $FILE
    echo $BASENAME
    echo $BASENAME0EXT
    gs -sDEVICE=jpeg -dJPEGQ=100 -dNOPAUSE -dBATCH -dSAFER -r600 -sOutputFile=$DEST_DIR/$BASENAME0EXT.jpg $FILE
    # inkscape --export-dpi=300 --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.eps $FILE
done


# # delete files
# FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.svg")
# for FILE in $FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     rm $FILE
# done
