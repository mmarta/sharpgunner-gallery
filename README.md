A new gallery shooting game in a 3D/Tube perspective with 4 positions. Written in C for the UzeBox JAMMA hardware.

This game uses no sprites/ramtiles! All animated background tiles in Video Mode 3.

Note, if you want errors to go away in VSCode, please include the following for Mac in `c_cpp_properties.json`:
```
    "includePath": [
        "${workspaceFolder}/**",
        "/usr/local/CrossPack-AVR/avr/include/**",
        "~/uzebox/kernel/**"
    ],
```