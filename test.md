#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>

#define I2C_RDWR	0x0707	/* Combined R/W transfer (one STOP only) */

struct i2c_msg {
	unsigned short addr;	/* slave address			*/
	unsigned short flags;
	unsigned short len;		/* msg length				*/
	unsigned char *buf;		/* pointer to msg data			*/
};

struct i2c_rdwr_ioctl_data {
	struct i2c_msg *msgs;	/* pointers to i2c_msgs */
	unsigned int nmsgs;			/* number of i2c_msgs */
};

int main()
{

}