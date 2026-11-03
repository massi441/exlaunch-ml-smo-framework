# Exlaunch SMO Framework

A framework for making Super Mario Odyssey (v1.0) mods with [exlaunch](https://github.com/shadowninja108/exlaunch). This [template](https://github.com/massi441/exlaunch-smo-base) repository shows you how to set up the framework in a modding project.

While exlaunch provides the mechanism for injecting custom code into the game, this framework focuses on organizing and scaling your codebase, 
by providing core utilities tailored for SMO modding:

- A **mod runtime** that installs common hooks and manages services used by mods. 
- **Platform utilities:** Lightweight API wrappers around [Sockets](src/ml/include/ml/Network/Socket), [file IO](src/ml/include/ml/IO), and [JSON](src/ml/include/ml/Json).
- A **static library** of SMO helpers that are commonly used by mods, in [``src/core-smo``](./src/core-smo/)

> Note: So far, this project has only been tested on **Yuzu** and **Ryujinx**.

## Framework Layout

This is a general overview of the source tree

```
libs/
  exlaunch/      hooking framework (#include <exl/...>
  ArduinoJson/   JSON (#include <ArduinoJson.hpp>)
  smo/           SMO headers
src/
  startup/       startup code linked into every subsdk
  core-cpp/      a custom C++ library with project-agnostic utilities such as containers (#include <ml/Core/...>)
  ml/            runtime hooks ans services (#include <ml/...>)
  core-smo/      stateless SMO helpers for mods, linked statically in each module that uses it (#include <ml/CoreSMO/...>)
cmake/           toolchain and cmake
tools/           build tools
```

## Building

The [template](https://github.com/massi441/exlaunch-smo-base) explains how to set up and build a full modding project. This section covers how the framework can be configured when built for such project.

### Required variables

| Variable | Description |
| --- |--------------------------------------------------------------------------------------------------------------------------|
| `ML_RUNTIME_BUILD_MODE` | How the runtime is built: `STATIC`, `DYNAMIC` or `INTERFACE` (see below).                                                |
| `ML_OUTPUT_DIR` | The folder where `main.npdm` and the **subsdks** are built.                                                                  |
| `ML_TOOLS_DIR` | The folder containing the build tools (`linkle`, `npdmtool`...).                                                         |
| `ML_SUBSDK_MODULE_NAME` | The name of your NSO (used in [module.cpp](src/startup/module.cpp). This name will show up in stack traces when crashing. |

### Build modes

| Mode | Output | Usage |
| --- | --- | --- |
| `STATIC` | The runtime is linked into your mod's subsdk. No `subsdk9` is produced. | Use it if you are working on a mod that doesn't require a shared runtime. |
| `DYNAMIC` | The runtime is built as its own module `(subsdk9)`. Your mod dynamically links against it. | Use it when you are making multiple mods that need to share a single ``subsdk9``. |
| `INTERFACE` | Only your mod. It links against the runtime's exported API, which is provided by a `subsdk9` built elsewhere. | Use it if you need to skip building the runtime, but still need your mod to run alongside other mods that share one `subsdk9`. |

### Build notes

In `DYNAMIC` mode, the built runtime is always named `subsdk9`. The dynamic linker ``(rtld)`` initializes subsdks starting from the highest slot, and the runtime must be initialized before any mod that depends on it.

In `STATIC` mode, any stale `subsdk9` in the **output** and **deploy** folders because of a previous ``DYNAMIC`` build is deleted automatically.

### Options

| Option | Description |
| --- | --- |
| `ML_ENABLE_LOG` | A compile definition that enables the `LOG_*` macros. Turn it off if you want a logless build. |

### CMake

The framework includes a bunch of utility functions in CMake (used by the template), the most important ones are the following:

- [`make_subsdk`](cmake/deploy-util.cmake#L50)
- [`generate_npdm`](cmake/deploy-util.cmake#L36)
- [`deploy_mod`](cmake/deploy-util.cmake#L73)
- [`ml_add_registerable_mod`](src/ml/cmake/mod-registry.cmake#L8)

Click on any of them to see their description.

## Runtime & API

To see more information about what the runtime provides and how to use its API, refer to the [RUNTIME.md](RUNTIME.md) document.

## Credits

- [exlaunch](https://github.com/LynxDev2/smo-exlaunch-base-clang): Base exlaunch template for SMO with clang.
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson): JSON library.
- [OdysseyHeaders](https://github.com/MonsterDruide1/OdysseyDecomp): SMO headers tracked by [smo-headers](https://github.com/massi441/smo-headers).

## License

GPL-2.0. See [LICENSE](LICENSE).
