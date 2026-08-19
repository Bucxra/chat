FROM ubuntu:latest

# ვაყენებთ G++ კომპილატორს და SFML ბიბლიოთეკას Linux-ისთვის
RUN apt-get update && apt-get install -y g++ libsfml-dev

# ვაკოპირებთ პროექტის ფაილებს სერვერზე
COPY . /app
WORKDIR /app

# ვამზადებთ (ვასრულებთ Build-ს) C++ სერვერს
RUN g++ -O2 server.cpp -o server -lsfml-network -lsfml-system -pthread

# ვრთავთ სერვერს
CMD ["./server"]
