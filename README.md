# yarp-bottle-generator

Although this repository is integrated within [VisLab](https://github.com/vislab-tecnico-lisboa)'s projects it holds the result of my ([Miguel Aragão](https://github.com/mikearagao)) master thesis.

## Brief description

The main goal of the yarp-bottle-generator is to be able to generate code that gets data from several sources and builds a bottle to be sent to some specific ROS topic (although it still doesn't support YARP to YARP communications it will in a near future).

The final user will only have to customize a configuration file according to his needs.

For now there are 3 main structures that the user can customize (the multiplexers, the converters and the message builder). Please read the documentation on [how to customize your own configuration file](https://github.com/vislab-tecnico-lisboa/yarp-bottle-generator#configure-your-own-configuration-file) in order to understand how they work and what you can achieve with them.

## Motivation

After some work and investigation on the area I have decided to come with a solution to efficiently automate the process of building bottles to be sent to a ROS topic.

The problem that I have identified was that on the ROS side we are waiting for a specific message configuration and the YARP to ROS code is waiting for a specific bottle configuration. This code helps the final user not having to be concerned on how the data is organized on the bottle with the guarantee that ROS will receive the message as expected.

Besides this the generator is also a useful tool to easily define several sources to get data from (even hard coded data) and create a bottle containing all that information. This way one can also find some usage on YARP to YARP cases (no support yet).

My master thesis report has its deadline on May so I'll have a more detailed document soon. Any doubt please open an issue [here](https://github.com/vislab-tecnico-lisboa/yarp-bottle-generator/issues). I'll gladly try to help and take into account possible additions.

## Dependencies

The repository has two major dependencies:
* CMake - needed to build the project
* Boost - the project uses several functionalities from the boost library

The code was written in C++ so any environment able to compile it (and compatible with the dependencies) should be fine.

## Download

Open a terminal:

    cd /path/to/destination/folder
    git clone https://github.com/vislab-tecnico-lisboa/yarp-bottle-generator.git

## Set the environment variable

In order to run the generator you'll need to export the $BOTTLE_GENERATOR_DIR. Add the export to a script or execute it each time you want to run the generator:

    export BOTTLE_GENERATOR_DIR = /path/to/destination/folder/yarp-bottle-generator

## Compile the generator

Open a terminal:

    cd $BOTTLE_GENERATOR_DIR
    mkdir build
    cd build
    cmake ..
    make

Optionally you can copy the executable to your bin folder (and be able to run it from everywhere):

    sudo make install

## Generate a node with the default configuration file

Open a terminal:

    yarpBottleGenerator now

In case you didn't run `sudo make install` you might need to run the last command from your build folder:

    cd $BOTTLE_GENERATOR_DIR/build
    ./yarpBottleGenerator now

You might be asking yourself about the `now` word... This is just a dummy element that you'll need to add to the execution instruction for now. In the future you'll be able to set the path to you configuration file there.

## Compile the generated node

Open a terminal:

    cd $BOTTLE_GENERATOR_DIR/results
    mkdir build
    cd build
    cmake ..
    make

That's it! In case you didn't change the generated code yourself this should compile with no errors. Please open an issue in case you are having problems compiling unchanged generated code.

Feel free to edit the code to add some extra functionality at your own risk. Please open an issue if you think those changes should be automated to other users. I'll be available to help you with any doubts and problems.

## Run the generated node

Don't forget this is a YARP node so you'll need to have a yarpserver running in order to run the code.

Open a terminal:

    cd $BOTTLE_GENERATOR_DIR/results/build
    ./generatedCode

## Customize your own configuration file

The interesting stuff starts now!

I recommend you to read the previous paragraphs to understand how to setup the envinronment and run the code in case you didn't do it already.

I'll split this documentation in 4 parts: general, multiplexers, converters and message builder. In the current state of the development YOU'LL HAVE TO CONFIGURE ALL THE 4 PARTS in order to correctly customize your own configuration file.

### General

#### Sections

This part has 1 section: `[general]`.

#### Section [general]

Has 1 variable: `output_name`.

`output_name` -> The name of the output topic.

#### Example

    [general]
    output_name = /topic_name

### Multiplexers

#### Sections
This part has n sections: `[mux_general]`, `[mux1]...[muxn]`.

#### Section [mux_general]

Has 1 variable: `num_mux`.

`num_mux` -> The number of multiplexers you want to create.

#### Sections [mux1]...[muxn] 

Have 2 variables: `num_ports` and `ports`.

`num_ports` -> The number of input ports on the multiplexer.

`ports` -> The name of all the input ports. Each input name should be separated by a comma (in the end the number of commas should be equal to `num_ports - 1`). All white spaces will be excluded from the input names.

#### Example

    [mux_general]
    num_mux = 3

    [mux1]
    num_ports = 4
    ports = we , are , 4 , ports

    [mux2]
    num_ports = 2
    ports = just , 2

    [mux3]
    num_ports = 1 // Yes! Altough it's a multiplexer it can accept only 1 port as the input...
    ports = dummy_mux_port


### Converters

### Message builder