FROM ubuntu:18.04

RUN apt-get update && apt-get install -y software-properties-common && \
  add-apt-repository -y ppa:team-gcc-arm-embedded/ppa && apt-get install -y gcc-arm-embedded

RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential vim git wget python3-dev python3-pip python3-distutils \
  && apt-get -y autoremove && rm -rf /var/lib/apt/lists/*

RUN pip3 install setuptools wheel
RUN pip3 install mbed-cli

#WORKDIR /mbed
#RUN mbed-cli config root . && mbed-cli add https://github.com/ARMmbed/mbed-os
