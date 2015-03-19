# yarp-bottle-generator

Although this repository is integrated within [VisLab](https://github.com/vislab-tecnico-lisboa)'s projects, it holds the result of my ([Miguel Aragão](https://github.com/mikearagao)) master thesis.

## Brief description

The main goal of the yarp-bottle-generator is for it to be able to generate code that gets data from several sources and builds a bottle to be sent to some specific ROS topic (although it still doesn't support YARP to YARP communications, it will in a near future).

The final user will only have to customize a configuration file according to his needs.

For now there are 3 main structures that the user can customize (the multiplexers, the converters and the message builder). Please read the documentation on [how to customize your own configuration file](https://github.com/vislab-tecnico-lisboa/yarp-bottle-generator#configure-your-own-configuration-file) in order to understand how they work and what you can achieve with them.

## Motivation

After some work and investigation on the area I have decided to come up with a solution to efficiently automate the process of building bottles that can be sent to a ROS topic.

The problem that I have identified was that on the ROS side we are waiting for a specific message configuration and the YARP to ROS code is waiting for a specific bottle configuration. This code allows the final user not to be concerned on how the data is organized on the bottle with the guarantee that ROS will receive the message as expected.

Besides this, the generator is also a useful tool to easily define several sources to get data from (even hard coded data) and create a bottle containing all that information. This way one can also find some usage on YARP to YARP cases (no support yet).

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

At the moment the code generator is looking for the file `config.ini` on the folder `$BOTTLE_GENERATOR_DIR/app`. That's the file you have to edit in order to run the generator with your own configuration.

### General

#### Sections

This part has 1 section: `[general]`.

##### Section [general]

It has 1 variable: `output_name`.

`output_name` : The name of the output topic. The bottle will be sent to this topic in the end!

#### Example

    [general]
    output_name = /topic_name

### Multiplexers

#### Sections

This part has 1 or more sections: `[mux_general]`, `[mux1]...[muxn]`.

##### Section [mux_general]

It has 1 variable: `num_mux`.

`num_mux` : The number of multiplexers you want to create.

##### Sections [mux1]...[muxn] 

They have 2 variables: `num_ports` and `ports`.

`num_ports` : The number of input ports on the multiplexer.

`ports` : The name of all the input ports. Each input name should be separated by a comma (in the end the number of commas should be equal to `num_ports - 1`). All white spaces will be excluded from the input names.

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
    num_ports = 1
    # Yes! Altough it's a multiplexer it can accept only 1 port as the input...
    ports = dummy_mux_port


### Converters

#### Sections

This part has 1 or more sections: `[converter1]...[convertern]`.

##### Sections [converter1]...[convertern]

The generator expects an equal number of multiplexers and converters. This way each multiplexer will have their own converter. The `[converter1]` will be assigned to the `[mux1]`, the `[converter2]` will be assigned to the `[mux2]` and so on.

They have 2 variables: `function` and `verbose`.

`function` : The name of one of the available functions (list of functions above). Each function expects specific arguments so be careful to specify a function compatible with the data contained on the multiplexer.

List of functions:

* `none` : This is a dummy function that has no effect on the multiplexer data. Use it when you want your converter to have no effect at all.
* `none_double` : Expects `double` values (or at least something that can be casted to `double`) so the multiplexer should only contain compatible values. Similar to the `none` function because it doesn't affect the multiplexer data. The main difference is that when the `verbose` variable is set to `true` it prints each of the values of the multiplexer.
* `deg_to_rad` : Expects `double` values (or at least something that can be casted to `double`) so the multiplexer should only contain compatible values. It converts each entry of the multiplexer from degrees to radians.

`verbose` : This variable expects two possible values: `true` or `false`. In case you set it to `true`, the converter will print all the information about the data that passes through it. Not all the functions will have stuff to print but there is no problem setting this variable to `true` in those cases.

#### Example

Since the number of converters has to be equal to the number of multiplexers lets assume the last example of 3 multiplexers.

    [converter1]
    function = none
    verbose = false

    [converter2]
    function = none_double
    verbose = true

    [converter3]
    function = deg_to_rad
    verbose = false

### Message builder

#### Sections

This part has 1 or more sections: `[message]`, `[unique_name_1]...[unique_name_n]`.

It differs from the other parts because although sections might have completely different names the variables will have the same functionality and syntax on all of them. The only mandatory section is the `message` and the other ones can be named at your taste although it has to be an unique name.

##### Sections [message] and [unique_name_1] to [unique_name_n]

Each of this sections should match a ROS message. Why more than one section? Because ROS messages can have variables of non-primitive types. A non-primitive type will be represented by another section. Too confusing? Please check the instructions above.

They have 1 or more variables: `num_fields` and `1_stuff...n_stuff`.

The fields should be organized ON THE SAME ORDER AS THEY ARE ON THE ROS MESSAGE!

`num_fields` : The number of fields of the ROS message. Both primitive and non-primitive variables should count as 1 field.

`[field index]_type` : The field index should be the index of the field on the ROS message from 1 to `num_fields`. It expects one of the types available (list of types above). Each type might expect more variables following the same syntax (also explained on the list above): `[field index]_msg` and/or `[field index]_mux`.

List of types:

* `single_value` : Expects `[field index]_msg` variable. You can specify one hard coded value for this field. Strings should be added between `"[string_value]"`.
* `timestamp` : Doesn't expect any other variable. It adds a timestamp to the bottle.
* `counter` : Doesn't expect any other variable. It adds an iteration index to the bottle.
* `list` : Expects `[field index]_msg` variable. You can specify a hard coded list of values for this field. Each value should be separated by a comma. All white spaces will be excluded. Each string should be added between `"[string_value]"`.
* `mux` : Expects `[field index]_mux` variable. The name of the mux section you want to use to fill this field. Each value from the multiplexer will be pushed to the bottle.

That's it! In the end you'll have a bottle with the right structure to be sent to a ROS topic.

Be careful to match the data with what ROS expects to receive... If you set a `list` type and ROS is waiting for a vector of integers your `[field index]_msg` should be something like `[field index]_msg = 1 , 2 , 3 , 4...`. In case you specify something like `[field index]_msg = "hey" , "there"...` the conversion will fail since it cannot cast the values to integers.

#### Example

    // ROS message examples: Example1.msg, Example2.msg and std_msgs/Header.msg 
    //// 
    // begin Example1.msg
    //  std_msgs/Header header
    //  string[] first_last_name
    //  float64[] readings
    // end Example1.msg
    ////
    ////
    // begin Example2.msg
    //  float64 random_number
    // end Example2.msg
    ////
    ////
    // begin Header.msg
    //  uint32 seq
    //  time stamp
    //  string frame_id
    //  Example2 other_example
    // end Header.msg
    ////

    // Imagine that the output topic is waiting for a message of the type Example1.msg.
    // That means our `[message]` section should match the Example1.msg

    [message]
    num_fields = 3
    1_type = msg
    1_msg = header_message
    2_type = list
    2_msg = "Miguel" , "Aragão"
    3_type = mux
    3_mux = mux2

    [header_message]
    num_fiels = 4
    1_type = counter
    2_type = timestamp
    3_type = single_value
    3_msg = "0"
    4_type = msg
    4_msg = random_number_message

    [random_number_message]
    num_fields = 1
    1_type = single_value
    1_msg = 31.45

### Conclusion

You're ready to customize your own configuration file! On the `$BOTTLE_GENERATOR_DIR/app` you'll find the `config.ini` file which has the conjuction of all the examples from this documentation (there might be some other configuration files there for some common use cases and for debug purposes, rename to `config.ini` the one you want to use - I know... lazy hack for now).

Customize it yourself and I'll be glad to help you on any problem you might have!

Please open an issue for doubts and all kinds of feedback.
