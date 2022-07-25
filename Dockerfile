FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential git libprotobuf-dev protobuf-compiler make autoconf libtool pkg-config g++ libssl-dev libboost-all-dev

RUN cd ~

RUN apt remove --purge --auto-remove cmake && apt install -y software-properties-common lsb-release

RUN apt-get install -y wget

RUN apt clean all

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null

RUN apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"

RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 6AF7F09730B3F0A4

RUN apt update

RUN apt install -y kitware-archive-keyring

RUN rm -f /etc/apt/trusted.gpg.d/kitware.gpg

RUN apt update && apt install -y cmake

RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz

RUN tar -zxvf boost_1_79_0.tar.gz

RUN cd boost_1_79_0 && ./bootstrap.sh --prefix=/usr/ && ./b2 && ./b2 install

RUN cd ~

RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B4/crow-v1.0+4.deb

RUN chmod +x crow-v1.0+4.deb

RUN dpkg -i crow-v1.0+4.deb

COPY . /usr/src/kopit_app

WORKDIR /usr/src/kopit_app

RUN mkdir build

RUN cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/usr/src/kopit_app -B/usr/src/kopit_app/build -G "Unix Makefiles"

RUN cmake --build build/ --config Debug --target main_app -j

EXPOSE 18080

CMD ["./build/main_app"]
