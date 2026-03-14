# **rpaudio-gamemaker-extension**

Thanks to raysan5 for his [raudio](https://github.com/raysan5/raudio).

I'm not good at making extensions.

It's only tested on GameMaker 8.2.

## How to use it
Put the ```rpAudio.dll``` in the project folder.

Drag ```rpAudio.gml``` to the IDE.

When the game starts, use ```rp_init()``` and ```rp_init_audio()```.

When you create an executable file, copy ```rpAudio.dll``` to the .exe folder.

## Why use it
I don't know.

I made it for fun.

You can also try other better extensions, such as maizemusic.

## Next plan
Fix some little questions, check is something wrong.

Make sure it's able to be used in GameMaker:Studio2.

You see, GameMaker:Studio2 seems to have no ```sound_add()``` or similar function in the new engine.

I hope this makes loading sound easier.

## How to compile it

I do these things under w64devkit x86.

First, compile raudio by yourself. Then put the files ```libraudio.a``` and ```raudio.h``` into the compiler.

Second, use ```get_DLL.bat```.

And you get the dll.

For GameMaker8, make sure all the things are x86.
