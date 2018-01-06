# IP地址信息查询服务

ipdesc 程序基于GPL v3发布。

本查询服务使用 http://ipip.net 提供的IP地址数据库免费版, 感谢北京天特信科技有限公司([http://ipip.net](http://ipip.net))。

特点：

* 使用DPDK 框架，无限连接数

演示站点（请单击如下URL测试）：

* 帮助信息 [http://210.45.224.10:90/help](http://210.45.224.10:90/help)
* 本机IP信息 [http://210.45.224.10:90/](http://210.45.224.10:90/) IPv6: [http://[2001:da8:d800:300::10]:90/](http://[2001:da8:d800:300::10]:90/)
* 查询IP信息 [http://210.45.224.10:90/202.38.64.1](http://210.45.224.10:90/202.38.64.1) IPv6: [http://[2001:da8:d800:300::10]:90/202.38.64.1](http://[2001:da8:d800:300::10]:90/202.38.64.1)

## 独立进程运行

```
cd /usr/src
git clone https://github.com/bg6cq/ipdesc-dpdk
cd ipdesc-dpdk
git submodule update --checkout
source env_vars
make

自行下载 http://ipip.net 的免费版 17monipdb.dat

#运行
build/ipdesc-dpdk -c1 -n1 x.x.x.x 80 
```

