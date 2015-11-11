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
