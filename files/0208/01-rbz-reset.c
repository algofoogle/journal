#include <defs.h>
#include <stub.h>


void configure_io()
{
    //  ======= set each IO to the desired configuration =============

    //  GPIO 0 is turned off to prevent toggling the debug pin.
    //  For debug, make this an output and drive it externally to ground.
    reg_mprj_io_0  = GPIO_MODE_MGMT_STD_ANALOG;

    // Changing configuration for IO[4:1] will interfere with programming flash.
    // If you change them, you may need to hold reset while powering up the board
    // and initiating flash to keep the process configuring these IO from their
    // default values.
    reg_mprj_io_1  = GPIO_MODE_MGMT_STD_OUTPUT;         // SDO
    reg_mprj_io_2  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;   // SDI
    reg_mprj_io_3  = GPIO_MODE_MGMT_STD_INPUT_PULLUP;   // CSB: PULLUP avoids floating.
    reg_mprj_io_4  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;   // SCK

    reg_mprj_io_5  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;   // UART Rx
    reg_mprj_io_6  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;   // UART Tx
    reg_mprj_io_7  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;   // IRQ

    // Raybox-zero pins:
    reg_mprj_io_11 = GPIO_MODE_USER_STD_INPUT_PULLUP;   // i_clk: PULLUP avoids floating.
    reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT;         // o_hsync
    reg_mprj_io_13 = GPIO_MODE_USER_STD_OUTPUT;         // o_vsync
    reg_mprj_io_14 = GPIO_MODE_USER_STD_OUTPUT;         // o_tex_csb
    reg_mprj_io_15 = GPIO_MODE_USER_STD_OUTPUT;         // o_tex_sclk
    reg_mprj_io_16 = GPIO_MODE_USER_STD_BIDIRECTIONAL;  // i_tex_in[0] (In) / o_tex_out0 (Out)
    reg_mprj_io_17 = GPIO_MODE_USER_STD_OUTPUT;         // o_gpout[0]
    reg_mprj_io_18 = GPIO_MODE_USER_STD_OUTPUT;         // o_gpout[1]
    reg_mprj_io_19 = GPIO_MODE_USER_STD_OUTPUT;         // o_gpout[2]
    reg_mprj_io_20 = GPIO_MODE_USER_STD_OUTPUT;         // o_gpout[3]
    reg_mprj_io_31 = GPIO_MODE_USER_STD_INPUT_NOPULL;   // i_tex_in[1]   (shared)
    reg_mprj_io_32 = GPIO_MODE_USER_STD_INPUT_NOPULL;   // i_tex_in[2]   (shared)
    reg_mprj_io_34 = GPIO_MODE_USER_STD_INPUT_NOPULL;   // i_tex_in[3]   (shared)
    reg_mprj_io_35 = GPIO_MODE_USER_STD_INPUT_NOPULL;   // i_spare_1     (shared)

    // Otherwise unused pins assigned by this firmware for testing:
    reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;

    // Other projects; set all to be 
    reg_mprj_io_8  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_9  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_33 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

    // Initiate the serial transfer to configure IO
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void delay(const int d)
{
    /* Configure timer for a single-shot countdown */
	reg_timer0_config = 0;
	reg_timer0_data = d;
    reg_timer0_config = 1;

    // Loop, waiting for value to reach zero
    reg_timer0_update = 1;  // latch current value
    while (reg_timer0_value > 0) {
        reg_timer0_update = 1;
    }
}


// Blinks the LED via `gpio`. IO36 follows, IO37 is inverted.
// Period is approx. 2M-cycles (~200ms at 10MHz => 5Hz)
void blink(int blink_delay)
{
    reg_gpio_out = 1;   // LED OFF
    // reg_mprj_datah = 0x00000010; // IO37=0, IO36=1
    // reg_mprj_datal = 0x00000000;

    delay(blink_delay);

    reg_gpio_out = 0;   // LED ON
    // reg_mprj_datah = 0x00000020; // IO37=1, IO36=0
    // reg_mprj_datal = 0x00000000;

    delay(blink_delay);
}


void main()
{
    // See:
    // https://web.open-source-silicon.dev/t/10118431/zzz
    // Set pad's DM value to 110 (fast rise/fall):
    reg_gpio_mode1 = 1; // Sets upper 2 bits of pad's DM value.
    reg_gpio_mode0 = 0; // Sets lower bit of pad's DM value.
    reg_gpio_ien = 1;   // IEb=1 (input disabled)
    reg_gpio_oe = 1;    // OE=1 (output ENabled)

    configure_io();

    // Use DLL instead of direct xclk:
    reg_hkspi_pll_divider = 5;          // Multiply xclk (10MHz) by 5 to get 50MHz.
    reg_hkspi_pll_source  = 0b100010;   // 100=div-4 (12.5MHz), 010=div-2 (25MHz)
    reg_hkspi_pll_ena     = 0b01;       // Select DLL output, enable DLL/DCO
    reg_hkspi_pll_bypass  = 0b0;        // Disable DLL bypass.
    reg_clk_out_dest      = 0b110;      // IO15=user_clock2, IO14=wb_clk_i

    // Configure LA[115:64] as outputs from SoC, but note that this config is from
    // the perspective of the UPW, so we configure these as INPUTS:
    reg_la2_oenb = reg_la2_iena = 0xffffffff; // Set 64..95 to UPW inputs.
    reg_la3_oenb = reg_la3_iena = 0x000fffff; // Set 96..115 to UPW inputs too.
    // reg_la3_oenb = reg_la3_iena = 0xffffffff; // Set 96..115 to UPW inputs too.

    int blink_delay = 10000000;

    // Set upper 20 bits (115:96) of RBZ LA config:
    reg_la3_data =
                 0b01100000000000000100;
    // xxxxxxxxxxxx--------------------     (unused LAs)
    // ------------0-------------------     i_spare_0
    // -------------1------------------     i_reg_outs_enb (1=direct out, not reg'd)
    // --------------1-----------------     i_mode[2]: 1=generated textures; 0=SPI textures
    // ---------------0----------------     i_mode[1]: i_inc_py
    // ----------------0---------------     i_mode[0]: i_inc_px
    // -----------------000000---------     i_gpout5_sel (unused)
    // -----------------------000000---     i_gpout4_sel (unused)
    // -----------------------------1--     i_debug_map_overlay
    // ------------------------------00     Top 2 bits of i_gpout3_sel

    // Set lower 32 bits (95:64) of RBZ LA config:
    reg_la2_data =
     0b00010000001000001001100000100100;
    // 0001----------------------------     i_gpout3_sel=1 (bottom 4 bits) => alt (i_reset_lock_b)
    // ----0---------------------------     i_debug_trace_overlay
    // -----000001---------------------     i_gpout2_sel=1 => alt (user_clock2)
    // -----------000001---------------     i_gpout1_sel=1 => alt (wb_clk_i)
    // -----------------0--------------     i_reg_mosi: 0
    // ------------------0-------------     i_reg_sclk: 0
    // -------------------1------------     i_reg_csb: 1 => inactive
    // --------------------1-----------     i_debug_vec_overlay: 1 (ON)
    // ---------------------000001-----     i_gpout0_sel=1 => alt (rbzero_reset)
    // ---------------------------0----     i_vec_mosi: 0
    // ----------------------------0---     i_vec_sclk: 0
    // -----------------------------1--     i_vec_csb: 1 => inactive
    // ------------------------------00     i_reset_lock_b/a: same = hold in reset

	while (1) {
        blink(blink_delay);
    }
}

