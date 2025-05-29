#include <iostream>
#include <verilated.h>
#include "Vfp32_sqrt_comb.h"

int time_counter = 0;

int main(int argc, char** argv) {

    Verilated::commandArgs(argc, argv);

    Vfp32_sqrt_comb* dut = new Vfp32_sqrt_comb();

    while (time_counter < 500) {
//        dut->clk = (time_counter % 2 == 0) ? 1 : 0; // Toggle clock every cycle
        float rand_val = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100.0f; // 0.0 to 100.0

        union {
            float f;
            uint32_t u;
        } conv;
        conv.f = rand_val;
        dut->a = conv.u;
//        dut->a = rand_val;
//        dut->a = 16.0f; // Set input value for square root
        dut->eval(); // Evaluate the design

        // Convert the output back to float
        union {
            uint32_t u;
            float f;
        } out_conv;
        out_conv.u = dut->y;

        // Print the output values
        std::cout << "Time: " << time_counter 
                  << " | sqrt_out: " << out_conv.f 
                  << " | sqrt_in: " << conv.f
                  << " | sqrt_out(math): " << sqrt(conv.f)
                  << std::endl;

        time_counter++;
    }

    dut->final();
    delete dut; // Clean up the allocated memory
    return 0;
}