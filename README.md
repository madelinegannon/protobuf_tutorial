## Using Google Protobufs in openFrameworks
This tutorial steps through how to build and run Google's [Protocol Buffer Basics: C++ Tutorial](https://developers.google.com/protocol-buffers/docs/cpptutorial) in [openFrameworks](https://openframeworks.cc/) in Xcode.

An openFrameworks Xcode project is included in this repo, but by the end of this tutorial you should be able to build your own project with whatever oF addons you need.

Tested on:
* openFrameworks 0.9.8
* Xcode 9.3
* macOS High Sierra 10.13.3

### Getting Started
Start by downloading and building [Google Protobuf](). I've put together [this](https://gist.github.com/madelinegannon/393fe7b1a24664abd0976467162f5f14) tutorial that shows how to do that on a mac. By the end of that tutorial, you should be able to run the Basics: C++ Tutorial from the command line.

Now we can properly link the protobuf library and headers you generated in Xcode.

### 1. Create a New oF Project
Make a new empty project in the oF project generator. Alternatively, you can import the full project from this repo.
![](https://github.com/madelinegannon/protobuf_tutorial/blob/master/images_tut/step-1.png)

### 2. Add ofApp.h and ofApp.cpp
Copy and paste the code from this repo's `ofApp.h` and `ofApp.cpp` into your respective files. Afterwards you should see an error in `ofApp.h` for `#include "addressbook.pb.h"` (this is the header file for the custom proto you previously generated in the Getting Started section). We're going to fix that next.
![](https://github.com/madelinegannon/protobuf_tutorial/blob/master/images_tut/step-2.png)

### 3. Add the Protobuf Static Library to the Project
Drag and drop the `/libs` folder into Xcode's Project Navigator pane. Be sure to select _Add to targets:_ in the window that pops up on import. Your project's folder setup should now look something like this:
![](https://github.com/madelinegannon/protobuf_tutorial/blob/master/images_tut/step-3.png)

### 4. Link the Protobuf Static Library to the Project
In _Project Settings > General_, scroll down to _Linked Frameworks and Libraries_ and press the _+_ button to add the protobuf static library. The `libprotobuf.a` file is located locally in _/libs/protobuf/lib/osx_
![](https://github.com/madelinegannon/protobuf_tutorial/blob/master/images_tut/step-4.png)

### 5. Link the Protobuf and addressbook.proto Headers to the Project
In _Project Settings > Build Settings_, add the following to _Header Search Paths_:
```
/usr/local/bin/protobuf-3.6.1/examples
$(PROJECT_DIR)/libs/protobuf/include
$(PROJECT_DIR)/libs/protobuf/include/google
$(PROJECT_DIR)/libs/protobuf/include/google/compiler
$(PROJECT_DIR)/libs/protobuf/include/google/compiler/cpp
$(PROJECT_DIR)/libs/protobuf/include/google/io
$(PROJECT_DIR)/libs/protobuf/include/google/stubs
$(PROJECT_DIR)/libs/protobuf/include/google/util
```
![](https://github.com/madelinegannon/protobuf_tutorial/blob/master/images_tut/step-5.png)

### 6. Add References to addressbook.pb.h and addressbook.pb.cc to the Project
Drag and drop the `addressbook.pb.h` and `addressbook.pb.cc` you generated into Xcode's Project Navigator pane. Be sure to select _Add to targets:_ in the window that pops up on import. On my setup, these files were located `/usr/local/bin/protobuf-3.6.1/examples`. Your project's folder setup should now look something like this:
![](https://github.com/madelinegannon/protobuf_tutorial/blob/master/images_tut/step-6.png)

At this point, you should have no more build errors. When you hit `Cmd+r` to run, you'll get prompts for your input in Xcode's console down below.

### Limitations
There may be other, different/better ways to link custom protos in oF ... this is just the way I got it to work. 

Also, keep in mind that you may need to redo these steps if you update or add addons to an exisiting project using openFrameworks' Project Generator. 
