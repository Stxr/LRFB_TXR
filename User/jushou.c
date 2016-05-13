#include "jushou.h"
void jushou(void)
{
  SetServoPosition(4,712,200);
  SetServoPosition(5,592,200);

  SetServoPosition(2,690,200);
  SetServoPosition(1,531,200);
  delay_ms(500);

  SetServoPosition(6,246,200);
  SetServoPosition(3,820,200);
  delay_ms(500);

}
void init(void)
{

  SetServoPosition(1,512,200);
  SetServoPosition(2,512,200);
  SetServoPosition(3,512,200);

  SetServoPosition(4,512,200);
  SetServoPosition(5,512,200);
  SetServoPosition(6,512,200);
  delay_ms(5000);
}
void hand1(void)
{
  //两手张开
  SetServoPosition(2,674,200);
  SetServoPosition(5,308,200);
  delay_ms(500);
  //两手抬起
  SetServoPosition(1,192,200);
  SetServoPosition(4,826,200);
  delay_ms(500);
  printf("han1\n");
}
void play(void)
{
  //击打
  SetServoPosition(1,192,200);
  SetServoPosition(2,417,200);//右手
  SetServoPosition(5,599,200);//左手

  SetServoPosition(4,826,200);
  SetServoPosition(3,662,200);
  SetServoPosition(6,663,200);

  delay_ms(500);
  SetServoPosition(1,192,200);
  SetServoPosition(2,674,200);//右手
  SetServoPosition(5,308,200);//左手

  SetServoPosition(4,826,200);
  SetServoPosition(3,512,200);
  SetServoPosition(6,512,200);
  delay_ms(500);
//  printf("play\n");

}
void start(void)
{
    SetServoPosition(1,756,200);
    SetServoPosition(2,213,200);
    SetServoPosition(3,533,200);
    SetServoPosition(4,752,200);
    SetServoPosition(5,545,200);
    SetServoPosition(6,569,200);
//    printf("start\n");
}
void end(void)

{
    SetServoPosition(1,756,200);
    SetServoPosition(2,319,200);
    SetServoPosition(3,458,200);
    SetServoPosition(4,756,200);
    SetServoPosition(5,433,200);
    SetServoPosition(6,530,200);
//    printf("end\n");
}
void start1(void)
{
    SetServoPosition(3,201,200);
    SetServoPosition(2,500,200);
    SetServoPosition(1,501,200);
    SetServoPosition(6,221,200);
    SetServoPosition(5,761,200);
    SetServoPosition(4,580,200);
//    printf("start1\n");
}
void end1(void)

{
    SetServoPosition(3,201,200);
    SetServoPosition(2,436,200);
    SetServoPosition(1,523,200);
    SetServoPosition(6,221,200);
    SetServoPosition(5,643,200);
    SetServoPosition(4,553,200);
//    printf("end1\n");
}
