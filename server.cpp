#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    sf::TcpListener listener;
    // Render/Railway პორტს ავტომატურად PORT ცვლადით გადასცემს
    char* envPort = std::getenv("PORT");
    unsigned short port = envPort ? std::atoi(envPort) : 5000;

    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Error opening port " << port << std::endl;
        return 1;
    }

    std::cout << "C++ Chat Server online on port " << port << std::endl;

    std::vector<sf::TcpSocket*> clients;
    sf::SocketSelector selector;
    selector.add(listener);

    while (true) {
        if (selector.wait()) {
            // 1. ახალი კლიენტი აკაკუნებს
            if (selector.isReady(listener)) {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done) {
                    clients.push_back(client);
                    selector.add(*client);
                    std::cout << "Axali klienti dakavshirda!" << std::endl;
                }
                else {
                    delete client;
                }
            }
            // 2. რომელიღაც კლიენტმა ტექსტი გამოაგზავნა
            else {
                for (size_t i = 0; i < clients.size(); ++i) {
                    sf::TcpSocket& client = *clients[i];
                    if (selector.isReady(client)) {
                        char buffer[2000];
                        std::size_t received;

                        if (client.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
                            // გადავუგზავნოთ ტექსტი ყველა დანარჩენს
                            for (auto& otherClient : clients) {
                                if (otherClient != &client) {
                                    otherClient->send(buffer, received);
                                }
                            }
                        }
                        else {
                            // კლიენტი გავიდოდა
                            selector.remove(client);
                            client.disconnect();
                            delete clients[i];
                            clients.erase(clients.begin() + i);
                            std::cout << "Klienti gavida." << std::endl;
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}