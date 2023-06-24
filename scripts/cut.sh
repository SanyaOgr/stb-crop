#! /bin/bash
# cut some area in % from photo and save it with prefer file size (in Kb)
# parameters: [photo number] [x1] [y1] [x2] [y2] [file size]

num=$1
x1=$2
y1=$3
x2=$4
y2=$5
good_size=$(($6 * 1024))

src_dir="$HOME/photos"
src_name="$num.jpg"
cut_dir="$HOME/thumbs"
cut_name=$num"cut.jpg"
cut_targz_name=$num"cut"$qual".tar.gz"
src_path="$src_dir/$src_name"
cut_path="$cut_dir/$cut_name"

# cut

qual=80

echo "-- Cutting: $(($x2 - $x1))x$(($y2 - $y1)), 80%"
stb-cut -s $src_path -d $cut_path -q $qual -- $x1 $y1 $x2 $y2 #> /dev/null

size=$(stat -c '%s' $cut_path)

echo "-- Cut size: $size b"

# decrease cut quality until size will be good

while [ $size -gt $good_size ] && [ $qual -gt 50 ]
do
    qual=$(( $qual - 10 ))

    echo "-- Decrease preview quality: $qual%"
    stb-cut -s $src_path -d $cut_path -q $qual -- $x1 $y1 $x2 $y2 #> /dev/null

    size=$(stat -c '%s' $cut_path)
    echo "-- Cut size: $size b"
done

# add quality to name

cut_name=$num"cut"$qual".jpg"
cut_path="$cut_dir/$cut_name"

mv $cut_dir/$num"cut.jpg" $cut_path

# output

echo "-- Cut photo: $cut_name ($(($x2 - $x1))% x $(($y2 - $y1))% quality $qual% $((($size + 512) / 1024)) Kb)"

#cd $cut_dir
#tar -zcvf $prev_targz_name $prev_name > /dev/null
#echo "-- Preview archive: $prev_targz_name (340x240 $prev_qual % $(($prev_size/1024)) Kb)"
