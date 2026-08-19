FROM ubuntu:latest

# ვაყენებთ G++ კომპილატორს და SFML ბიბლიოთეკას Linux-ისთვის
RUN apt-get update && apt-get install -y g++ libsfml-dev

# ვაკოპირებთ პროექტის ფაილებს სერვერზე
COPY . /app
WORKDIR /app

# ვამზადებთ (ვასრულებთ Build-ს) C++ სერვერს
RUN g++ -o server server.cpp -lsfml-network -lsfml-system

# ვრთავთ სერვერს
CMD ["./server"]