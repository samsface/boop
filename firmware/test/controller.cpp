#include <catch2/catch.hpp>
#include "controller.hpp"

optional<message> read_message(detail::pin& pin)
{
    comm::protocol p;
    
    while(true)
    {
        auto msg = p(pin.read());
    
        if(msg) return msg;
        if(pin.data.empty()) return {};
    }
}

TEST_CASE("controller config", "[controller]")
{
    auto& a = arduino;
    
    controller c;
    
    SECTION("set_address")
    {
        message msg_in{0, 1, set_address, 1};
        
        a.pins[0].write(comm::protocol{}(msg_in));
        c.tick(23);
        
        auto msg = read_message(a.pins[1]);
        
        REQUIRE(msg);
        REQUIRE(msg->ack == 1);
        REQUIRE(msg->function_code == acking);
    }
    
    SECTION("set_wifi_ssid")
    {
        message msg_in{0, 1, set_wifi_ssid };
        msg_in.value[0] = 's';
        msg_in.value[1] = 'a';
        msg_in.value[2] = 'm';
        
        a.pins[0].write(comm::protocol{}(msg_in));
        c.tick(23);
        
        auto msg_ack = read_message(a.pins[1]);
        
        REQUIRE(msg_ack);
        REQUIRE(msg_ack->ack == 1);
        REQUIRE(msg_ack->function_code == acking);
    }
}

TEST_CASE("controller scripting", "[controller]")
{ 
    auto& a = arduino;
    
    controller c;
    
    SECTION("set_script")
    {
        message msg_in{0, 1, set_script0};
        msg_in.value[0] = script::wait_for_button0_down;
        msg_in.value[1] = script::set_led0_solid_orange;
        msg_in.value[2] = script::wait_for_ack_with_5s_timeout;
        msg_in.value[3] = script::set_led0_solid_green;
        msg_in.value[4] = script::wait_for_1s;
        msg_in.value[5] = script::set_led0_off;
        msg_in.value[6] = script::goto_start;
        
        a.pins[0].write(comm::protocol{}(msg_in));
        
        c.tick(24);
        
        auto msg_ack = read_message(a.pins[1]);
        
        REQUIRE(msg_ack);
        REQUIRE(msg_ack->ack == 1);
        REQUIRE(msg_ack->function_code == acking);
        
        c.tick(1);
        
        REQUIRE(a.pins[11].data.empty());
        
        a.pins[8].write(LOW);
        
        c.tick(1);
    }
}