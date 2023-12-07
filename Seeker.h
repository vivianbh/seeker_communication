#ifndef _SEEKER_
#define _SEEKER_

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t   video_Resolution;          // 0:1280x720p, 2:1920x1080p,
    uint8_t   gimbal_Mode;               // 0:FrontView, 1:manual(joystick), 2:scan_AZ, 3:scan_EL, 4:gpsLock, 5:videoTrack, 6:manual(angleSet)
    uint16_t  curr_angular_Motor_Pan;    // unit: scale 0.01 to deg/s, range:(0, 4500)
    uint16_t  curr_angular_Motor_Tilt;   // unit: scale 0.01 to deg/s, range:(0, 4500)
    int16_t   curr_angle_Motor_Pan;      // unit: scale 0.01 to deg, range:(-11000{left}, 11000{right})
    int16_t   curr_angle_Motor_Tilt;     // unit: scale 0.01 to deg, range:(12000{down}, -3000{up})
    uint16_t  set_angular_Motor_Pan;     // unit: scale 0.01 to deg/s, range:(0, 4500)
    uint16_t  set_angular_Motor_Tilt;    // unit: scale 0.01 to deg/s, range:(0, 4500)
    int16_t   set_angle_Motor_Pan;       // unit: scale 0.01 to deg, range:(-11000{left}, 11000{right})
    int16_t   set_angle_Motor_Tilt;      // unit: scale 0.01 to deg, range:(12000{down}, -3000{up})
    int16_t   set_max_Angle_Motor_Pan;   // unit: scale 0.01 to deg, range:(-11000{left}, 11000{right})
    int16_t   set_min_Angle_Motor_Pan;   // unit: scale 0.01 to deg, range:(-11000{left}, 11000{right})
    int16_t   set_max_Angle_Motor_Tilt;  // unit: scale 0.01 to deg, range:(12000{down}, -3000{up})
    int16_t   set_min_Angle_Motor_Tilt;  // unit: scale 0.01 to deg, range:(12000{down}, -3000{up})
    uint16_t  EO_Zoom;                   // unit: scale 0.1 to ratio, range:(10, 250)
    uint8_t   Laser_Status;              // 0:off, 1:on, default:0:off
    uint16_t  LRF_Distance;              // unit: ft, range:(0, 65535)
    int16_t   estimateTarget_AZ;         // unit: scale 0.01 to deg, range:(-12000{left}, 12000{right})
    int16_t   estimateTarget_EL;         // unit: scale 0.01 to deg, range:(14000{down}, -5000{up})
    uint8_t   command;                   // 0:standby, 1:attack, 2:cancel, 3:VC reset, 4.gimbal reset
} __attribute__((packed)) seekerData_t;

typedef struct
{
    uint8_t   set_video_Resolution;     // 0:1280x720p, 2:1920x1080p, default:0:1280x720p
    uint8_t   set_gimbal_mode;          // 0:FrontView, 1:manual(joystick), 2:scan_AZ, 3:scan_EL, 4:gpsLock, 5:videoTrack, 6:manual(angleSet), default:0:FrontView
    int16_t   set_joyStick_Xaxis;       // unit: scale 0.01 to %, range:(-10000, 10000), default:0
    int16_t   set_joyStick_Yaxis;       // unit: scale 0.01 to %, range:(-10000, 10000), default:0
    uint16_t  set_angular_Motor_Pan;    // unit: scale 0.01 to deg/s, range:(0, 4500), default:420
    uint16_t  set_angular_Motor_Tilt;   // unit: scale 0.01 to deg/s, range:(0, 4500), default:420
    int16_t   set_angle_Motor_Pan;      // unit: scale 0.01 to deg, range:(-11000{left}, 11000{right}), default:0
    int16_t   set_angle_Motor_Tilt;     // unit: scale 0.01 to deg, range:(12000{down}, -3000{up}),     default:  17.46(1746)
    int16_t   set_max_Angle_Motor_Pan;  // unit: scale 0.01 to deg, range:(-11000{left}, 11000{right}), default:  26.56(2656)
    int16_t   set_min_Angle_Motor_Pan;  // unit: scale 0.01 to deg, range:(-11000{left}, 11000{right}), default: -26.56(2656)
    int16_t   set_max_Angle_Motor_Tilt; // unit: scale 0.01 to deg, range:(12000{down}, -3000{up}),     default:  120.00(12000)
    int16_t   set_min_Angle_Motor_Tilt; // unit: scale 0.01 to deg, range:(12000{down}, -3000{up}),     default: -30.00(-3000)
    uint16_t  set_EO_Zoom;              // unit: scale 0.1 to ratio, range:(10, 250), default:4.5(45)
    uint8_t   set_Laser_Status;         // 0:off, 1:on, default:0:off
    int32_t   uav_GPS_Longitude;        // unit: scale 1E-07 to deg, range:(-1800000000, 1800000000), WGS84
    int32_t   uav_GPS_Latitude;         // unit: scale 1E-07 to deg, range:( -900000000,  900000000), WGS84
    int32_t   uav_GPS_Altitude;         // unit: scale 1E-04 to ft, WGS84
    int16_t   uav_Attitude_roll;        // unit: scale 0.01 to deg, range:(-18000, 18000), body3-2-1
    int16_t   uav_Attitude_pitch;       // unit: scale 0.01 to deg, range:( -9000,  9000), body3-2-1
    uint16_t  uav_Attitude_yaw;         // unit: scale 0.01 to deg, range:(     0, 36000), body3-2-1
    uint16_t  uav_course_angel;         // unit: scale 0.01 to deg, range:(     0, 36000)
    int16_t   uav_angel_of_attack;      // unit: scale 0.01 to deg, range:(-10000, 10000)
    int32_t   target_GPS_Longitude;     // unit: scale 1E-07 to deg, range:(-1800000000, 1800000000), WGS84
    int32_t   target_GPS_Latitude;      // unit: scale 1E-07 to deg, range:( -900000000,  900000000), WGS84
    int32_t   target_GPS_Altitude;      // unit: scale 1E-04 to ft, default:0, WGS84
    int16_t   target_Dx;                // unit: pixel, range:(-2048{left}, 2048{right}), default:0
    int16_t   target_Dy;                // unit: pixel, range:(-2048{down}, 2048{up}),    default:0
    uint8_t   command;                  // 0:standby, 1:attack, 2:cancel, 3:VC reset, 4.gimbal reset, range:(0, 255), default:0
    uint8_t   trackerState;
} __attribute__((packed)) seeker_CMD_t;

void seekerParser(uint8_t Rxbyte);
void getSeekerData(void);      
void sendSeekerCommand(void);   

uint8_t* UART_SendData();

#endif
