#include <windows.h>
#include <iostream>
#include <omp.h>
#include <fstream>

#pragma comment(lib, "winmm.lib")
#define MAX_BUFF (16*1024)


int main(int argc, char* argv[])
{
	omp_set_num_threads(2);
#pragma omp parallel
	{
#pragma omp master 
		{

			HMODULE hModule = GetModuleHandleW(NULL);
			WCHAR path[MAX_PATH];
			GetModuleFileNameW(hModule, path, MAX_PATH);
			char buffer[MAX_BUFF];
			memset(buffer, 0, MAX_BUFF);
			
			

			for (size_t i = 0; (char)path[i] !='\0'; i++)
			{
				buffer[i] = (char)path[i];
			}	
							

			*(strrchr(buffer, '\\'))='\0';

			char sub_buf[] = "\\music\\ILikeItLikeThat.wav";
			strcat_s(buffer,MAX_BUFF, sub_buf);
			
			PlaySound(buffer, NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP
					
				
				

		}
		if (omp_get_thread_num() == 1)
		{
			std::cout << " please enter any short int: \n";
			int a = 0;
			std::cin >> a;
			std::cout << " I love you man!\n";
			std::cout << " this is your number + 45  -> " << a + 45 << std::endl << "So, now just wait till music ends ^^\n";
		}

#pragma omp barrier
	}
	return 0;
}