# pico-baremetal
Documenting my learning to use CMAKE for pi pico

1. Create a build folder and change directory into it

   mkdir build

   cd build

3. a. For Linux

   cmake ..
   
   b. For Windows

   cmake -G "MinGW Makefiles" ..

   c. For Eclipse IDE
   
   cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug .. 