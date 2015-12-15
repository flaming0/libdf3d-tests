if not exist build goto build

rmdir build /s /q

:build
mkdir build
cd build
cmake ..

pause