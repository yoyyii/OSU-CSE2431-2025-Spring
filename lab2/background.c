#include <stdio.h>
#include <unistd.h>

int main() {
	while (1) {
		printf("in background now ");
		fflush(stdout);

		sleep(2);
	}
	return 0;
}
