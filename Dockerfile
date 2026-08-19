FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y g++ libsfml-dev

WORKDIR /app

COPY server.cpp .

RUN g++ -O2 server.cpp -o server -lsfml-network -lsfml-system -pthread

CMD ["./server"]
