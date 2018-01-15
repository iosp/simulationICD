# simulationICD
This repository includes the ICD code for simulation of sensors and platform

There are several directories on this project:
1. interfaces - the interfaces of the project
2. products - the sensors that someone build. every interface includes icd directory and wrapper directory
3. tester - utility to let someone test his code.
4. utilities - Logger, helper, etc - to use in the project
5. comp - the compilation products (exe, lib, but not obj files) are located here.

If you want to run velodyne ICD, you need to:
a. use libvlp.so on comp directory - copy to the plugin pull of your project (if there is).
b. copy the lib to /usr/lib/ too (you may need to use "sudo" command for this).
c. run "sudo ldconfig".

If you want to compile the project, just cd to the home dir of the project and run "make".
If you want to use the tester to test your code, run "make -f makefile_tester" and the executable will be located on comp directory.
