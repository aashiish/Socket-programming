#include<winsock2.h>
#include<iostream>

using namespace std;
int main()
{

	cout<< "\t\t------TCP CLIENT-----" << endl;
	cout << endl;

	//Local variable
	WSADATA Winsockdata;
	int iWsaStartup;
	int iWsaCleanup;

	SOCKET  TCPClientSocket;
	int iCloseSocket;

	struct sockaddr_in TCPServerAdd;
	
	int iConnect;

	int iRecv;
	char RecvBuffer[512];
	int iRecvBuffer = strlen(RecvBuffer) + 1; 

	int iSend;
	char SenderBuffer[512] = "Hello from client!";
	int iSenderBuffer = strlen(SenderBuffer) + 1;


	//STEP-1 WSASTARTUP FUNCTION
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
	if (iWsaStartup != 0)
	{
		cout << "WSAStarup Failed" << endl;
	}
	else
		cout << "WSAStartup Success." << endl;


	//step- 2 Socket creation
	TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPClientSocket == INVALID_SOCKET)
	{
		cout << "TCP client creation failed" << WSAGetLastError() << endl;

	}
	cout << "TCP client creation successful" << endl;


	//STEP- 3 Fill the structure
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAdd.sin_port = htons(8000);

	//step- 4 Connect fun
	iConnect = connect(TCPClientSocket,(SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iConnect == INVALID_SOCKET)
	{
		cout << "TCP connection failed" << WSAGetLastError() << endl;
	}
	cout << "TCP connection successful" << endl;


	//STEP - 5 Recv Data from server
	iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR)
	{
		cout << "Receiving Failed & Error No-> " << WSAGetLastError() << endl;
	}
	cout << "DATA RECEIVED-> " << RecvBuffer << endl;


	//Step-6 Send Data to server
	iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
	if (iSend == SOCKET_ERROR)
	{
		cout << "Sending Failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Data Sending successful " << endl;

	//STEP-9 CLOSE SOCKET
	iCloseSocket = closesocket(TCPClientSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "Closing socket failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Socket closed successfully" << endl;

	//STEP-10 Cleanup from DLL
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR)
	{
		cout << "Cleanup fun failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Cleanup fun successful" << endl;

	system("PAUSE");
	return 0;

}