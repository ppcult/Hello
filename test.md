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
	int fd;
	struct i2c_rdwr_ioctl_data e2prom_data;
	/*1、打开通用设备文件*/
	fd = open("/dev/i2c-0",O_RDWR);

	e2prom_data.msgs = (struct i2c_msg*)malloc(2 * sizeof(struct i2c_msg));

	/*2、构造写数据到eeprom的消息*/
	e2prom_data.nmsgs = 1; /*1条消息*/
	e2prom_data.msgs[0].len = 2; /*写入两个字节*/
	e2prom_data.msgs[0].addr = 0x50;  /*不要带读写方向位*/
	e2prom_data.msgs[0].flags = 0;/*表示写*/
	e2prom_data.msgs[0].buf = (unsigned char *)malloc(2);/*分配两个字节的空间*/
	e2prom_data.msgs[0].buf[0] = 0x10;
	e2prom_data.msgs[0].buf[1] = 0x60;

	/*3、使用ioctl写入数据*/
	ioctl(fd, I2C_RDWR, (unsigned long)&e2prom_data); /*传进去的必须是一个地址*/

	/*4、构造从eeprom读数据的消息*/
	/*需要构造的消息是两条*/
	e2prom_data.nmsgs = 2; /*2条消息 第一条写 第二天读*/
	e2prom_data.msgs[0].len = 1; /*写入两个字节 偏移地址*/
	e2prom_data.msgs[0].addr = 0x50;  /*不要带读写方向位*/
	e2prom_data.msgs[0].flags = 0;/*表示写*/
	e2prom_data.msgs[0].buf[0] = 0x10;

	e2prom_data.msgs[1].len = 1; /*写入两个字节 偏移地址*/
	e2prom_data.msgs[1].addr = 0x50;  /*不要带读写方向位*/
	e2prom_data.msgs[1].flags = 1;/*表示写*/
	e2prom_data.msgs[1].buf = (unsigned char *)malloc(2);/*分配两个字节的空间*/	
	e2prom_data.msgs[1].buf[0] = 0;

	/*5、使用ioctl读出数据*/
	ioctl(fd, I2C_RDWR, (unsigned long)&e2prom_data);

	printf("buf[0] = %x\n", e2prom_data.msgs[1].buf[0]);
	/*6、关闭设备*/
	close(fd);

	return 0;
}