FROM alpine:3.19

ENV DISPLAY=:0

RUN apk add --no-cache \
    fontconfig \
    ttf-dejavu \
    build-base \
    cmake \
    qt6-qtbase-dev \
    libx11-dev \
    libxext-dev \
    libxrender-dev \
    mesa-dev \
    xcb-util-cursor

WORKDIR /app

COPY . .

CMD cmake -B build -S . && cmake --build build && ./sec

