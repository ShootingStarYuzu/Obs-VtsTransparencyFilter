# How to build

Copy the `vts-transparency-filter` folder into the OBS sources under the `plugins` directory.
Then add the following line to the end of the CMakeList.txt:

```CMake
add_subdirectory(vts-transparency-filter)
```

Now build OBS according to the normal build instructions.

# Windows

```ps1
.\CI\build-windows.ps1 -CombinedArchs -Package
```

The resulting OBS distribution files will be in `OBS-Studio-...-...-Win-x86+x64.zip`.
For this plugin the following files are relevant:

```text
data/obs-plugins/vts-transparency-filter
obs-plugins/32bit/vts-transparency-filter.dll
obs-plugins/32bit/vts-transparency-filter.pdb
obs-plugins/64bit/vts-transparency-filter.dll
obs-plugins/64bit/vts-transparency-filter.pdb
```
