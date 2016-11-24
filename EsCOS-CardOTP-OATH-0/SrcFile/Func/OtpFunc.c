/********************************************************************
                          Nationz Co.,Ltd
        Copyright (c) 2009��2015 All Rights Reserved
 ********************************************************************
File: OtpFunc.c
History��
Version                      Author                     Date
V0.1                         nationz                  2013-04-2

Description:
     OtpFunc Source Code File;
Function list:
    UINT8 ucOtpByteRead(UINT16 Addr);
    void vOtpRead(UINT16 Addr,UINT16 Len,UINT8  *DataBuf);
            
Special statement:
     NULL
 *******************************************************************/
#define _OTPFUNC_C_
#include "OTPFUNC.H"
#include "OTPFRAME.H"
#include "LCDFUNC.H"
#include "SCUFUNC.H"
#include "string.H"	
#include "SM3FUNC.H"
#include "SM4.h"
#include "SM4Process.h"
#include "UARTFRAME.h"
#include "TbcFunc.h"
//#include "SM3.h"
#include "Typedefine.h"
#include "Sha1.h"
#include "Hmac.h"

u1 idata g_u1RandCnt _at_ 0x39;
u1 g_pu1Random[CHAL_LEN];
u1 g_u1OtpInput[80];
/********************************************************************
Function name:       UINT8 ucOtpByteRead(UINT16 Addr)
Input parameters:
    UINT16 Addr�� read Address	
	 
Return:
    UINT8:return data of the address
Function:
    read one byte from the specify address 
********************************************************************/
#if 0
UINT8 ucOtpByteRead(UINT16 Addr)
{
	UINT8 DataValue;
	UINT8 code *pAddr;
	pAddr =(UINT8 code *) Addr;	
	DataValue = *pAddr;	
	return DataValue;
}
#endif
/********************************************************************
Function name:       void vOtpRead(UINT16 Addr,UINT16 Len,UINT8  *DataBuf)
Input parameters:
    UINT16 Addr��read Address
	UINT16 Len:	 length of data to read
	UINT8  *DataBuf: save the data read from the address
	 
Return:
    void
Function:
    read  data from the specify address
********************************************************************/
#if 0
void vOtpRead(UINT16 Addr,UINT16 Len,UINT8  *DataBuf)
{
	UINT16 i;
	UINT8 code *pAddr;
	pAddr = (UINT8 code *)Addr;
	for(i=0;i<Len;i++)
	{
		*DataBuf++=*pAddr++;
	}
}
#endif
/********************************************************************
Function name:      void vOtpRead_ChipSn(UINT8  *DataBuf)
Input parameters:     
	UINT8  *DataBuf: save the data read from the address
	 
Return:
    void
Function:
    read the Chip SN 
********************************************************************/

#if 0
void vOtpRead_ChipSn(UINT8  *DataBuf)
{
	UINT16 i;
	UINT8 code *pAddr;

#ifdef  _CODE_16K_
	pAddr = (UINT8 code *)(0X3FE0);
#endif

#ifdef  _CODE_24K_
	pAddr = (UINT8 code *)(0X5FE0);
#endif

#ifdef  _CODE_48K_
	pAddr = (UINT8 code *)(0XBFE0);
#endif

	for(i=0;i<16;i++)
	{
		*DataBuf++=*pAddr++;
	}
}
#endif

#if 0
u1 PinPowerCheck(u1 *pu1DataBuf)
{
		
	if((pu1DataBuf[0]==pu1DataBuf[1]))						// 111111  123456  112233  654321  332211��������
	{
		if((pu1DataBuf[0]==pu1DataBuf[2]))
		{
			if((pu1DataBuf[0]==pu1DataBuf[3])&&(pu1DataBuf[0]==pu1DataBuf[4])&&(pu1DataBuf[0]==pu1DataBuf[5]))
			{
				//while(1);
				return 1;
			}
		}
		else if((pu1DataBuf[0]>pu1DataBuf[2]))
		{
			if((pu1DataBuf[0]-pu1DataBuf[2])==1)
			{
				if((pu1DataBuf[2]==pu1DataBuf[3]))
				{
					if((pu1DataBuf[2]>pu1DataBuf[4])&&((pu1DataBuf[2]-pu1DataBuf[4])==1))
					{
						if((pu1DataBuf[4]==pu1DataBuf[5]))
						{
							return 1;
						}
					}
				}
			}
		}
		else
		{
			if((pu1DataBuf[2]-pu1DataBuf[0])==1)
			{
				if((pu1DataBuf[2]==pu1DataBuf[3]))
				{
					if((pu1DataBuf[4]>pu1DataBuf[2])&&((pu1DataBuf[4]-pu1DataBuf[2])==1))
					{
						if((pu1DataBuf[4]==pu1DataBuf[5]))
						{
							return 1;
						}
					}
				}
			}
		}
	}
	#if 1
	else if(pu1DataBuf[0]>pu1DataBuf[1])
	{
		if((pu1DataBuf[0]-pu1DataBuf[1])==1)
		{
			if((pu1DataBuf[1]>pu1DataBuf[2])&&((pu1DataBuf[1]-pu1DataBuf[2])==1))
			{
				if((pu1DataBuf[2]>pu1DataBuf[3])&&((pu1DataBuf[2]-pu1DataBuf[3])==1))
				{
					if((pu1DataBuf[3]>pu1DataBuf[4])&&((pu1DataBuf[3]-pu1DataBuf[4])==1))
					{
						if((pu1DataBuf[4]>pu1DataBuf[5])&&((pu1DataBuf[4]-pu1DataBuf[5])==1))
						{
							return 1;
						}
					}
				}
			}
		}
	}
	else
	{
		if((pu1DataBuf[1]-pu1DataBuf[0])==1)
		{
			if((pu1DataBuf[1]<pu1DataBuf[2])&&((pu1DataBuf[2]-pu1DataBuf[1])==1))
			{
				if((pu1DataBuf[2]<pu1DataBuf[3])&&((pu1DataBuf[3]-pu1DataBuf[2])==1))
				{
					if((pu1DataBuf[3]<pu1DataBuf[4])&&((pu1DataBuf[4]-pu1DataBuf[3])==1))
					{
						if((pu1DataBuf[4]<pu1DataBuf[5])&&((pu1DataBuf[5]-pu1DataBuf[4])==1))
						{
							return 1;
						}
					}
				}
			}
		}
	}
	#endif
	return 0;


}
#endif

void GetTimeFactor(u1 *pu1Time)
{
	u4 u4Minite;
	//u2 u2time;

	//u4Minite = (gTimer_Count_Base + TBC_COUNT_VALUE)/60;
	u4Minite = (gTimer_Count_Base + Base_Time())/TIMESTEP;		//60

	#if(GMT)
	u2time = 8*60*60/TIMESTEP;
	u4Minite -= u2time;
	#endif
	
	gToken_Time1 = u4Minite;
	
	memset(pu1Time, 0x00, 8);
	pu1Time[0x07] = (u1)u4Minite;
	u4Minite >>= 0x08;
	pu1Time[0x06] = (u1)u4Minite;
	u4Minite >>= 0x08;
	pu1Time[0x05] = (u1)u4Minite;
	u4Minite >>= 0x08;
	pu1Time[0x04] = (u1)u4Minite;
	u4Minite >>= 0x08;
}

#if 0
// ��pu1Inputת���ɿ���ʾ������
// ÿ���ֽ�ת��2�ֽڵ�4�ֽ�, ÿ�����ֽ�,���С��0x0A, ת��1�ֽ�, �������0x09, ת��2�ֽ�
// ����, ���ȵ�, �����һ�����ֽھʹ���9, ֱ�Ӱ�һ���ֽ�ת����3�ֽ�, ��0xFFת��255(0x32, 0x35, 0x35)
// ����ֻ��������HASH����
void Byte2Num(u1* pu1OutPut, u2 u2OutPutLen, const u1* pu1Input, u1 u1InputLen)
{
	u1 u1Tmp;
	u1 u1Tmp2;
	u1 u1For;
	u2 u2Index;
	
	u2Index= 0x00;
	for ( u1For=0x00; u1For<u1InputLen; u1For++ )
	{
		u1Tmp = (pu1Input[u1For]>>0x04);
		if ( u1Tmp < 0x0A )
		{
			pu1OutPut[u2Index++] = 0x30 + u1Tmp;
		}
		else
		{
			// ��һ�����ֽ�>9, �������ֽ�ת����3�ֽ�
			u1Tmp2 = pu1Input[u1For];
			pu1OutPut[u2Index++] = 0x30 + u1Tmp2/100;
			if ( u2Index == u2OutPutLen )
			{
				return;
			}
			u1Tmp = u1Tmp2/10;
			pu1OutPut[u2Index++] = 0x30 + u1Tmp%10;
			if ( u2Index == u2OutPutLen )
			{
				return;
			}
			pu1OutPut[u2Index++] = 0x30 + u1Tmp2%10;
			if ( u2Index == u2OutPutLen )
			{
				return;
			}
			continue;
		}
		if ( u2Index == u2OutPutLen )
		{
			return;
		}
		u1Tmp = (pu1Input[u1For]&0x0F);
		if ( u1Tmp < 0x0A )
		{
			pu1OutPut[u2Index++] = 0x30 + u1Tmp;
		}
		else
		{
			pu1OutPut[u2Index++] = 0x30 + (u1Tmp - 0x09);
			if ( u2Index == u2OutPutLen )
			{
				return;
			}
			pu1OutPut[u2Index++] = 0x30 + 0x09;
		}
		if ( u2Index == u2OutPutLen )
		{
			return;
		}
	}
}
#endif

///////////////////////////////////////////////////
// ���ܣ���HMAC���еõ�ָ�����ȵ�����, ���ܱ�׼
// szOTP:		���������OTP
// dwHOTPLen��	���������ָ��������ĳ���
// pbMAC:		���������HMAC��
// dwMACLen��	���������pbMAC�ĳ��ȣ�Ҫ��Ϊ
// ����ֵ��		��������:FALSE���ɹ���TRUE
///////////////////////////////////////////////////
/*
void SubstractHotp(u1* pszOtp, u1 u1OTPLen, u1* pu1MAC, u1 u1MACLen)
{
	u1 				i;
	u4	xdata		u4Mode;
	u4	xdata		u4S1,u4S2,u4S3,u4S4,u4S5,u4S6,u4S7,u4S8;
	u4	xdata		u4S;
	u4	xdata		u4OD;
	u4	xdata		u4Index;
	u4	xdata		u4Tmp1,u4Tmp2,u4Tmp3,u4Tmp4;
	
	if ( 0x20 != u1MACLen )
	{
		return;
	}

	u4Tmp1 = ((u4)(pu1MAC[0x00])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x01])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x02])<<0x08); u4Tmp4 = pu1MAC[0x03]; 
	u4S1 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;
	u4Tmp1 = ((u4)(pu1MAC[0x04])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x05])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x06])<<0x08); u4Tmp4 = pu1MAC[0x07];
	u4S2 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;
	u4Tmp1 = ((u4)(pu1MAC[0x08])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x09])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x0A])<<0x08); u4Tmp4 = pu1MAC[0x0B];
	u4S3 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;
	u4Tmp1 = ((u4)(pu1MAC[0x0C])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x0D])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x0E])<<0x08); u4Tmp4 = pu1MAC[0x0F];
	u4S4 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;
	u4Tmp1 = ((u4)(pu1MAC[0x10])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x11])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x12])<<0x08); u4Tmp4 = pu1MAC[0x13];
	u4S5 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;
	u4Tmp1 = ((u4)(pu1MAC[0x14])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x15])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x16])<<0x08); u4Tmp4 = pu1MAC[0x17];
	u4S6 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;
	u4Tmp1 = ((u4)(pu1MAC[0x18])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x19])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x1A])<<0x08); u4Tmp4 = pu1MAC[0x1B];
	u4S7 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;
	u4Tmp1 = ((u4)(pu1MAC[0x1C])<<0x18); u4Tmp2 = ((u4)(pu1MAC[0x1D])<<0x10); u4Tmp3 = ((u4)(pu1MAC[0x1E])<<0x08); u4Tmp4 = pu1MAC[0x1F];
	u4S8 = u4Tmp1 | u4Tmp2 | u4Tmp3 | u4Tmp4;


	u4S = u4S1;
	u4S += u4S2;
	u4S += u4S3;
	u4S += u4S4;
	u4S += u4S5;
	u4S += u4S6;
	u4S += u4S7;
	u4S += u4S8;
	u4OD = u4S;
	
	u4Mode = 1;
	for ( i = 1; i <= u1OTPLen; i++)
	{
		u4Mode *= 10;
	}
	u4OD %= u4Mode;

	for ( i = 0; i < u1OTPLen; i++)
	{
		pszOtp[i] = '0';
	}
	pszOtp += (u1OTPLen - 0x01);
	u4Mode = 10;
	while ( u1OTPLen )
	{
		u4Index = (u4OD%u4Mode);
		u4OD -= u4Index;
		u4Index /= (u4Mode/10);
		u4Mode *= 10;
		*pszOtp = 0x30 + (u1)u4Index;
		u1OTPLen--;
		pszOtp--;
	}
}
*/

///////////////////////////////////////////////////
// ���ܣ���HMAC���еõ�ָ�����ȵ�����
// pbMAC:		���������HMAC��
// dwMACLen��	���������pbMAC�ĳ��ȣ�Ҫ��Ϊ
// dwHOTPLen��	���������ָ��������ĳ���
// szOTP:		���������OTP
// ����ֵ��		��������:FALSE���ɹ���TRUE
///////////////////////////////////////////////////
BOOL ExtractHOTP(UINT8* pu1MAC, UINT32 dwMACLen, UINT8* pszOtp, UINT32 dwOTPLen)
{
	UINT8	    i;
	UINT32		dwData;
	UINT8		index;
	//UINT32	    dwMode;
	//UINT32		nLen;
	UINT32	u4Mode;
	UINT32   u4Index;
	//UINT8		szTemp[OTP_MAX_LEN+1];

	if ( dwMACLen != OTP_HASH_LEN_SHA1)
	{
		return FALSE;
	}
	if ( dwOTPLen < OTP_MIN_LEN )
	{
		dwOTPLen = OTP_MIN_LEN;
	}
	if ( dwOTPLen > OTP_MAX_LEN)
	{
		dwOTPLen = OTP_MAX_LEN;
	}
// 	BYTE pbMAC[32] = {128,233,57,17,153,230,80,173,84,74,244,57,140,69,150,13,172,170,113,121,83,205,51,192,191,147,233,228,103,217,69,225};
// 	dwMACLen = 32;
// 	dwOTPLen = 8;
	index = pu1MAC[dwMACLen-1];
	index &= 0x0F;
	
	dwData = pu1MAC[index];
	dwData &= 0x7F;
	dwData <<= 0x08;
	dwData |= pu1MAC[index+1];
	dwData <<= 0x08;
	dwData |= pu1MAC[index+2];
	dwData <<= 0x08;
	dwData |= pu1MAC[index+3];

	#if 0
	dwMode = 1;
	for ( i = 1; i <= dwOTPLen; i++)
	{
		dwMode *= 10;
	}
	dwData %= dwMode;

	for ( i = 0; i < dwOTPLen; i++)
	{
		pszOtp[i] = '0';
	}
	
	//nLen = strlen(szTemp);
	//memcpy(&pszOtp[dwOTPLen-nLen], szTemp, nLen+1);
	#endif
	u4Mode = 1;
	for ( i = 1; i <= dwOTPLen; i++)
	{
		u4Mode *= 10;
	}
	dwData %= u4Mode;

	for ( i = 0; i < dwOTPLen; i++)
	{
		pszOtp[i] = '0';
	}
	pszOtp += (dwOTPLen - 0x01);
	u4Mode = 10;
	while ( dwOTPLen )
	{
		u4Index = (dwData%u4Mode);
		dwData -= u4Index;
		u4Index /= (u4Mode/10);
		u4Mode *= 10;
		*pszOtp = 0x30 + (u1)u4Index;
		dwOTPLen--;
		pszOtp--;
	}

	return TRUE;
}

///////////////////////////////////////////////////
// ���ܣ�Otp���㶯̬����
// pu1Time:			���������ʱ������[8]
// u1TimeLen		���������ʱ�����ӳ��ȣ�ĿǰΪ8�ֽ�
// pu1Seed:			���������Otp���ӣ�64�ֽ��������SM3ֵ
// u1SeedSize		���������Otp���ӳ��ȣ�ĿǰΪ32�ֽ�
// pu1Question:		�����������ս�룬����Ǽ��㼤��׶ε���֤�룬������Otp���кź�6λ������303030303031
// u1QuestionLen:	�����������ս�볤��
// pu1Ocra:			�����������̬����
// pu1OcraLen:		�����������̬����ĳ��ȣ�ĿǰΪ8�ֽ�
// ����ֵ��			0�ɹ�������ʧ��
///////////////////////////////////////////////////

//���������Ҫ���ַ���ת����ʮ��������
u1 GenOtpOcra(u1* pu1Time,u1 u1TimeLen,u1* pu1Seed,u1 u1SeedSize,u1* pu1Question,u1 u1QuestionLen,u1* pu1Ocra,u1* pu1OcraLen )
{
	u1 u1Tmp;
	u1 *pu1Tmp; //seed 20bytes + time 8bytes + ��ս�������22bytes = 50
	//u1 u1SM3HashOutput[32];		//��оƬhash ����������������ͬһ������
	//u2 out[32];

	//u1 u1Hmac_Sha1Output[20];		//��оƬhash ����������������ͬһ������
	u1 out[20];
	u2 u2Len;
	
	memset(out,0x00,20);

	pu1Tmp = g_u1OtpInput; //T8��stack����������ȫ�ֱ���RAM������
	if ( 0x08 != u1TimeLen )
	{
		return 0xFF;
	}			
		
    if ( u1QuestionLen < 0x08 )
    {
        memset(pu1Question + u1QuestionLen, 0x00, 0x08 - u1QuestionLen);
        u1QuestionLen = 0x08;
    }
	
	u1Tmp = 0;
	/*
	memcpy(pu1Tmp + u1Tmp, pu1Seed, u1SeedSize);
	u1Tmp += u1SeedSize;
	*/
	memcpy(pu1Tmp + u1Tmp, pu1Time, u1TimeLen);
	u1Tmp += u1TimeLen;
	//memcpy(pu1Tmp + u1Tmp, pu1Question, u1QuestionLen);			//test20160718
	//u1Tmp += u1QuestionLen;	

	
	//u1Tmp = SM3_Hash(pu1Tmp, u1Tmp, out); 
	//HMAC_SHA1(pu1Seed, u1SeedSize, pu1Tmp, u1Tmp, out);
	
	HmacEx(0xc1, pu1Seed, u1SeedSize, pu1Tmp, u1Tmp, out, &u2Len);		//test
	//while(1);
	//memcpy(u1Hmac_Sha1Output,out,20);
	
	u1Tmp= 20;
	// //��������ת��
	*pu1OcraLen = 8;
	//SubstractHotp(pu1Ocra, *pu1OcraLen, u1SM3HashOutput, u1Tmp);  //������Ҫ�޸�
	ExtractHOTP(out, u1Tmp, pu1Ocra, *pu1OcraLen);

	return 0;
}

// ����ʱ�����
// u1CalFlg: ˫���Ǽ�, �����Ǽ�
void CalTime(u4 *pu4OutTime1, u4 *pu4OutTime2, u4 u4Time1, u4 u4Time2, u1 u1CalFlg)
{
	if ( 0x01&u1CalFlg )
	{
		if ( 0x00 == u4Time2 )
		{
			u4Time1 -= 0x01;
			u4Time2 = 0xFFFFFFFF;
		}
		else
		{
			u4Time2 -= 0x01;
		}
	}
	else
	{
		if ( 0xFFFFFFFF == u4Time2 )
		{
			u4Time1 += 0x01;
			u4Time2 = 0x00;
		}
		else
		{
			u4Time2 += 0x01;
		}
	}
	*pu4OutTime1 = u4Time1;
	*pu4OutTime2 = u4Time2;
	
}
long BYTE2LONG(u1* pu1Data)
{
	long	lResult;
		
        lResult = *(long*)pu1Data;
	return lResult;
}

#define LONG2BYTE(pu1Data,u4Data)	((u1*)(pu1Data))[0] = (u1)((u4Data)>>24);((u1*)(pu1Data))[1] = (u1)((u4Data)>>16);((u1*)pu1Data)[2] = (u1)((u4Data)>>8);((u1*)pu1Data)[3] = (u1)((u4Data))

//////////////////////////////////////////////////////////////////////////
// ��������:
//	��֤������
// ����˵��:
// pu1Time:			���������ʱ������[8]
// u1TimeLen		���������ʱ�����ӳ��ȣ�ĿǰΪ8�ֽ�
// pu1Seed:			���������Otp���ӣ�64�ֽ��������SM3ֵ
// u1SeedSize		���������Otp���ӳ��ȣ�ĿǰΪ32�ֽ�
// pu1Question:		�����������ս��
// u1QuestionLen:	�����������ս�볤��
// pu1Ocra:			�����������̬����
// pu1OcraLen:		�����������̬����ĳ���
//  u1Window:       ���������У�鴰��, 00-С����, 01-�д���, 02-�󴰿�
// ����ֵ:
//	0xFF:			��֤ʧ��
//	����:			��֤�ɹ�, ����ƫ��
//////////////////////////////////////////////////////////////////////////
u1 OtpActiveVerify(u1* pu1Time,u1 u1TimeLen,u1* pu1Seed,u1 u1SeedSize,u1* pu1Question,u1 u1QuestionLen,u1* pu1Ocra,u1 u1OcraLen, u1 u1Window )
{
	u1			pu1InputOTP[0x08];
	u1			*pu1T;
	u1			pu1Substract[0x20];
	u4			u4Time1;
	u4			u4Time2;
	u4			u4Time1_Dec;
	u4			u4Time2_Dec;
	u4			u4Time1_Add;
	u4			u4Time2_Add;
	u1			u1Index;
	u1			u1Tmp;
	u1			u1OtpDataLen;
	u1			u1NumAdd;
	u1			u1NumDec;
	//u1			*pu1OtpData;//[0x80];
	u1			pu1OtpTmp[0x20];
	u1  			out[32];
	u2 			u2Len;

	//pu1OtpData =g_u1OtpInput;
	// ���úø���������ֵ
	memset(g_u1OtpInput, 0x00, 80);
	/*
	memcpy(g_u1OtpInput, pu1Seed, u1SeedSize);  // SEED
	memxor(g_u1OtpInput, NULL, 0x10);				//OTP����׶Σ���������ǰ��ҪSEEDǰ�벿��ȡ��
	u1OtpDataLen = u1SeedSize;
	*/
	u1OtpDataLen = 0;
	memcpy(g_u1OtpInput+u1OtpDataLen, pu1Time, u1TimeLen);  // T
	pu1T = g_u1OtpInput+u1OtpDataLen;
	u1OtpDataLen += u1TimeLen;
	memcpy(g_u1OtpInput+u1OtpDataLen, pu1Question, u1QuestionLen);  // Q
	u1OtpDataLen += u1QuestionLen;
	memcpy(pu1InputOTP, pu1Ocra, u1OcraLen);

	// �Ȳ��Ե�ǰʱ��
	u4Time1_Dec = BYTE2LONG(pu1T);
	u4Time2_Dec = BYTE2LONG((pu1T + 0x04));
	//u4Time1_Dec = BYTE2LONG(pu1Time);
	//u4Time2_Dec = BYTE2LONG((pu1Time + 0x04));
	u4Time1_Add = u4Time1_Dec;
	u4Time2_Add = u4Time2_Dec;

	if ( OTP_SMALL_WINDOW == u1Window )
	{
		// С����
		// ǰ1��1
		u1Window = 0x03;
	}
	else if ( OTP_MIDDLE_WINDOW == u1Window  )
	{
		// �д���
		// ǰ4��4
		u1Window = 0x09;
	}
	else
	{
		// �󴰿�
		// ǰ8��8
		u1Window = 0x11;

	}
	u1NumAdd = 0x00;
	u1NumDec = 0x80;
	for ( u1Index = 0x00; u1Index < u1Window; u1Index++ )
	{
		if ( 0x00 == u1Index )
		{
			// ��ǰʱ��
			u4Time1 = u4Time1_Dec;
			u4Time2 = u4Time2_Dec;
		}
		else if ( 0x01 & u1Index )
		{
			CalTime(&u4Time1, &u4Time2, u4Time1_Dec, u4Time2_Dec, u1Index);
			u4Time1_Dec = u4Time1;
			u4Time2_Dec = u4Time2;
			u1NumDec++;
		}
		else
		{
			CalTime(&u4Time1, &u4Time2, u4Time1_Add, u4Time2_Add, u1Index);
			u4Time1_Add = u4Time1;
			u4Time2_Add = u4Time2;
			u1NumAdd++;
		}

		LONG2BYTE(pu1T, u4Time1);
		LONG2BYTE((pu1T + 0x04), u4Time2);
		//LONG2BYTE(pu1Time, u4Time1);
		//LONG2BYTE((pu1Time + 0x04), u4Time2);
		//memcpy(g_u1OtpInput+u1OtpDataLen, pu1Time, u1TimeLen);  

		//u1Tmp = SM3_Hash(g_u1OtpInput,u1OtpDataLen,out);		
        	//HMAC_SHA1(pu1Seed, u1SeedSize, g_u1OtpInput, u1OtpDataLen, out);
		HmacEx(0xc1, pu1Seed, u1SeedSize, g_u1OtpInput, u1OtpDataLen, out, &u2Len);		//test
		memcpy(pu1OtpTmp,out,20);

		
		u1Tmp = 20;	//text
		//SubstractHotp(pu1Substract, u1OcraLen, pu1OtpTmp, u1Tmp); //������Ҫ�޸�
		ExtractHOTP(pu1OtpTmp, u1Tmp, pu1Substract, u1OcraLen);
		
		if ( 0x00 == memcmp(pu1Substract, pu1InputOTP, u1OcraLen) )
		{
			if ( 0x00 == u1Index )
			{
				return 0x00;
			}
			else if ( 0x01 & u1Index )
			{
				return u1NumDec;
			}
			else
			{
				return u1NumAdd;
			}
		}
	}
	return 0xFF;
}

u1 CosOperation(u1 Mode,u1 *pu1DataBuf)
{
	//u1 u1Len;
	u1 u1Status;
	//u1 u1ChalLen;
	u1 u1Rsp;
	u1 pu1MacKey[16];
	//u1 pu1Q[6];
	u1 pu1Seed[SEED_LEN];
    u1 i;
	//u1 j;
	u1 u1OLen;
	u1 pu1TimeFactor[8];
	//u1 pu1Buff[9];
	u1 pu1IV[16];
	u2 u2Len;

	//u1 out[36];
	

	vScu_SetSysClkOsc2M();
    switch( Mode )
	{
		case OP_SN:
			{
				memset(g_u1SN,0x00,g_SNLen);
				memcpy(g_u1SN,pu1DataBuf,g_SNLen);
				memcpy(g_u1Key,pu1DataBuf+g_SNLen+TIME_LEN,KEY_LEN);
				
				for(i=0;i<KEY_LEN;i++) pu1MacKey[i] =g_u1PriKey[i];
				//u2Len =KEY_LEN;
				SM4_Init(pu1MacKey);
				SM4_Crypto(g_u1Key,KEY_LEN,0x01,0x00,NULL,g_u1Key);		//���� u1Key
				u1Rsp = OTPSECU_OP_OK;
				break;
			}
		case OP_MACKEY_SEEDKEY:
			{
			
				memset(g_u1MacKey,0x00,MACKEY_LEN);
				//memset(g_u1SeedKey,0x00,SEEDKEY_LEN);
				memset(pu1Seed,0x00, SEED_LEN);
				memcpy(g_u1MacKey,pu1DataBuf,MACKEY_LEN);
				//memcpy(g_u1SeedKey,pu1DataBuf+MACKEY_LEN,SEEDKEY_LEN);
				memcpy(pu1Seed,pu1DataBuf+MACKEY_LEN,20);
				for(i=0;i<KEY_LEN;i++) pu1MacKey[i] =g_u1Key[i];
				//u2Len =MACKEY_LEN;
				SM4_Init(pu1MacKey);
				SM4_Crypto(g_u1MacKey,MACKEY_LEN,0x01,0x00,NULL,g_u1MacKey);		//���� mac_Key
				//u2Len =SEEDKEY_LEN;
				
				//for(i=0;i<KEY_LEN;i++) pu1MacKey[i] =g_u1Key[i];
				//SM4_Init(pu1MacKey);
				//SM4_Crypto(g_u1SeedKey,MACKEY_LEN,0x01,0x00,NULL,g_u1SeedKey);		//���� seed_Key

				u2Len = 32;
				for(i=0;i<16;i++) pu1MacKey[i] = g_u1Key[i];
				SM4_Init(pu1MacKey);
				SM4_Crypto(pu1Seed,u2Len,0x00,0x00,NULL,gUserInfo);		//jia mi seed
				
				g_AutoUnlockCnt = 0;
				gPinErr_Count = 0;
				gUnlockPinErr_Count = 0;
				gPinErr_Time = 0;
				u1Rsp = OTPSECU_OP_OK;
				memset(pu1Seed,0x00,SEED_LEN);
			}
			break;
			#if 0
		case OP_GEN_SEED:
			{
				memset(pu1Seed,0x00, SEED_LEN);	
				memcpy(out,g_u1SN, g_SNLen);
				memcpy(out+g_SNLen, g_u1SeedKey, SEEDKEY_LEN);
				SHA1Data(pu1Seed, out, g_SNLen+SEEDKEY_LEN);
				//while(1);
				//#if(DEBUG)
				//memset(pu1Seed,0x00, SEED_LEN);
				//for(i=0; i<20; i++)
				//{
				//	pu1Seed[i] = 0x30+((i+1)%10);
				//}
				//#endif
				
				u2Len = 32;
				for(i=0;i<16;i++) pu1MacKey[i] = g_u1Key[i];
				SM4_Init(pu1MacKey);
				SM4_Crypto(pu1Seed,u2Len,0x00,0x00,NULL,gUserInfo);	
				u1Rsp = OTPSECU_OP_OK;
				memset(pu1Seed,0x00,SEED_LEN);
								
			}
			break;
			#endif
		case OP_TIME_TOKEN:
			{
				memset(pu1DataBuf,0x00,6);
				GetTimeFactor(pu1TimeFactor);
				
				memcpy(pu1Seed,gUserInfo,SEED_LEN);
				
				for(i=0;i<KEY_LEN;i++) pu1MacKey[i] =g_u1Key[i];
				SM4_Init(pu1MacKey);
				SM4_Crypto(pu1Seed,SEED_LEN,0x01,0x00,NULL,pu1Seed);		//���� seed

				u1Status =GenOtpOcra(pu1TimeFactor,TIME_LEN,pu1Seed,20,pu1DataBuf,6,pu1IV,&u1OLen);
				//while(1);
				memcpy(pu1DataBuf,pu1IV,u1OLen);
				memset(pu1Seed,0x00,SEED_LEN);	
				if ( 0x00==u1Status )
				{
					//for ( u1OLen=0; u1OLen<TIME_TOKEN_LEN; u1OLen++) pu1DataBuf[u1OLen] -= 0x30;		//��ʾ�ľ���ASCLL��
					u1Rsp = OTPSECU_OP_OK;
				}
				else
				{
					u1Rsp = OTPSECU_OP_ERR;
				}
				break;
			}
			
			default:
			u1Rsp = OTPSECU_OP_ERR;
			break;
	}
	
	vScu_SetSysClk32K();
	return u1Rsp;
}
