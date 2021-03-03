#include <stdio.h>
#include <stdlib.h>

void* bufferFile(const char* name){
	FILE* fp = fopen(name, "rb");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	printf("size %d\n", size);
	void* buffer  = malloc(size);
	if(buffer == NULL)
		return NULL;
	rewind(fp);
	fread(buffer, 1, size, fp);
	return buffer;
}

int main(int argc, char** argv){
	if(argc < 2)
		return 1;
	uint8_t* ROM = bufferFile(argv[1]);
	if(ROM){
		printf("%c\n", *ROM);
		free(ROM);
	}
	return 0;	
}
