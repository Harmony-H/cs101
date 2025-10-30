include <stdio.h>

int main()
{
	char* names[]= {
		"IU",
		"IU LEE",
		"李知恩"
	};

	char* (*ptr)[3];
	ptr=&names;
	for(int i=0; i<3; i++) {
		printf("ptr[%d] = %s\n",i,*(*ptr+i));
	}
	return 0;
}