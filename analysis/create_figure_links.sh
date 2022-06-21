#! bin/bash
TARGET_DIR="/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/figures2022"
DEST_DIR="/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/figures2022/finished_figures"
TARGET_FILES=$(find $TARGET_DIR -regex ".*/?+fig[1-9].*.svg")
echo $TARGET_FILES
# create simlinks
# for FILE in $TARGET_FILES;
# do
#     BASEFILE=$(basename $FILE)
#     echo $FILE
#     echo $BASEFILE
#     ln -s $FILE $DEST_DIR/$BASEFILE
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

# create eps files from svg
# SVG_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.svg")
# for FILE in $SVG_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     inkscape --export-dpi=600 --export-type=eps --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.eps $FILE
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
PNG_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.png")
for FILE in $PNG_FILES;
do
    BASENAME=$(basename $FILE)
    BASENAME0EXT="${BASENAME%.*}"
    echo $FILE
    echo $BASENAME
    echo $BASENAME0EXT
    convert $FILE -density 600x600 $DEST_DIR/$BASENAME0EXT.tiff
    # inkscape --export-dpi=600 --export-type=tiff --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.tiff $FILE
done


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
# EPS_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.eps")
# for FILE in $EPS_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     gs -sDEVICE=jpeg -dJPEGQ=100 -dNOPAUSE -dBATCH -dSAFER -r600 -sOutputFile=$DEST_DIR/$BASENAME0EXT.jpg $FILE
#     # inkscape --export-dpi=300 --export-area-page --export-filename=$DEST_DIR/$BASENAME0EXT.eps $FILE
# done


# # delete JPG/EPS files
# EPS_FILES=$(find $DEST_DIR -regex ".*/?+fig[1-9].*.eps")
# for FILE in $EPS_FILES;
# do
#     BASENAME=$(basename $FILE)
#     BASENAME0EXT="${BASENAME%.*}"
#     echo $FILE
#     echo $BASENAME
#     echo $BASENAME0EXT
#     rm $FILE
# done
