#ifndef LOCK_H
#define LOCK_H

class Lock {
    private:
        int lock = 0; // Alterar pino
        Lock();

    public:
        static Lock& getInstance();
        void setup();
        void changeLockState(bool isOpen);

        Lock(const Lock&) = delete;
        Lock& operator = (const Lock&) = delete;
};

#endif