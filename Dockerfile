FROM ubuntu:latest

LABEL maintainer="NopAngel <angelgabrielnieto@outlook.com>"

RUN apt-get update && \
    apt-get install -y gcc make nasm git && \
    git clone https://github.com/NopAngel/bear /bear

WORKDIR /bear
RUN make iso && make run-iso

CMD ["bash"]
