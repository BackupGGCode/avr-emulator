#include <AvrEmualtor.h>
#include <windows.h>
using namespace std;

class myCallback : avremu::PheripheralCallback
{
public:
    avremu::AVRMicrocontroller  *mcu;
    void onCallback(avremu::IPeripheralDevice *sender, avremu::u8 type)
    {
        if(type == IOPORT_CHANGE)
        {
          //  printf("PORTB is %X at cc: %d\n",(*((avremu::IOPorts*)sender)->PORT_reg),
              //     mcu->_cycle_counter);
            //system("pause");
        }
    }
};
int main()
{
    myCallback cbl;
	avremu::Atmega8Microcontroller* micro = new avremu::Atmega8Microcontroller(new avremu::StandardAVROpcodeInterpreter());
    cbl.mcu = micro;
    avremu::IntelHexFileLoader flash_loader(
                "E:\\Projekty\\AVRSimulator\\TestPrograms\\Avr_Test\\avr_test.hex");

    flash_loader.writeMemory(micro->_flash_program,micro->_flash_program_size);
    micro->portB->getCallbackContainer()->add((avremu::PheripheralCallback*)&cbl);


    avremu::u8 SREG_tmp = *(micro->_SREG_addr);
    int tc1 = GetTickCount();
    for(int i=0;i<32;i++)
//    unsigned int i=0;
//    for(;;)
    {
       //std::this_thread::sleep_for(std::chrono::microseconds(5));
        micro->processTick(false);

//        printf("R17 = 0x%x;\n",micro->_general_registers[17]);
        /*if(SREG_tmp != *(micro->_SREG_addr) && false)
        {
            SREG_tmp = *(micro->_SREG_addr);

            printf("R1 = %x(%d) -> ",micro->_general_registers[1],micro->_general_registers[1]);
            printf("[%d] ->T: %d, H: %d, S: %d, V: %d, N: %d, Z: %d, C: %d ",
                   micro->_cycle_counter,BIT(*(micro->_SREG_addr),avrsim::T_bit),
                   BIT(*(micro->_SREG_addr),avrsim::H_bit),BIT(*(micro->_SREG_addr),avrsim::S_bit),
                   BIT(*(micro->_SREG_addr),avrsim::V_bit),BIT(*(micro->_SREG_addr),avrsim::N_bit),
                   BIT(*(micro->_SREG_addr),avrsim::Z_bit),BIT(*(micro->_SREG_addr),avrsim::C_bit));
            printf("[change]\n");

//            //break;

        }*/
//        printf("\n");
//        i++;
    }
    int tc2 = GetTickCount();

    printf("ticks: %d\n", tc2 - tc1);
    delete micro;
    return 0;
}

