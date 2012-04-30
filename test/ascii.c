#include <stdio.h>

main()
	{
	int c;
	for(c = 0; c < 255; c++)
		printf("%d: %c\t", c, (char)c);
		if(c % 4 == 0 && c)
			printf("\n");
	}
