DTS,DTB,DTC关系：

DTS为设备数源码文件，DTB为将DTS编译成的二进制文件，DTC为编译过程用到的工具

# imx6ull节点包含关系：

/ 根节点

- aliases节点（定义节点别名，类似于&lable）
- chosen节点（不是真实设备，为了uboot向linux传递数据）

- cpus节点
  - cpu0
  - cpu1...
- soc节点（SOC内部外设）
  - aips1节点（imx6ull内部分为三个域，分管不同外设控制器）
  - aips2节点
  - aips3节点

## 设备树要点：

- 节点定义
- 属性作用
- 绑定信息文档
- 常用of函数

## 设备树常用of函数：

### 查找节点的of函数：

linux内核使用<u>**device_node**</u>结构体描述一个节点，在include/linux/of.h中

of_find_node_by_name()	通过节点名字查找指定节点

of_find_node_by_type()	通过节点对应的type字符串，也就是device_type属性值查找

of_find_compatible_node()	通过device_type和compatible两个属性值查找节点

of_find_matching_node_and_match()	通过of_device_id匹配表查找

of_find_node_by_path()	通过路径查找

### 查找父/子节点的of函数：

of_get_parent()	获取指定节点的父节点

of_get_next_child()	从指定子节点开始查找下一个子节点

### 提取属性值的of函数：

linux使用<u>**property**</u>结构体表示节点里面的属性值，在include/linux/of.h中

of_find_property()	查找指定属性

of_property_count_elems_of_size()	获取属性中元素的数量

of_property_read_u32_index()	从属性中获取指定标号的u32类型数据值

of_property_read_u8_array() 函数
of_property_read_u16_array() 函数
of_property_read_u32_array() 函数
of_property_read_u64_array() 函数

以上四个获取属性中u8，u16，u32，u64类型的数组数据

of_property_read_u8() 函数
of_property_read_u16() 函数
of_property_read_u32() 函数
of_property_read_u64() 函数

有些属性只有一个整形值，以上四个函数用于读取这种只有一个整形值的属性

of_property_read_string()	用于读取属性中字符串值

of_n_addr_cells()	用于获取#address-cells属性值

of_n_size_cells()	获取#size-cells属性值

### 其他常用of函数:

of_device_is_compatible()	查看节点的compatible属性是否包含compat指定的字符串，即检查设备节点的兼容性

of_get_address()	获取地址相关属性，主要是“reg”或者“assigned-addresses”属性值

of_translate_address()	将从设备树读取到的地址转换为物理地址

of_address_to_resource()	将reg属性值转换为resource结构体类型的资源值

of_iomap()	直接将reg属性中的内存地址映射为虚拟地址

