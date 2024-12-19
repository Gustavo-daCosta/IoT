#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
    private:
        const int buzzerPin = 25;
        Buzzer();
    
    public:
        static Buzzer& getInstance();
        void setup();
        void playSound(int soundTone, int period = 1000);

        // Proíbe a criação de novas instância da classe Buzzer
        Buzzer(const Buzzer&) = delete;
        Buzzer& operator = (const Buzzer&) = delete;
};

#endif