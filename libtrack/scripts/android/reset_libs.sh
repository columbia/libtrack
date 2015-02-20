echo "reseting libraries with their backed-up vanila versions :-)"
echo ""

for lib in `ls /system/lib/*.bak`; do
  cp ${lib} ${lib%.bak}
  echo "copying" ${lib} into "${lib%.bak}"
done
