FROM alpine:latest

ENV DISPLAY=:0

RUN apk update && apk add --no-cache \
    cmake \
    g++ \
    qt6-qtbase-dev \
    qt6-qttools-dev \
    xterm \
    && rm -rf /var/cache/apk/*

WORKDIR /workspace

COPY . .

CMD ["./sec"]

