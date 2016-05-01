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