
#include "MSP430G2553.h"
#include "UARt_Global.h"
#include "UART_FIFO.h"
#include "UART_Event.h"

#include "fengmingqi.h"
extern long temp;

#define LED1_ON P1DIR|=BIT0; P1OUT|=BIT0
#define LED1_OFF P1DIR|=BIT0; P1OUT&=~BIT0
#define LED2_ON P1DIR|=BIT6; P1OUT|=BIT6
#define LED2_OFF P1DIR|=BIT6; P1OUT&=~BIT6

const  unsigned char String4[]="邓程元(1452546)測量的温度为:";
unsigned char String5[5];//测量温度
const  unsigned char String6[]="摄氏度\r\n";
const  unsigned char String7[]="邓程元(1452546)的序号是46\r\n";



void Command_match();  // 字符匹配命令函数
/******************************************************************************************************
 * 名       称：UART_OnTx()
 * 功       能：UART的Tx事件处理函数
 * 入口参数：无
 * 出口参数：无
 * 说       明：Tx_FIFO里有数据就将数据移到Tx Buffer寄存器中去
 * 范       例：无
 ******************************************************************************************************/
void UART_OnTx(void)
{
	unsigned char Temp;
	if(Tx_FIFO_DataNum>0)
	{
		Tx_FIFO_ReadChar(&Temp);	//调用FIFO库函数
		UCA0TXBUF= Temp;
	}
}
/******************************************************************************************************
 * 名       称：UART_OnRx()
 * 功       能：UART的Rx事件处理函数
 * 入口参数：无
 * 出口参数：无
 * 说       明：对接收到的数据，区别对待进行处理
 * 范       例：无
 ******************************************************************************************************/
void UART_OnRx(void)
{
	unsigned char Temp = 0;
	Temp=UCA0RXBUF;			// 预存下Tx Buffer数据
	//-----首先必须回显屏幕-----
	if(Temp == 0x0d)				//如果是回车
	{
		Tx_FIFO_WriteChar('\r');
		Tx_FIFO_WriteChar('\n');
	}
	else if(Temp==0x08 || Temp==0x7f)	//如果是退格
	{
		UART_SendString(Out_DELETE);		// 发送退格键
	}
	else										//如果是正常显示数据
		Tx_FIFO_WriteChar(Temp);		//回显数据
	//-----回车后开始数据帧识别-----
	if(Temp == 0x0d)				// 如果是回车，表明可以做个”了断“了
	{
		if(Rx_FIFO_DataNum > 0)	//FIFO里有数据，则进行数据判断
		{
			Command_match();		//判断命令是什么
			Rx_FIFO_Clear();				//清空FIFO
		}
		else{									//如果啥数据都没有（光敲了个回车）
			UART_SendString(String1);  	//显示命令提示符
			UART_SendString(String2);	//显示命令提示符
		}
	}
	//-----退格键则要删除FIFO里一个数据-----
	else if(Temp==0x08 || Temp==0x7f)	//如果是退格键，则需要删除一个
	{
		if( Rx_FIFO_DataNum>0)			//有数据才需要删，没有数据当然不用删
		{
			_disable_interrupts();			//操作FIFO时必须关中断
			Rx_FIFO_DataNum--;				//待读数据减1
			if(Rx_FIFO_IndexW >0)			//防止溢出
				Rx_FIFO_IndexW--;				//写指针退格
			 _enable_interrupts();
		}
	}
	//-----既不是回车也不是退格，那就正常存命令数据-----
	else
	{
		Rx_FIFO_WriteChar(Temp); 			//正常写FIFO
	}
}
/******************************************************************************************************
 * 名       称：UART_SendString()
 * 功       能：用UART发送一个字符串
 * 入口参数：*Ptr：字符串首地址
 * 出口参数：无
 * 说       明：字符串如果很长，超过Tx_FIFO长度，则会发生阻塞CPU
 * 范       例：无
 ******************************************************************************************************/
void UART_SendString(const unsigned char *Ptr) //给上位机发送字符串
{
	while(*Ptr)
	{
		Tx_FIFO_WriteChar(*Ptr++);
	}
}
/******************************************************************************************************
 * 名       称：Command_match()
 * 功       能：对接收到的命令数据进行匹配，根据匹配结果控制LED并回显处理结果
 * 入口参数：无
 * 出口参数：无
 * 说       明：共4种预先约定的命令字：LED1_ON,LED1_OFF,LED2_ON,LED2_OFF
 * 范       例：无
 ******************************************************************************************************/
void Command_match()  // 字符匹配命令
{

					if((Rx_FIFO[0]=='4')&&(Rx_FIFO[1]=='6'))
					{
						Time0_A_Init();
						 ADC10CTL0 |= ENC + ADC10SC;            // Sampling and conversion start
						 //     _bis_SR_register(CPUOFF + GIE);       	 // LPM0 with interrupts enabled
						      __delay_cycles(1000);
					    long I= temp*4225/1024 - 2777;		//转换为摄氏度，并10倍处理
						String5[0]=(I/100)+48;
						String5[1]=((I%100)/10)+48;
						String5[2]='.';
						String5[3]=((I%100)%10)+48;
						String5[4]=0;
						UART_SendString(String4);
						UART_SendString(String5);
						UART_SendString(String6);
					}
					else
					{
					   Time0_A_Init();
					   Time0_A_Init();
					   Time0_A_Init();
					   UART_SendString(String7);
					}

}



