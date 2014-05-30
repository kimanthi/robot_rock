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

  // Attach Start
  iSize=200;
  //Parameters
  strcpy(sAPN, "claro.com.br");
  strcpy(sUser,"claro.com.br");
  strcpy(sPwd, "claro.com.br");
  strcpy(sIP,  "177.106.122.121");
  ucPort=8000;

  ScrCls();
  printf("\nWait WNET INIT");
  iRet=WlInit(NULL);

  if (iRet)
  {
    printf("\nWNET INIT %d  ", iRet);
  }
  DelayMs(2000);

  ScrFontSet(0);
  printf("\nLogon %s %s %s",sAPN,sUser,sPwd);

  iRet = WirelessDial(sAPN,sUser,sPwd);
  printf("\nPPP Logon: %d",iRet);

  if (iRet!=0) {
    ScrCls();
    printf("\nLOGOUT...");
    while (1)
    {
      if (kbhit()==OK) {
        if (getkey()==KEYCANCEL) return 0;
      }
    }
  }
  // Attach End

  // Socket Start
  for (ii=0; ii<3; ii++)
  {
    int    iNCRet,iTemp,jj,iNSRet;
    uchar  ucTmpSend[300],ucTmpRcv[102400];

    struct net_sockaddr server_addr;

    iNSRet=NetSocket(NET_AF_INET, NET_SOCK_STREAM, 0);
    if (iNSRet < 0)
    {
      printf("\nNetSocket:%d", iNSRet);
      AppWaitKey(30);
      break;
    }

    SockAddrSet(&server_addr, sIP, ucPort);
    //SET timeout
    Netioctl(iNSRet, CMD_TO_SET, 55000);

    iNCRet=NetConnect(iNSRet,&server_addr,sizeof(server_addr));
    printf("\nTCP OPEN %s:%u =%d",sIP,ucPort,iNCRet);

    if (iNCRet<0)
    {
      printf("\nSocket close");
      NetCloseSocket(iNSRet);
      AppWaitKey(30);
      break;
    }
    // Socket End

    // Send Start
    memset(ucTmpSend, 0, sizeof(ucTmpSend));
    for (jj=0;jj<iSize;jj++) ucTmpSend[jj]=(unsigned char )(jj);
    iNCRet=NetSend(iNSRet,ucTmpSend,iSize,0);
    printf("\nTCP Send:%d ", iNCRet);

    if (iNCRet<0)
    {
      printf("\nSocket close");
      NetCloseSocket(iNSRet);
      AppWaitKey(30);
      break;
    }
    iTemp = 0;
    iTimeoutNum = 0;
    memset(ucTmpRcv, 0, sizeof(ucTmpRcv));

    while (1) {
      iNCRet=NetRecv(iNSRet,ucTmpRcv+iTemp,10*1000,0);
      if (iNCRet<0) {
        if (iNCRet==-13) {
          iTimeoutNum++;
          if (iTimeoutNum<3)
            continue;
          else
            break;
        }
        else//-4
          break;

        break;
      }


      iTemp+=iNCRet;
      if (iTemp>=iSize) break;

      if (kbhit()==0) {
        if (getkey()==KEYCANCEL) break;
      }
    }

    // Send End
    printf("\nTCP Recv:%d Rlen:%d ",iNCRet,iTemp);
    NetCloseSocket(iNSRet);
    WlPppLogout();
    break;
  }
  printf("\n ANY KEY CONTINUE");
  kbflush();getkey();

  return 0;
}

int WirelessDial(uchar *sAPN,uchar *sUser,uchar *sPwd)
{
  int ii,iRet,iTimeoutNum;

  iTimeoutNum = 0;
  do {
    iTimeoutNum++;
    for (ii=0;ii<3;ii++)
    {
      printf("\nPppLogin");
      WlPppLogin(sAPN,sUser,sPwd,0xff,0,0);
      DelayMs(2000);

      while (WlPppCheck()==1)
      {
        iRet = FAIL;
        printf("\nkbhit() OK");
        if (kbhit()==OK)
        {
          printf("\ngetkey() KEYCANCEL");
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
        printf("\nWlPppCheck Success");
        iRet = OK;
        break;
      }
      printf("\nPPP Logon time:%d",ii);
    }

    if (iRet !=0 && iTimeoutNum ==1)
    {
      printf("\nWlSwitchPower!");
      WlSwitchPower(0);
      DelayMs(10*1000);
      WlSwitchPower(1);
      printf("\nWlSwitchPower finish");
    }
  } while (iRet != 0 && iTimeoutNum == 1);

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