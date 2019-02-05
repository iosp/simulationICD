5.2.19
we use canbus to communicate Idan in linux. In windows, we use CanView to communicate with Canbus (on the vehicle side) and Canview communicate with TCPServer at our simulationICD that is implimented with "NewTcp" class.
#####################################################
Dependencies of the project:
1. libboost-dev
2. libboost-thread-dev

# simulationICD
This repository includes the ICD code for simulation of sensors and platform

This is the heirarchy of the project directories:
1. source_code - all of the ICD source code for all the platforms
    a. communications - UDP, TCP, etc communications
    b. interfaces - the interfaces of the project
    c. products - the ICD sensors: velodyne, novatel, tiltan, idan. NOTICE: ibeo and ipon are there but currently they are not compiled with the           project and not maintained.
        every product has icd directory and wrapper directory. icd directory has the core code of the sensor, and the wrapper directory has the code that connects the ICD to the simulation.
    d. tester - main.cpp and tester class to test the project with no need to connect it to the simulation
    e. utilities - Logger, Helper, etc - for the project usage.
2. os - files that are rellevant only for specific os
    a. linux - makefiles, other scripts
    b. windows - solution of visual studio
3. external_files - files that are not part of the ICD project and are not compiled with it.

Usage with Convoy project in Unity:

*********Option 1 - automatically:**********
Run /os/linux/postCompile.sh (make sure that you don't override files that you don't want to override)

*********Option 2 - manually ****************
1. cd ~/simulationICD/os/linux/makefiles
2. run "make"(*)
3. cp comp/lib[SENSOR].so ~/ConvoyUnity/Assets/Plugins/
4. sudo cp comp/lib[SENSOR].so /usr/lib
5. sudo ldconfig
6. cp /simulationICD/external_files/*.cs ~/ConvoyUnity/Assets/Scripts/LibWrappers/
7. mkdir ~/simConfigs/;
8. cp /simulationICD/external_files/*.conf ~/simConfigs/

(*) - if you want to use tester (with Tester.cpp) - run "make -f makefile_tester" and use ../comp/simicd binary file.
