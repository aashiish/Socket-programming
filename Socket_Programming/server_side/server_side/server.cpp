#include<winsock2.h>
#include<iostream>

using namespace std;
int main()
{

	cout << "\t\t------TCP SERVER-----" << endl;
	cout << endl;

	//Local variable
	WSADATA Winsockdata;
	int iWsaStartup;
	int WsaCleanup;

	SOCKET   TCPServerSocket;
	int iCloseSocket;

	struct sockaddr_in TCPServerAdd;
	struct sockaddr_in TCPClientAdd;
	int iTCPClientAdd;
	int iTCPClientAdd = sizeof(TCPClientAdd);	
	
	int iBind;
	
	int iListen;
	
	SOCKET sAcceptSocket;

	int iSend;
	char SenderBuffer[512] = "Hello from server!";
	int iSenderBuffer = strlen(SenderBuffer) + 1;

	int iRecv;
	char RecvBuffer[512];
	int iRecvBuffer = strlen(RecvBuffer) + 1;


	//STEP-1 WSASTARTUP FUNCTION
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
	if (iWsaStartup != 0)
	{
		cout << "WSAStarup Failed" << endl;
	}
	else
		cout << "WSAStartup Success." << endl;

	//STEP- 2 Fill the structure
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAdd.sin_port = htons(8000);

	//step- 3 Socket creation
	TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPServerSocket == INVALID_SOCKET)
	{
		cout << "TCP serever  creation failed" << WSAGetLastError() << endl;

	}

	cout << "TCP server creation successful" << endl;

	//STEP - 4 Bind the socket
	iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iBind == SOCKET_ERROR)
	{
		cout << "Binding Failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Binding Success" << endl;

	//STEP-5 Listen request
	iListen = listen(TCPServerSocket, 2);
	if (iListen == SOCKET_ERROR)
	{
		cout << "Listening Failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Listening Success" << endl;


	//STEP-6 Accept request
	sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd,&iTCPClientAdd);
	if (sAcceptSocket == INVALID_SOCKET)
	{
		cout << "Accept Failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Connection accepted" << endl;

	//Step-7 Send Data to client
	iSend = send(sAcceptSocket, SenderBuffer,iSenderBuffer, 0);
	if (iSend == SOCKET_ERROR)
	{
		cout << "Sending Failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Data Sending successful "<< endl;

	//STEP - 8 Recv Data from Client
	iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR)
	{
		cout << "Receiving Failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "DATA RECEIVED-> "<<RecvBuffer << endl;

	//STEP-9 CLOSE SOCKET
	iCloseSocket = closesocket(TCPServerSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "Closing socket failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Socket closed successfully"<< endl;

	//STEP-10 Cleanup from DLL
	WsaCleanup = WSACleanup();
		if (WsaCleanup == SOCKET_ERROR)
	{
		cout << "Cleanup fun failed & Error No-> " << WSAGetLastError() << endl;

	}
	cout << "Cleanup fun successful"<< endl;

	system("PAUSE");
	return 0;



}