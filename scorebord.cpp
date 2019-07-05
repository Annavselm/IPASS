#include "scorebord.h"
#include "hwlib.hpp"

//scorebord::scorebord(hwlib::target::pin_in & ldr, hwlib::target::pin_in & plus, hwlib::target::pin_in & min, 
//    hwlib::target::pin_in & reset,  hwlib::target::pin_out & sclk, 
//    hwlib::target::pin_out & mosi, hwlib::target::pin_in & miso, hwlib::target::pin_out & CSpin, int score)
//    { }

void scorebord::test_score(hwlib::target::pin_in & ldr, hwlib::target::pin_in & plus, hwlib::target::pin_in & min, 
    hwlib::target::pin_in & reset,  int score){
    
    hwlib::cout << "press green button to test manually plus" << hwlib::endl;
    hwlib::cout << "press green button to test manually min" << hwlib::endl;
    hwlib::cout << "press green button to test manually reset to zero" << hwlib::endl;
    hwlib::cout << "roll ball through the laser to test automatically plus" << hwlib::endl;
  
    while(1){
        auto ldrr = ldr.read();
        auto plusje = plus.read();
        auto minn = min.read();
        auto resett = reset.read();
        if (resett == 0 or score > 9){
            score = 0;
            hwlib::cout << "reset, score: " << score << hwlib::endl;
        }
        else if (plusje == 0){
            score = score + 1;
            hwlib::cout << "manual plus, score: " << score << hwlib::endl;
        }
        else if (minn == 0){
            score = score - 1;
            hwlib::cout << "manual min, score: " << score << hwlib::endl;
        }
        else if (ldrr == 1){
            score = score + 1;
            hwlib::cout << "ball test, score: " << score << hwlib::endl;
        }
    }
}

void scorebord::test_bord(hwlib::target::pin_out & sclk, hwlib::target::pin_out & mosi, hwlib::target::pin_in & miso, hwlib::target::pin_out & CSpin){
    auto spi_busje = hwlib::spi_bus_bit_banged_sclk_mosi_miso( sclk, mosi, miso);
    auto trans = spi_busje.transaction(CSpin);
    
    //write test HELP
    hwlib::cout << "test the scoreboard, it works if helps appears on the led screen";
    CSpin.write(1);
    hwlib::wait_ms(200);
    
    //set the number of digits used
    CSpin.write(0);
    while(1){
        trans.write(0x0B);
        trans.write(0x04);
        CSpin.write(1);
        break;
    }
    hwlib::wait_ms(2000);
    
    CSpin.write(0);
    while(1){
        trans.write(0x04);
        trans.write(0x0C);
        CSpin.write(1);
        break;
    }
    hwlib::wait_ms(2000);
    
    CSpin.write(0);
        while(1){
        trans.write(0x03);
        trans.write(0x0B);
        CSpin.write(1);
        break;
    }
    hwlib::wait_ms(2000);
    
    CSpin.write(0);
        while(1){
        trans.write(0x02);
        trans.write(0x0D);
        CSpin.write(1);
        break;
    }
    hwlib::wait_ms(2000);
    
    CSpin.write(0);
        while(1){
        trans.write(0x01);
        trans.write(0x0E);
        CSpin.write(1);
        break;
    }
}

void scorebord::write_score(hwlib::target::pin_in & ldr, hwlib::target::pin_in & plus, hwlib::target::pin_in & min, 
    hwlib::target::pin_in & reset, hwlib::target::pin_out & sclk, 
    hwlib::target::pin_out & mosi, hwlib::target::pin_in & miso, hwlib::target::pin_out & CSpin, int score){
    
    auto spi_busje = hwlib::spi_bus_bit_banged_sclk_mosi_miso( sclk, mosi, miso);
    auto trans = spi_busje.transaction(CSpin);
    
    
    while(1){
        auto ldrr = ldr.read();
        auto plusje = plus.read();
        auto minn = min.read();
        auto resett = reset.read();
        if (resett == 0 or score > 9){
            score = 0;
            hwlib::cout << "reset" << hwlib::endl;
        }
        else if (plusje == 0){
            score = score + 1;
            hwlib::cout << "Er is gescoord!" << hwlib::endl;
        }
        else if (minn == 0){
            score = score - 1;
            hwlib::cout << "-1" << hwlib::endl;
        }
        else if (ldrr == 1){
            score = score + 1;
            hwlib::cout << "Er is gescoord!" << hwlib::endl;
        }
        
        CSpin.write(1);
        hwlib::wait_ms(200);
        CSpin.write(0);
        while(1){
            trans.write(0x01);
            trans.write(score);
            CSpin.write(1);
            break;
        }
    }
}

void scorebord::setup(hwlib::target::pin_out & sclk, hwlib::target::pin_out & mosi, hwlib::target::pin_in & miso,
    hwlib::target::pin_out & CSpin){
    
    auto spi_busje = hwlib::spi_bus_bit_banged_sclk_mosi_miso( sclk, mosi, miso);
    auto trans = spi_busje.transaction(CSpin);
    
    //come out of shutdown    
    CSpin.write(1);
    hwlib::wait_ms(200);
    CSpin.write(0);
    while(1){
        trans.write(0x0C);
        trans.write(0x01);
        CSpin.write(1);
        break;
    }
    
    //make possible to give a int and it automaticly knows wich segments to turn on (decode)
    CSpin.write(0);
    while(1){
        trans.write(0x09);
        trans.write(0xFF);
        CSpin.write(1);
        break;
    }
    
    //set all digits OFF     
    for (int i = 0; i < 9; i++){
        CSpin.write(0);
        while(1){
            trans.write(i);
            trans.write(0x0F);
            CSpin.write(1);
            break;
        }
    }
    
    //how bright the numbers are
    CSpin.write(0);
    while(1){
        trans.write(0x0A);
        trans.write(0x02);
        CSpin.write(1);
        break;
    }
    
    //set the number of digits used
    CSpin.write(0);
    while(1){
        trans.write(0x0B);
        trans.write(0x01);
        CSpin.write(1);
        break;
    }
    hwlib::cout << "Setup done, game can start" << hwlib::endl;
}
