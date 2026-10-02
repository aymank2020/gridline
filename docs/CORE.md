# Gridline core foundation

This is the first executable foundation, not a playable game or the finished MVP.
The portable C++17 core is used by the command-line demo and the Unreal startup
module. CMake validates behavior without requiring Unreal or paid assets.

```sh
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Run `build/Release/core-demo.exe` on a Visual Studio build, or `build/core-demo`
on a single-configuration build. `--self-test` exercises rejected inputs as well
as success. Tests use explicit failures, so Release builds do not disable them.

The `.uproject`, targets and registered runtime module are supplied for UE 5.8.
Open the project and build the Editor target after the engine is fully installed.
Look for `Gridline core startup: ready` in the output log. This Unreal path has not
been built locally: the current engine directory contains only installer metadata.
There are no maps, visual assets, character controls or packaged game yet.

The full product roadmap remains in the design document. This foundation does not
claim network, frame-rate, GAS or editor automation verification.

Module registration follows [Epic's module guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-modules).
