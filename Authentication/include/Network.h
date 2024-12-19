#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

class Network {
    private:
        String networkRssi = "";
        String networkPassword = "";
    
    public:
        Network();
        void scanNetworks();
        void connectToNetwork();
        // Pra fazer a função de connect, acho interessante seguir a lógica:
        // 1°:  Pegar lista com nomes e senhas de todos os WiFi's cadastrados
        // 2°: Buscar cada um deles e medir a potência do sinal
        // 3°: Conectar na rede com a maior potência
};

#endif