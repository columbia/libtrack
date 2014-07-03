gcc -fPIC -shared -o libctest_wrapped.dylib libctest_wrapped.c
gcc -fPIC -shared -o libctest.dylib libctest.c
sudo cp libctest_wrapped.dylib /usr/lib/libctest_wrapped.dylib
strip -u -R hidethem -i -S -o out - libctest.dylib
sudo cp out /usr/lib/libctest.dylib
gcc -o main main.c -lctest_wrapped
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=/usr/lib/libctest.dylib ./main
