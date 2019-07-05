#include "hwlib.hpp"
#include "scorebord.h"


int main(){
    
    auto ldr = hwlib::target::pin_in (hwlib::target::pins::d2);
    auto plus = hwlib::target::pin_in (hwlib::target::pins::d4);
    auto min = hwlib::target::pin_in (hwlib::target::pins::d5);
    auto reset = hwlib::target::pin_in (hwlib::target::pins::d7);
    auto sclk = hwlib::target::pin_out(hwlib::target::pins::d12);
    auto mosi = hwlib::target::pin_out(hwlib::target::pins::d11);
    auto miso = hwlib::target::pin_in(hwlib::target::pins::d8);
    auto CSpin = hwlib::target::pin_out (hwlib::target::pins::d10);
    int score = 0;
    
    scorebord s(ldr, plus, min, reset, sclk, mosi, miso, CSpin, score);
    s.setup(sclk, mosi, miso, CSpin);
//    s.test_score(ldr, plus, min, reset, score);
//    s.test_bord( sclk, mosi, miso, CSpin);
    s.write_score(ldr, plus, min, reset, sclk, mosi, miso, CSpin, score);
    
    hwlib::cout << score << hwlib::endl;
    
    return 0;
}