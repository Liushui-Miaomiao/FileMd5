#include "FileMd5.h"

int main(void){
	SetConsoleTitleA("FileMd5");

	char* l_p_filePath = NULL;
	char* l_p_fileMd5 = NULL;

	while (TRUE) {
		l_p_filePath = NULL;
		l_p_fileMd5 = NULL;
		l_p_filePath = (char*)malloc(256);
		l_p_fileMd5 = (char*)malloc(32);
		if (!l_p_filePath || !l_p_fileMd5) {
			puts("Failed to allocate memory!");
			free(l_p_filePath);
			free(l_p_fileMd5);
			exit(EXIT_FAILURE);
		}

		printf("Please enter the file path:");
		gets_s(l_p_filePath, 255);

		if (!strcmp(l_p_filePath, "exit")) {
			free(l_p_filePath);
			free(l_p_fileMd5);
			break;
		}

		//Deal with double quotes.
		int l_len = strlen(l_p_filePath);
		if (l_p_filePath[l_len - 1] == '\"') {
			l_p_filePath[l_len - 1] = '\0';
		}
		if (l_p_filePath[0] == '\"') {
			strcpy_s(l_p_filePath, l_len, l_p_filePath + 1);
		}

		l_p_fileMd5 = GetFileMd5(l_p_filePath);

		if (l_p_fileMd5) {
			printf("Md5 Code:%s\n", l_p_fileMd5);

			if (!WriteClipboard(l_p_fileMd5)) {
				puts("Failed to write to clipboard!");
			}

			putchar('\n');
			continue;
		}

		puts("Failed to open file!");
	}

	return EXIT_SUCCESS;
}
