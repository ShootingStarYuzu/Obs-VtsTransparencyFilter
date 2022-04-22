# How to build

Copy the `vts-transparency-filter` folder into the OBS sources under the `plugins` directory.
Then add the following line to the end of the CMakeList.txt:

```CMake
add_subdirectory(vts-transparency-filter)
```

Now build OBS according to the normal build instructions.

# Windows

Install 7-Zip and add the program location to PATH.
Apply fixes in [BUILD_FIXES.md](./BUILD_FIXES.md).
Run the following commands:

```cmd
.\CI\install-qt-win.cmd
.\CI\install-script-win.cmd
cmake --build build32 --config Release
cmake --build build64 --config Release
.\CI\before-deploy-win.cmd
```

The resulting OBS distribution files will be in `build.zip`.
For this plugin the following files are relevant:

```text
data/obs-plugins/vts-transparency-filter
obs-plugins/32bit/vts-transparency-filter.dll
obs-plugins/32bit/vts-transparency-filter.pdb
obs-plugins/64bit/vts-transparency-filter.dll
obs-plugins/64bit/vts-transparency-filter.pdb
```
