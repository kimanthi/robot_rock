#include "posapi.h"
#include "string.h"
/********************** Internal macros declaration ************************/
#define OK 0
#define FAIL 1
#define Original_Code 0
#define WNET_MODE_B  1
#define WNET_MODE_CG 2
#define WNET_MODE_CC 3
/********************** Internal functions declaration *********************/
int WNetSetMode(unsigned char mode);
int WirelessDial(uchar *sAPN,uchar *sUser,uchar *sPwd);
/********************** external functions declaration *********************/
extern char *strstr(const char *, const char *);

unsigned char AppWaitKey(int wsec)
{
  unsigned char ucKeyval;

  TimerSet(0,(ushort)(wsec*10));
  ucKeyval=NOKEY;
  while (TimerCheck(0))
  {
    if (kbhit()==OK)
    {
      ucKeyval=getkey();
      break;
    }
  }
  return ucKeyval;
}

int pax_connect(void)
{
  int	              ii;
  unsigned char     sAPN[100],sUser[100],sPwd[100];
  unsigned char     sIP[24];
  ushort            ucPort;
  unsigned char     ucTbuf[104];
  int               iRet,iSize,iTimeoutNum;
  unsigned char     ucKeyVal;

  //SystemInit();
  iSize=200;
  strcpy(sAPN,"claro.com.br");
  strcpy(sUser,"claro.com.br");
  strcpy(sPwd,"claro.com.br");
  strcpy(sIP,"177.106.92.162");
  ucPort=8000;

  ScrCls();
  printf("\nWait WNET INIT");

  iRet=WlInit(NULL);
  if (iRet)
  {
    printf("\nWNET INIT %d  ", iRet);
  }

  ucKeyVal = 0;
  while (1)
  {
    ScrCls();
    printf("\nALPHA:  OnOff");
    printf("\nMENU:   Logout");
    printf("\nFUN:    AT Mode");
    printf("\nKEY 1:  SETUP");
    printf("\nCANCEL: EXIT");
    printf("\nOTHER:  TEST");

    if (ucKeyVal!=0)
    {
      ucKeyVal = getkey();
    }
    else
    {
      ucKeyVal = KEY1;
    }

    ScrCls();
    if ((ucKeyVal==KEYMENU) || (ucKeyVal==KEYCANCEL))
    {
      Lcdprintf("LOGOUT...\n");
      DelayMs(1000);
      WlPppLogout();
      while (WlPppCheck()==1)
      {
      }
      if (ucKeyVal==KEYCANCEL)
      {
        return 0;
      }
    }
    else if (ucKeyVal==KEYALPHA)
    {
      Lcdprintf("Power OFF...\n");
      WlSwitchPower(0);
      DelayMs(3000);
      Lcdprintf("ON, WAIT...\n");
      WlSwitchPower(1);
      DelayMs(10*1000);
    }
    else if (ucKeyVal==KEYFN)
    {
      Lcdprintf("AT MODE\n");
      WlPppLogout();
      while (WlPppCheck()==1)
      {
      }
      WlOpenPort();
      DelayMs(100);
      WlSendCmd(NULL,NULL,0,0,0);
    }
    else if (ucKeyVal==KEY1)
    {
      ScrCls();ScrPrint(0,0,1,"ENTER APN:");ScrGotoxy(0,6);
      strcpy(ucTbuf,sAPN);
      iRet=GetString(ucTbuf,0xf5,1,32);
      if (iRet==0)
      {
        memcpy(sAPN,ucTbuf+1,ucTbuf[0]);
        sAPN[ucTbuf[0]]=0;
      }
      else if (iRet==0xff)
      {
        continue;
      }

      ScrCls();ScrPrint(0,0,1,"ENTER Name:");ScrGotoxy(0,6);
      strcpy(ucTbuf,sUser);
      iRet=GetString(ucTbuf,0xf5,0,32);
      if ((iRet==0))
      {
        memcpy(sUser,ucTbuf+1,ucTbuf[0]);
        sUser[ucTbuf[0]]=0;
      }
      else if (iRet==0xff)
      {
        continue;
      }
      if (iRet==0x0d)
      {
        sUser[0]=0;
      }

      ScrCls();ScrPrint(0,0,1,"ENTER Pwd:");ScrGotoxy(0,6);
      strcpy(ucTbuf,sPwd);
      iRet=GetString(ucTbuf,0xf5,0,32);
      if ((iRet==0)||(iRet==0x0d))
      {
        memcpy(sPwd,ucTbuf+1,ucTbuf[0]);
        sPwd[ucTbuf[0]]=0;
      }
      else if (iRet==0xff)
      {
        continue;
      }
      if (iRet==0x0d)
      {
        sPwd[0]=0;
      }

      ScrCls();ScrPrint(0,0,1,"ENTER IP:");ScrGotoxy(0,6);
      strcpy(ucTbuf,sIP);
      iRet=GetString(ucTbuf,0xf5,7,16);
      if ((iRet==0)||(iRet==0x0d))
      {
        memcpy(sIP,ucTbuf+1,ucTbuf[0]);
        sIP[ucTbuf[0]]=0;
      }
      else if (iRet==0xff)
      {
        continue;
      }

      ScrCls();ScrPrint(0,0,1,"ENTER Port:");ScrGotoxy(0,6);
      sprintf(ucTbuf,"%u",ucPort);
      iRet=GetString(ucTbuf,0xf5,0,5);
      if ((iRet==0)||(iRet==0x0d))
      {
        ucPort=atoi(&ucTbuf[1]);
      }
      else if (iRet==0xff)
      {
        continue;
      }
    }
    else
    {
      ScrFontSet(0);
      ScrCls();
      ScrPrint(0,0,0,"Logon %s %s %s",sAPN,sUser,sPwd);
      //拨号开始
      iRet = WirelessDial(sAPN,sUser,sPwd);
      ScrClrLine(2, 7);
      ScrPrint(0,2,0,"PPP Logon:%d",iRet);

      if (iRet!=0) 
      {
        //提示错误，并返回ERR_CONNECT
        ScrCls();
        Lcdprintf("LOGOUT...\n");
        while (1)
        {
          if (kbhit()==OK)
          {
            //按键退出
            if (getkey()==KEYCANCEL)
            {
              return 0;
            }
          }
        }
      }			
      //登录时间处理
      //以下为IP操作函数
      for (ii=0; ii<3; ii++)
      {
        int    iNCRet,iTemp,jj,iNSRet;
        uchar  ucTmpSend[300],ucTmpRcv[102400];

        struct net_sockaddr server_addr;

        //发送数据长度
        iNSRet=NetSocket(NET_AF_INET, NET_SOCK_STREAM, 0);
        if (iNSRet < 0)
        {
          ScrPrint(0,3,0,"NetSocket:%d", iNSRet);
          AppWaitKey(30);
          break;
        }

        SockAddrSet(&server_addr, sIP, ucPort);
        //设置55秒timeout
        Netioctl(iNSRet, CMD_TO_SET, 55000);
        iNCRet=NetConnect(iNSRet,&server_addr,sizeof(server_addr));
        ScrPrint(0,3,0,"TCP OPEN %s:%u =%d",sIP,ucPort,iNCRet);

        if (iNCRet<0)
        {
          ScrPrint(0,3,0,"iNCRet<0");
          NetCloseSocket(iNSRet);
          AppWaitKey(30);
          break;
        }

        memset(ucTmpSend, 0, sizeof(ucTmpSend));
        for (jj=0;jj<iSize;jj++) ucTmpSend[jj]=(unsigned char )(jj);
        iNCRet=NetSend(iNSRet,ucTmpSend,iSize,0);
        ScrPrint(0,5,0,"TCP Send:%d ",iNCRet);

        if (iNCRet<0)
        {
          NetCloseSocket(iNSRet);
          AppWaitKey(30);
          break;
        }
        iTemp = 0;
        iTimeoutNum = 0;
        memset(ucTmpRcv, 0, sizeof(ucTmpRcv));

        while (1)
        {
          iNCRet=NetRecv(iNSRet,ucTmpRcv+iTemp,10*1000,0);
          if (iNCRet<0)
          {
            if (iNCRet==-13)//针对超时情况进行处理
            {
              iTimeoutNum++;
              if (iTimeoutNum<3)
              {
                continue;
              }
              else
              {
                break;
              }
            }
            else//-4或其它值，则直接退出
            {
              break;
            }

            break;
          }


          iTemp+=iNCRet;
          if (iTemp>=iSize)break;

          if (kbhit()==0)
          {
            if (getkey()==KEYCANCEL) break;
          }
        }
        ScrPrint(0,6,0,"TCP Recv:%d Rlen:%d ",iNCRet,iTemp);
        NetCloseSocket(iNSRet);
        WlPppLogout();
        break;
      }
      //以上为IP操作函数
      ScrPrint(0,7,0x80," ANY KEY CONTINUE");
      kbflush();getkey();
    }
  }
  return 0;
}

//循环3次WlPppLogin拨号，如果3次都失败的话，则对模块进行上下电处理
int WirelessDial(uchar *sAPN,uchar *sUser,uchar *sPwd)
{
  int   ii,iRet,iTimeoutNum;

  iTimeoutNum = 0;
  do {
    iTimeoutNum++;
    for (ii=0;ii<3;ii++)
    {
      //GPRS模块，WlPppLogin的AliveInterval参数可以置为0.
      WlPppLogin(sAPN,sUser,sPwd,0xff,0,0);
      //针对Q24模 块的特点，在拨号后，需要等待2秒
      DelayMs(2000);

      while (WlPppCheck()==1)
      {
        iRet = FAIL;
        if (kbhit()==OK)
        {
          if (getkey()==KEYCANCEL)
          {
            break;
          }
        }
        DelayMs(200);
        continue;
      }
      if (WlPppCheck()==0)
      {
        iRet = OK;
        break;
      }
      ScrPrint(0,2,0,"PPP Logon time:%d",ii);
    }
    if (iRet !=0 && iTimeoutNum ==1)
    {
      // 失败三次，进行上下电处理
      ScrPrint(0,3,0,"WlSwitchPower!");
      WlSwitchPower(0);
      DelayMs(10*1000);
      WlSwitchPower(1);
    }
  }
  // 循环退出条件，拨号成功或者已经尝试2次
  while (iRet != 0 && iTimeoutNum == 1);
  return iRet;
}

int WNetSetMode(unsigned char mode)
{
  char   rsp[512];
  int    ii,wliRet;

  if (WlPppCheck()==0)
  {
    //ppp在线需要退出ppp
    WlPppLogout();
    while (WlPppCheck()==1)
    {

    }
  }
  WlInit(NULL);
  WlOpenPort();
  memset(rsp,0,sizeof(rsp));
  WlSendCmd("AT+CGCLASS?\r",(unsigned char *)rsp,sizeof(rsp),10*1000,20);

  if (strstr(rsp,"+CGCLASS:"))
  {
    if (mode==WNET_MODE_CG)
    {
      if (strstr(rsp,"\"CG\""))
      {
        //本身已经设置成数据模式，直接返回
        return 0;
      }
    }
    else if (mode==WNET_MODE_CC)
    {
      if (strstr(rsp,"\"CC\""))
      {
        //本身已经设置好
        return 0;
      }
    }
    else 
    {
      if (strstr(rsp,"\"B\""))
      {
        //本身已经设置好
        return 0;
      }
    }
  }
  WlSwitchPower(0); //下电
  DelayMs(1000);
  WlSwitchPower(1); //上电，monitor下自动等待8秒才会上电

  for (ii=0;ii<100;ii++)
  {
    memset(rsp,0,sizeof(rsp));
    wliRet=WlSendCmd("ATE0\r",rsp,sizeof(rsp),500,50);
    if ((wliRet==0)&&(strstr(rsp,"OK")))
    {
      break;
    }
  }
  memset(rsp,0,sizeof(rsp));

  if (mode==WNET_MODE_CG)
  {
    wliRet=WlSendCmd("AT+CGCLASS=\"CG\"\r",rsp,sizeof(rsp),10*1000,50);
  }
  else if (mode==WNET_MODE_CC)
  {
    wliRet=WlSendCmd("AT+CGCLASS=\"CC\"\r",rsp,sizeof(rsp),10*1000,50);
  }
  else 
  {
    wliRet=WlSendCmd("AT+CGCLASS=\"B\"\r",rsp,sizeof(rsp),10*1000,50);
  }

  if ((wliRet==0)&&(strstr(rsp,"OK")))
  {
    wliRet=0;
  }
  else wliRet=-2;
  WlSendCmd("AT+CMEE=1\r",rsp,sizeof(rsp),10*1000,50);
  return wliRet;
}

//end