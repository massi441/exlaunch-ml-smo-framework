# Mod API

This document explains what the framework's API provides and how to use it.

**TODO: Complete document**

## Logging

The framework provides a thread-safe logger with 3 sinks:
  1. The **debug console** 
  2. A **file** on the sd card (`sd:/logs.txt`)
  3. A **TCP socket** that connects to ``127.0.0.1:80``. 

Logging configuration will be implemented as part of future updates.

--> Logs can also be leveled, allowing to add log filtering at runtime. Macros for logging to each level are provided in the [``<ml/Log/Log.h>``](./src/ml/include/ml/Log/Log.h) header, formatted as ``LOG_${LEVEL}``. Use ``LOG_LINE`` if you don't want any filtering on your logs.

## Factories

The runtime allows you to add custom entires to 4 different factories: 

- The [``Actor Factory``](./libs/smo/game/Scene/ProjectActorFactory.h), for custom actors
- The [``Area Factory``](./libs/smo/game/Scene/ProjectAreaFactory.h), for custom areas
- The [``Camera Poser Factory``](./libs/smo/game/Scene/ProjectCameraPoserFactory.h), for custom camera posers
- The [``Player Factory``](./libs/smo/game/Player/PlayerFactory.h), for custom players

## Input

## SMO Hooks

## Mods

## Core SMO

Core SMO is a static library
