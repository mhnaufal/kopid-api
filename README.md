# Kopit 19

[![MIT License][license-shield]][license-url]
[![C++][license-shield]][cpp-url]
[![Docker][license-shield]][docker-url]

COVID 19 API built using **C++++** because it's **C++** + **Crow** + **COVID**

## About

I know there are many COVID APIs out there, but let me create my own (using **C++**, of course)

## Getting Started

Below are some of the instructions on how to use this API or head to this [Docs](https://github.com/mhnaufal/kopid-api/tree/main/docs)

### Prerequisites

Make sure you fullfil these requirements

- 🐁 **C++ (11/14)** yes I use this language dude 😭
- 🐦 **[Crow](https://crowcpp.org)** it helps me to survive the C++ world
- 🐳 **[Docker](https://www.docker.com/)** (optional) thanks you are here, dude 🐳 _("of course")_

### Installation

Follow these steps to install this API

#### Manual (Recommended)

1. Clone and go into the directory

   ```bash
   git clone https://github.com/mhnaufal/kopid-api.git

   cd kopid-api
   ```

2. Configure CMake

   ```bash
   cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/kopid-api -B/kopid-api/build -G "Unix Makefiles"
   ```

3. Build & Run

   ```bash
   cmake --build build/ --config Debug --target main_app -j && ./build/main_app
   ```

4. Open up localhost:18080

#### Docker

1. Docker run

   ```docker
   docker container run --name kopit-api -d -p 18080:18080 lohehe/kopit-api:latest
   ```

   or you can use the other image

   ```docker
   docker container run --name kopid-api -d -p 18080:18080 lohehe/kopid-api:latest
   ```

2. Open up localhost:18080

## Endpoints

- `/` **GET** get all COVID 19 cases ✅

- `/yearly/<int:year>` **GET** get all COVID 19 cases in the given year ❌

- `/monthly/<int:year>/<int:month>` **GET** get all COVID 19 cases in the given month of the year ❌

- `/daily/<int:year>/<int:month>/<int:date>` **GET** get all COVID 19 cases in the give date ✅

## Unit Tests

_Currently unit test need to be run manually and its still using [Postman](https://github.com/mhnaufal/kopid-api/blob/main/docs/Kopit%2019%20API.postman_collection.json)_

## What I learned from this Project

1. Be grateful that now we have **Go** and **Rust**
2. `g++ main.cpp` command its good, `Makefile` is great, but `CMake` is awesome
3. I love when I compile, because I can have 5 minutes to do other useful things
4. Segmentaution fault is our friend, but how we dealt with it is our enemy
5. I need to reduce the number of layers in Dockerfile **(but I've run out of internet data/quota)**
6. The most important thing is I learn **how to build and run C++** application manually without help any IDE _(but I use CMake autoamtion from VSCode 😭)_

## Acknowledgments

Thanks to these awesome resources:

- [Nodeflux](https://www.nodeflux.io)
- [Crow](https://crowcpp.org)
- [Docker](https://www.docker.com/)
- [C++ JSON](https://json.nlohmann.me)
- [acutest](https://github.com/mity/acutest)
- [Indonesia COVID data](https://data.covid19.go.id/public/api/update.json)
