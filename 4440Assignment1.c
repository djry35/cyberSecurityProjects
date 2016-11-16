#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
	static char a[100] = "abc";
	
	FILE* fp = fopen("a.out", "rb");

	fseek(fp, 0, SEEK_END);

	size_t bytes = ftell(fp);
		
	void* buffer = malloc(bytes);
	
	fseek(fp, 0, SEEK_SET); 

	fread(buffer, bytes, 1, fp);

	void* ptr = buffer + 0x10a0;
	
	*((char*)(ptr)) = 0x80;
	*((char*)(ptr+1)) = 0x80;
	*((char*)(ptr+2)) = 0x80;
	
	fseek(fp, 0, SEEK_SET);	

	FILE* fp2 = fopen("tmp", "wb");

	fwrite(buffer, bytes, 1, fp2);
	
	fclose(fp2);	
	fclose(fp);
	
	system("rm a.out");
		
	system("chmod 777 tmp");

	system("mv tmp a.out");

	free(buffer);

	if(a[0] != 'a')
	{
		printf("modified\n");
	}
	else
	{
		printf("normal.\n");
	}
	return 0;
}
