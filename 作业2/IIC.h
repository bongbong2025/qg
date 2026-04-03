#ifndef __IIC_H__
#define __IIC_H__


void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(void);
void IIC_NotAck(void);
unsigned char IIC_WaitAck(void);
void IIC_WriteByte(unsigned char dat);
unsigned char IIC_ReadByte(unsigned ack);

#endif