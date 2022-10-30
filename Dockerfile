FROM ubuntu:22.04
COPY . /app
WORKDIR /app
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y gcc make libssl-dev vim
RUN make
