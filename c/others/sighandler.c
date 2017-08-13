#include <stdio.h>
#include <signal.h>

void sigproc(void);

void quitproc(void);

void sigkill(void);

main()
{
	signal(SIGINT, sigproc);
	signal(SIGQUIT, quitproc);
	signal(SIGKILL, sigkill);
	printf("ctrl-c disabled use ctrl-\\ to quit\n");
	for(;;); /* infinite loop */}

void sigproc()
{
	signal(SIGINT, sigproc); /*  */
	/* NOTE some versions of UNIX will reset signal to default
	   after each call. So for portability reset signal each time */

	printf("you have pressed ctrl-c \n");
}

void quitproc()
{
	printf("ctrl-\\ pressed to quit\n");
	exit(0); /* normal exit status */
}

void sigkill()
{
	printf("wow! That much? SIGKILL is here! Get out!\n");
	exit(0);
}
