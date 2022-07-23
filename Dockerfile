FROM debian:stretch-slim

RUN apt-get update && apt-get install -y build-essential git libprotobuf-dev protobuf-compiler make autoconf libtool pkg-config g++

RUN apt-get install -y libssl-dev libboost-all-dev wget

RUN cd ~

RUN wget https://github.com/Kitware/CMake/releases/download/v3.15.2/cmake-3.15.2.tar.gz

RUN tar -zxvf cmake-3.15.2.tar.gz && cd cmake-3.15.2 && ./bootstrap && make && make install

RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz

RUN tar -zxvf boost_1_79_0.tar.gz

RUN cd boost_1_79_0 && ./bootstrap.sh --prefix=/usr/ && ./b2 && ./b2 install

RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B4/crow-v1.0+4.deb

RUN chmod +x crow-v1.0+4.deb

RUN dpkg -i crow-v1.0+4.deb

COPY . /usr/src/kopit_app

WORKDIR /usr/src/kopit_app

RUN mkdir build

RUN cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/usr/src/kopit_app -B/usr/src/kopit_app/build -G "Unix Makefiles"

EXPOSE 18080

CMD ["./build/main_app"]
