# 新字符设备驱动

## 基础：之前的老字符设备驱动

## 1、创建硬件设备私有数据

- 创建一个结构体，将设备的属性，如主设备号(dev_t)、类(class)、设备(device)、开关状态(state)等等

  ```c
  /* newchrled结构体 */
  struct newchr{
      dev_t devid;             //设备号
      struct cdev cdev;        //cdev
      struct class *class;     //class
      struct device *device;   //device
      int major;				//主设备号
      int minor;  			//次设备号
  };
  struct newchr newchrled;
  ```

- 在open函数里设置结构体为私有数据，使用write、read、close等函数中直接读取private_data即可得到设备结构体（之前open函数里没东西）

  ```c
  static int new_led_open (struct inode *inode, struct file *file)
  {
      file->private_data = &newchrled; //设置私有数据
      return 0;
  }
  ```

  

## 2、自动分配和释放设备号

- 设备属性结构体中有`dev_t devid; int major; int minor`三个成员，为设备号，主设备号，次设备号，在驱动入口函数中配置玩led之后使用如下代码获取设备号：

  ```c
  if(newchrled.major) {
          newchrled.devid = MKDEV(newchrled.major, 0);
          register_chrdev_region(newchrled.devid, NEWCHR_CNT, NEWCHR_NAME);
      }else {
          alloc_chrdev_region(&newchrled.devid, 0, NEWCHR_CNT, NEWCHR_NAME);
          newchrled.major = MAJOR(newchrled.devid);
          newchrled.minor = MINOR(newchrled.devid);
      }
      printk("major is :%d,minor is:%d\r\n",newchrled.major,newchrled.minor);
  ```

- 申请设备号之后要在驱动出口函数中注销设备号：

  ```c
  unregister_chrdev_region(newchrled.devid,1);  //注销设备号
  ```

## 3、新字符设备注册和注销方法

- 在设备属性结构体中有`struct cdev cdev`结构体，内容如下：

  ```c
  struct cdev {
  	struct kobject kobj;
  	struct module *owner;
  	const struct file_operations *ops;
  	struct list_head list;
  	dev_t dev;
  	unsigned int count;
  };
  ```

  可见里面有一个dev_t结构体，此处先用以上的方法创建设备号

- 初始化cdev结构体并添加一个cdev

  ```c
  /* 初始化cdev结构体 */
      newchrled.cdev.owner = THIS_MODULE;
      cdev_init(&newchrled.cdev, &new_led_fops);
  
      /* 添加一个cdev */
      cdev_add(&newchrled.cdev,newchrled.devid,NEWCHR_CNT);
  ```

  此时就完成了设备的注册

- 注销字符设备

  ```c
   cdev_del(&newchrled.cdev);  //删除cdev
  ```

## 4、自动创建设备节点

- 在设备属性结构体中有`struct class *class;      struct device *device; `结构体

  ```c
  /* 创建类 */
      newchrled.class = class_create(THIS_MODULE, NEWCHR_NAME);
      if (IS_ERR(newchrled.class)) {
          return PTR_ERR(newchrled.class);
      }
      /* 创建设备 */
      newchrled.device = device_create(newchrled.class, NULL, newchrled.devid,NULL, NEWCHR_NAME);
      if(IS_ERR(newchrled.device)){
          return PTR_ERR(newchrled.device);
      }
  ```

- 删除类删除设备

  ```c
  /* 删除设备 */
      device_destroy(newchrled.class, newchrled.devid);
      /* 删除类 */
      class_destroy(newchrled.class);
  ```

  以上，即可在加载模块的时候自动创建设备节点，具体函数细节可查文档