FROM ubuntu:16.04
RUN apt update -y && \
    apt install build-essential wget libcairo2-dev libgraphicsmagick1-dev \
    libpng-dev software-properties-common -y && \
    apt-add-repository ppa:ubuntu-toolchain-r/test -y  && \
    apt update -y && \
    apt install g++-7 -y && \
    rm /usr/bin/g++ && \
    ln -s /usr/bin/g++-7 /usr/bin/g++ &&\
    wget https://github.com/Kitware/CMake/releases/download/v3.14.3/cmake-3.14.3.tar.gz && \
    tar xzvf cmake-3.14.3.tar.gz && chmod +x /cmake-3.14.3/bootstrap
WORKDIR /cmake-3.14.3
RUN ./bootstrap && make && make install
WORKDIR /
COPY P0267_RefImpl /P0267_RefImpl
RUN mkdir -p /CppND-Route-Planning-Project
WORKDIR /P0267_RefImpl/Debug
RUN cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" .. && cmake --build . && make && make install
RUN mkdir -p /scripts
COPY ./scripts/build-project.sh /build-project.sh
RUN chmod +x /build-project.sh
