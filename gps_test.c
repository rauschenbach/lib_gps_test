#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <gps.h>
#include "utils.h"

#define HOSTNAME	"localhost"
#define PORTNUM		"2947"

void main()
{
    struct gps_data_t gps_data;
    char str[128];
    int t0, t1 = 0;
    float frac;
    int ret;

    ret = gps_open(HOSTNAME, PORTNUM, &gps_data);

    (void) gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

    while (1) {

	/* Put this in a loop with a call to a high resolution sleep () in it. */
	if (gps_waiting(&gps_data, 5)) {
	    errno = 0;

	    if (gps_read(&gps_data) == -1) {
		printf("GPS read data error\n");
	    } else {

		/* Display data from the GPS receiver. */
		if (gps_data.set & TIME_SET) {
		    t0 = (int) gps_data.fix.time;
		    frac = gps_data.fix.time - t0;
		    sec_to_str(t0, str);
		    if (t0 != t1) {
			printf("%s.%f: fix: %d, sat: %d\n", str, frac, gps_data.status, gps_data.satellites_used);
			t1 = t0;
		    }
		}
	    }
	}
    }
    /* When you are done... */
    (void) gps_stream(&gps_data, WATCH_DISABLE, NULL);
    (void) gps_close(&gps_data);
}
