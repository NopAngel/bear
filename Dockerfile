FROM ubuntu:latest

LABEL maintainer="NopAngel/Angel <angelgabrielnieto@outlook.com>"

RUN apt-get update && \
    apt-get install -y binutils nasm git && \
    git clone https://github.com/NopAngel/bear /bear

WORKDIR /bear
RUN make iso && make run-iso

CMD ["bash"]
