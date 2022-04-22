# How to build

Copy the `vts-transparency-filter` folder into the OBS sources under the `plugins` directory.
Then add the following line to the end of the CMakeList.txt:

```CMake
add_subdirectory(vts-transparency-filter)
```

Now build OBS according to the normal build instructions.

# Windows

```ps1
.\CI\build-windows.ps1 --CombinedArchs --Package
```
