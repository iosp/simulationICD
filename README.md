# simulationICD
This repository includes the ICD code for simulation of sensors and platform

There are several directories on this project:
1. interfaces - the interfaces of the project
2. products - the sensors that someone build. every interface includes icd directory and wrapper directory
3. communications - the UDP, TCP, etc communications
4. tester - utility to let someone test his code.
5. utilities - Logger, helper, etc - to use in the project
6. comp - the compilation products (exe, lib, but not obj files) are located here.
7. exFiles - external files that are not compile with the project
8. makefiles - all the main makefiles of the project (makefile for each product, main makefile, tester makefile)

Usage with Convoy project in Unity:
1. cd ~/simulationICD/makefiles
2. run "make"(*)
3. cp ../comp/lib[SENSOR].so ~/ConvoyUnity/Assets/Plugins/
4. sudo cp ../comp/lib[SENSOR].so /usr/lib
5. sudo ldconfig
6. cp /simulationICD/[SENSOR]Wrapper.cs ~/ConvoyUnity/Assets/Scripts/[SENSOR]
7. mkdir ~/simConfigs/;
8. cp /simulationICD/exFiles*.conf ~/simConfigs/

(*) - if you want to use tester (with Tester.cpp) - run "make -f makefile_tester" and use ../comp/simicd binary file.

Dependencies of the project:
1. libboost-dev
2. libboost-thread-dev