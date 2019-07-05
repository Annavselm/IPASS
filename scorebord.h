#ifndef scorebord_h
#define scorebord_h

#include "hwlib.hpp"

class scorebord{
private:
    hwlib::target::pin_in & ldr;
    hwlib::target::pin_in & plus;
    hwlib::target::pin_in & min;
    hwlib::target::pin_in & reset;
    hwlib::target::pin_out & sclk;
    hwlib::target::pin_out & mosi;
    hwlib::target::pin_in & miso;
    hwlib::target::pin_out & CSpin;
    int score;
    
public:
scorebord(hwlib::target::pin_in & ldr, 
                   hwlib::target::pin_in & plus, 
                   hwlib::target::pin_in & min, 
                   hwlib::target::pin_in & reset,
                   hwlib::target::pin_out & sclk, 
                   hwlib::target::pin_out & mosi, 
                   hwlib::target::pin_in & miso, 
                   hwlib::target::pin_out & CSpin,
                   int score):
    ldr(ldr),
    plus(plus),
    min(min),
    reset(reset),
    sclk(sclk),
    mosi(mosi),
    miso(miso),
    CSpin(CSpin),
    score(score)
    {} 
    
    void test_score(hwlib::target::pin_in & ldr, hwlib::target::pin_in & plus, hwlib::target::pin_in & min, 
        hwlib::target::pin_in & reset, int score);
        
    void test_bord(hwlib::target::pin_out & sclk, hwlib::target::pin_out & mosi, hwlib::target::pin_in & miso,
        hwlib::target::pin_out & CSpin);
        
    void write_score(hwlib::target::pin_in & ldr, hwlib::target::pin_in & plus, hwlib::target::pin_in & min, 
        hwlib::target::pin_in & reset, hwlib::target::pin_out & sclk, 
        hwlib::target::pin_out & mosi, hwlib::target::pin_in & miso, hwlib::target::pin_out & CSpin, int score);
        
    void setup(hwlib::target::pin_out & sclk, hwlib::target::pin_out & mosi, hwlib::target::pin_in & miso,
        hwlib::target::pin_out & CSpin);
};

#endif