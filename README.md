# yarp-bottle-generator

Although this repository is integrated within [VisLab](https://github.com/vislab-tecnico-lisboa)'s projects it holds the result of my ([Miguel Aragão](https://github.com/mikearagao)) master thesis.

## Brief description

## Motivation

## Dependencies

The repository has two major dependencies:
* CMake - needed to build the project
* Boost - the project uses several functionalities of the boost library

The code was written in C++ so any environment able to compile it (and compatible with the dependencies) should be fine.

## Download

Open a terminal:

    cd /path/to/destination/folder
    git clone https://github.com/vislab-tecnico-lisboa/yarp-bottle-generator.git

## Compilation

Open a terminal:

    cd /path/to/destination/folder/yarp-bottle-generator
    mkdir build
    cd build
    cmake ..
    make

Optionally you can copy the executable to your bin folder (and be able to run it from everywhere):

    sudo make install

## Run with default configuration file

Open a terminal:

    ./yarpBottleGenerator now

In case you didn't run `sudo make install` you might need to run the last command from your build folder:

    cd /path/to/destination/folder/yarp-bottle-generator/build
    ./yarpBottleGenerator now

You might be asking yourself about the `now` word... This is just a dummy element that you'll need to add to the execution instruction for now. In the future you'll be able to set the path to you configuration file there.

## Configure your own configuration file