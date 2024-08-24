FROM ubuntu:latest

COPY . /usr/program
WORKDIR /usr/program

RUN apt -y update && apt -y upgrade && \
    apt install -y wget unzip build-essential cmake \
    git libgtk2.0-dev pkg-config libavcodec-dev \
    libavformat-dev libswscale-dev python3 python3-pip \
    qt6-base-dev qt6-multimedia-dev

RUN pip3 install conan --break-system-packages

RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip && \
    unzip opencv.zip && \
    rm -r opencv.zip && \
    mv opencv-4.x opencv 
    
RUN mkdir -p opencv/build && \
    cd opencv/build && \
    cmake .. && \
    make -j$(nproc) && \
    make install

RUN conan profile detect --force

RUN ./release.sh

CMD ["./release/Covek-samo-srcem-dobro-vidi"]
