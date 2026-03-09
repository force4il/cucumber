FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-tools-dev-tools \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

CMD ["./sec"]
