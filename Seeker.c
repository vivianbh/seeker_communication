#include <string.h>
#include "Seeker.h"

/**************************************************************************************************/
/* seeker data receieved                                                                          */
/**************************************************************************************************/
uint8_t  seekerRcvBuff[64];
uint8_t  seekerPacketReceived = 0;
uint16_t seekerPacketCnt = 0;
uint16_t seekerPacketErrorCnt = 0;
uint16_t seekerPacketFreq = 0;
seekerData_t seekerData;

void seekerParser(uint8_t Rxbyte){

    static uint8_t  state = 0;
    static uint8_t  msgLen = 0;
    static uint8_t  msgId = 0;
    static uint8_t  chkSumRcv = 0;
    static uint16_t chkSum = 0;
    static uint16_t count = 0;

    switch( state ){
        // $DAT
        case 0:
            if( Rxbyte == '$' )
                state = 1;
            else
                state = 0;
            break;

        case 1:
            if( Rxbyte == 'D' )
                state = 2;
            else
                state = 0;
            break;

        case 2:
            if( Rxbyte == 'A' )
                state = 3;
            else
                state = 0;
            break;

        case 3:
            if( Rxbyte == 'T' )
                state = 4;
            else
                state = 0;
            break;

        // [MSG LEN]
        case 4:
            msgLen = Rxbyte;
            if( msgLen == (sizeof(seekerData_t)+1) ){
                chkSum = Rxbyte;
                state = 5;
            }
            else
                state = 0;
            break;

        // [MSG ID]
        case 5:
            msgId = Rxbyte;
            if( msgId == 0x02 ){
                chkSum += Rxbyte;
                state = 6;
                count = 0;
            }
            else
                state = 0;
            break;

        // [DATA]
        case 6:
            if( count < sizeof(seekerRcvBuff) ){
                seekerRcvBuff[count] = Rxbyte;
                chkSum += Rxbyte;
                count++;
                if( count >= sizeof(seekerData_t) ){
                    state = 7;
                }
            }
            else
                state = 0;
            break;

        // [CHKSUM]
        case 7:
            chkSumRcv = Rxbyte;
            state = 8;
            break;

        // [END]
        case 8:
            if( ((uint8_t)(chkSum&0x00FF) == chkSumRcv) && (Rxbyte == 0x0A) ) {
                seekerPacketCnt++;
                seekerPacketReceived = 1;
            }
            else {
                seekerPacketErrorCnt++;
            }
            state = 0;
            break;
    }
}

void getSeekerData(void){
    if( seekerPacketReceived ){
        memcpy((uint8_t*)&seekerData,  (uint8_t*)&seekerRcvBuff, sizeof(seekerData_t));
        seekerPacketReceived = 0;

        printf("\nread----------------\n");
        for(int i = 0; i < sizeof(seekerRcvBuff); i++){
            printf("%04x\t", seekerRcvBuff[i]);
        }
        printf("\n");
    }
}

/**************************************************************************************************/
/* seeker command send, call every 20ms(default).                                                 */
/**************************************************************************************************/
uint8_t seekerCmd_Txbuff[(sizeof(seeker_CMD_t)+8)];
seeker_CMD_t seekerCmd = {0, 6, 0, 0, 420, 420, 0, 3746, 2656, -2656, 12000, -3000, 45, 0,
                                      0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
uint16_t seekerCmd_checkSum = 0;

void sendSeekerCommand(void){
    seekerCmd_Txbuff[0] = '$';
    seekerCmd_Txbuff[1] = 'D';
    seekerCmd_Txbuff[2] = 'A';
    seekerCmd_Txbuff[3] = 'T';
    seekerCmd_Txbuff[4] = sizeof(seeker_CMD_t) + 1;
    seekerCmd_Txbuff[5] = 0x82;

    memcpy((uint8_t*)&seekerCmd_Txbuff[6], (uint8_t*)&seekerCmd, sizeof(seeker_CMD_t));

    seekerCmd_checkSum = 0;
    for( uint8_t index = 4 ; index < (sizeof(seeker_CMD_t)+6) ; index++){
        seekerCmd_checkSum += seekerCmd_Txbuff[index];
    }

    seekerCmd_Txbuff[(sizeof(seeker_CMD_t)+6)] = (uint8_t)(seekerCmd_checkSum&0x00FF);
    seekerCmd_Txbuff[(sizeof(seeker_CMD_t)+7)] = 0x0A;

    /* send seekerCmd_Txbuff out by user*/
    //UART_SendData((uint8_t*)&seekerCmd_Txbuff, sizeof(seekerCmd_Txbuff));
}

uint8_t* UART_SendData(){
    //printf("seekerCmd_Txbuff: %p\n", &seekerCmd_Txbuff);
    return seekerCmd_Txbuff;
}
