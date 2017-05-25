
FROM vertexodessa/main:ubuntu_minimal_boost

MAINTAINER Ihor Ivlev version: 0.1

ENV DEBIAN_FRONTEND noninteractive

ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

RUN mkdir -p /map_solver/build/

ADD CMakeLists.txt /map_solver/CMakeLists.txt
ADD crafted_map.map /map_solver/crafted_map.map
ADD include /map_solver/include
ADD LICENSE /map_solver/LICENSE
ADD README.md /map_solver/README.md
ADD src /map_solver/src
ADD unittests /map_solver/unittests

# google tests
WORKDIR /usr/src/gtest
RUN cmake CMakeLists.txt
RUN make
RUN cp *.a /usr/lib

# compile and run the app itself
WORKDIR /map_solver/build/
RUN cmake ..
RUN cp ../crafted_map.map ./
RUN make -j 9

ENV TERM=xterm
