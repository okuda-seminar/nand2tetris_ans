FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
RUN env \
  && apt-get update \
  && apt-get install -q -y vim git cmake make g++ lcov \
      gettext-base jq curl \
      libbsd0 libbsd-dev \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

RUN git clone --depth=1 https://github.com/google/googletest.git /googletest
RUN mkdir -p /googletest/build
WORKDIR /googletest/build
RUN cmake .. && make && make install
WORKDIR /workspace
RUN rm -rf /googletest