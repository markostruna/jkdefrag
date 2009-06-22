
#ifndef JKDEFRAG
#define JKDEFRAG

int Running = STOPPED;           /* If not RUNNING then stop defragging. */

int IamRunning;

/* Debug level.
	0: Fatal errors.
	1: Warning messages.
	2: General progress messages.
	3: Detailed progress messages.
	4: Detailed file information.
	5: Detailed gap-filling messages.
	6: Detailed gap-finding messages.
*/
int Debug = 1;

#endif