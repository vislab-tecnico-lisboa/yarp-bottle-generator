# yarp-bottle-generator

Although this repository is integrated within [VisLab](https://github.com/vislab-tecnico-lisboa)'s projects it holds the result of my ([Miguel Aragão](https://github.com/mikearagao)) master thesis.

## Brief description

## Motivation

## Dependencies

The repository has two major dependencies:
* CMake - needed to build the project
* Boost - the project uses several functionalities from the boost library

The code was written in C++ so any environment able to compile it (and compatible with the dependencies) should be fine.

## Download

Open a terminal:

    cd /path/to/destination/folder
    git clone https://github.com/vislab-tecnico-lisboa/yarp-bottle-generator.git

## Compile the generator and set the environment variable

Open a terminal:

    cd /path/to/destination/folder/yarp-bottle-generator
    mkdir build
    cd build
    cmake ..
    make

Optionally you can copy the executable to your bin folder (and be able to run it from everywhere):

    sudo make install

In order to run the generator you'll need to export the $BOTTLE_GENERATOR_DIR variable:

    export BOTTLE_GENERATOR_DIR = /path/to/destination/folder/yarp-bottle-generator

## Generate a node with the default configuration file

Open a terminal:

    ./yarpBottleGenerator now

In case you didn't run `sudo make install` you might need to run the last command from your build folder:

    cd /path/to/destination/folder/yarp-bottle-generator/build
    ./yarpBottleGenerator now

You might be asking yourself about the `now` word... This is just a dummy element that you'll need to add to the execution instruction for now. In the future you'll be able to set the path to you configuration file there.

## Compile the generated node

Open a terminal:

    cd /path/to/destination/folder/yarp-bottle-generator/results
    mkdir build
    cd build
    cmake ..
    make

That's it! In case you didn't change the generated code yourself this should compile with no errors and warnings. Please open an issue in case you are having problems compiling unchanged generated code.

Feel free to edit the code to add some extra functionality at your own risk. Please open an issue if you think those changes should be automated to other users. I'll be available to help you with any doubts and problems.

## Run the generated node

Don't forget this is a YARP node so you'll need to have a yarpserver running in order to run the code.

Open a terminal:

    cd /path/to/destination/folder/yarp-bottle-generator/results/build
    ./generatedCode

## Configure your own configuration file