/*
 * FAN_INTERFACE.h
 *
 * Created: 10/25/2022 12:22:36 AM
 *  Author: AHMED ELDEEB
 */ 


#ifndef FAN_INTERFACE_H_
#define FAN_INTERFACE_H_

void Fan_init(void);
void Fan_SET_ON(void);
void Fan_SET_OFF(void);
u8 Fan_Read(void);



#endif /* FAN_INTERFACE_H_ */