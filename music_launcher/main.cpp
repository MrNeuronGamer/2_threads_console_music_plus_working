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
			std::ofstream Locate_cr;
			Locate_cr.open("loc.txt", std::ios_base::ate);

			for (size_t i = 0; (char)path[i] !='\0'; i++)
			{
				Locate_cr << (char)path[i];
			}
			Locate_cr << '\n';
			Locate_cr.close();

			std::ifstream Get_loc;
			Get_loc.open("loc.txt");

			char buffer[MAX_BUFF];
			memset(buffer, 0, MAX_BUFF);

			{

				size_t i = 0;
				while (Get_loc >> buffer[i])
				{
					i++;
				}
				
			}

			Get_loc.close();

			*(strrchr(buffer, '\\'))='\0';

			char sub_buf[] = "\\music\\ILikeItLikeThat.wav";
			strcat_s(buffer,MAX_BUFF, sub_buf);
			
			PlaySound(buffer, NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP
					
				
				

		}
		if (omp_get_thread_num() == 1)
		{
			std::cout << " enjoy your music!";
			int a = 0;
			std::cin >> a;
			std::cout << " I love you man!\n";
			std::cout << " this is your number + 45  -> " << a + 45 << std::endl;
		}

#pragma omp barrier
	}
	return 0;
}