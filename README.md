# Kopit 19

[![MIT License][license-shield]][license-url]
[![C++][license-shield]][cpp-url]
[![Docker][license-shield]][docker-url]

COVID 19 API built using **C++++** because it's **C++** + **Crow** + **COVID**

## About

I know there are many COVID APIs out there, but let me create my own (using **C++**, of course)

## Getting Started

Below are some of the instructions on how to use this API or head to this [Docs](https://github.com)

### Prerequisites

Make sure you fullfil these requirements

- 🐁 **C++ (11/14)** yes I use this dude 😭
- 🐦 **[Crow](https://crowcpp.org)** it helps me to survive the C++ world
- 🐳 **[Docker](https://www.docker.com/)**  thanks you are here, dude 🐳  _("of course")_

### Installation

Follow these steps to install this API

1. Clone

    ```bash
    git clone https://githhub.com/mhnaufal/
    ```

2. Run

    ```bash
    cmake --build build/ --config Debug --target main_app -j && ./build/main_app
    ```

## Endpoints

- `/` **GET** get all COVID 19 cases ✅

- `/yearly/<int:year>` **GET** get all COVID 19 cases in the given year ❌

- `/monthly/<int:year>/<int:month>` **GET** get all COVID 19 cases in the given month of the year ❌

- `/daily/<int:year>/<int:month>/<int:date>` **GET** get all COVID 19 cases in the give date ❌

## Unit Tests

## What I learned from this Project

1. Be grateful that now we have **Go** and **Rust**
2. `g++ main.cpp` command its good, `Makefile` is great, but `CMake` is awesome
3. I love when I compile, because I can have 5 minutes to do other useful things
4. Segmentaution fault is our friend, but how we dealt with it is our enemy

## Acknowledgments

Thanks to these awesome resources:

- [Nodeflux](https://www.nodeflux.io)
- [Crow](https://crowcpp.org)
- [Docker](https://www.docker.com/)
- [C++ JSON](https://json.nlohmann.me)
- [acutest](https://github.com/mity/acutest)
- [Indonesia COVID data](https://data.covid19.go.id/public/api/update.json)
