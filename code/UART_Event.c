
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

const  unsigned char String4[]="�˳�Ԫ(1452546)�y�����¶�Ϊ:";
unsigned char String5[5];//�����¶�
const  unsigned char String6[]="���϶�\r\n";
const  unsigned char String7[]="�˳�Ԫ(1452546)�������46\r\n";



void Command_match();  // �ַ�ƥ�������
/******************************************************************************************************
 * ��       �ƣ�UART_OnTx()
 * ��       �ܣ�UART��Tx�¼�������
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����Tx_FIFO�������ݾͽ������Ƶ�Tx Buffer�Ĵ�����ȥ
 * ��       ������
 ******************************************************************************************************/
void UART_OnTx(void)
{
	unsigned char Temp;
	if(Tx_FIFO_DataNum>0)
	{
		Tx_FIFO_ReadChar(&Temp);	//����FIFO�⺯��
		UCA0TXBUF= Temp;
	}
}
/******************************************************************************************************
 * ��       �ƣ�UART_OnRx()
 * ��       �ܣ�UART��Rx�¼�������
 * ��ڲ�������
 * ���ڲ�������
 * ˵       �����Խ��յ������ݣ�����Դ����д���
 * ��       ������
 ******************************************************************************************************/
void UART_OnRx(void)
{
	unsigned char Temp = 0;
	Temp=UCA0RXBUF;			// Ԥ����Tx Buffer����
	//-----���ȱ��������Ļ-----
	if(Temp == 0x0d)				//����ǻس�
	{
		Tx_FIFO_WriteChar('\r');
		Tx_FIFO_WriteChar('\n');
	}
	else if(Temp==0x08 || Temp==0x7f)	//������˸�
	{
		UART_SendString(Out_DELETE);		// �����˸��
	}
	else										//�����������ʾ����
		Tx_FIFO_WriteChar(Temp);		//��������
	//-----�س���ʼ����֡ʶ��-----
	if(Temp == 0x0d)				// ����ǻس������������������˶ϡ���
	{
		if(Rx_FIFO_DataNum > 0)	//FIFO�������ݣ�����������ж�
		{
			Command_match();		//�ж�������ʲô
			Rx_FIFO_Clear();				//���FIFO
		}
		else{									//���ɶ���ݶ�û�У������˸��س���
			UART_SendString(String1);  	//��ʾ������ʾ��
			UART_SendString(String2);	//��ʾ������ʾ��
		}
	}
	//-----�˸����Ҫɾ��FIFO��һ������-----
	else if(Temp==0x08 || Temp==0x7f)	//������˸��������Ҫɾ��һ��
	{
		if( Rx_FIFO_DataNum>0)			//�����ݲ���Ҫɾ��û�����ݵ�Ȼ����ɾ
		{
			_disable_interrupts();			//����FIFOʱ������ж�
			Rx_FIFO_DataNum--;				//�������ݼ�1
			if(Rx_FIFO_IndexW >0)			//��ֹ���
				Rx_FIFO_IndexW--;				//дָ���˸�
			 _enable_interrupts();
		}
	}
	//-----�Ȳ��ǻس�Ҳ�����˸��Ǿ���������������-----
	else
	{
		Rx_FIFO_WriteChar(Temp); 			//����дFIFO
	}
}
/******************************************************************************************************
 * ��       �ƣ�UART_SendString()
 * ��       �ܣ���UART����һ���ַ���
 * ��ڲ�����*Ptr���ַ����׵�ַ
 * ���ڲ�������
 * ˵       �����ַ�������ܳ�������Tx_FIFO���ȣ���ᷢ������CPU
 * ��       ������
 ******************************************************************************************************/
void UART_SendString(const unsigned char *Ptr) //����λ�������ַ���
{
	while(*Ptr)
	{
		Tx_FIFO_WriteChar(*Ptr++);
	}
}
/******************************************************************************************************
 * ��       �ƣ�Command_match()
 * ��       �ܣ��Խ��յ����������ݽ���ƥ�䣬����ƥ��������LED�����Դ�����
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ������4��Ԥ��Լ���������֣�LED1_ON,LED1_OFF,LED2_ON,LED2_OFF
 * ��       ������
 ******************************************************************************************************/
void Command_match()  // �ַ�ƥ������
{

					if((Rx_FIFO[0]=='4')&&(Rx_FIFO[1]=='6'))
					{
						Time0_A_Init();
						 ADC10CTL0 |= ENC + ADC10SC;            // Sampling and conversion start
						 //     _bis_SR_register(CPUOFF + GIE);       	 // LPM0 with interrupts enabled
						      __delay_cycles(1000);
					    long I= temp*4225/1024 - 2777;		//ת��Ϊ���϶ȣ���10������
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



