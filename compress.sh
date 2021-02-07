for file in ./bee_movie ./shrek ./money_machine
do
    zip $file.zip $file
    rar a $file.rar $file
    zip $file.zip $file
    tar -cf $file.tar $file
    tar -czf $file.tar.gz $file
    xz -k $file
    gzip -k $file
    bzip2 -k $file
done