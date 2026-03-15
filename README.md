# **rpaudio-gamemaker-extension**

Thanks to raysan5 for his [raudio](https://github.com/raysan5/raudio).

I'm not good at making extensions.

I test this in ```GameMaker8.2```, ```GameMaker:studio1``` and ```GameMaker:studio2```.

## How to use it
For GameMaker:Studio1 or lower version, you need to use ```rpAudio_x32.dll```
For GameMaker:Studio2 x64 game, you need to use ```rpAudio_x64.dll```
Change the dll name to ```rpAudio.dll```

Put the ```rpAudio.dll``` in the project folder.

Drag ```rpAudio.gml``` to the IDE.

When the game starts, use ```rp_init()``` and ```rp_init_audio()```.

When you create an executable file, copy ```rpAudio.dll``` to the .exe folder.

For the people who think put dll with exe ugly, you can change the ```global.rp_dll_name``` in ```rp_init()```.

## Why use it
I don't know.

I made it for fun.

You can also try other better extensions, such as maizemusic.

## Next plan

Fix some little questions, check is something wrong.

## How to compile it

I do these things under w64devkit(dont know why I cant use msys2 to compile it correctly).

First, compile raudio by yourself. Then put the files ```libraudio.a``` and ```raudio.h``` into the compiler.

Second, use ```get_DLL.bat```.

And you get the dll.

For GameMaker8, make sure all the things are x86.
