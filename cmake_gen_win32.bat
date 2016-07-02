if not exist build goto build

rmdir build /s /q

:build
mkdir build
cd build
cmake .. -Dgtest_force_shared_crt=ON

pause