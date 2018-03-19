# IP地址信息查询服务

ipdesc 程序基于GPL v3发布。

本查询服务使用 http://ipip.net 提供的IP地址数据库免费版, 感谢北京天特信科技有限公司([http://ipip.net](http://ipip.net))。

特点：

* 使用DPDK 框架，无限连接数
* 支持IPv4/IPv6

演示站点（请单击如下URL测试）：

* 帮助信息 [http://222.195.81.233/help](http://222.195.81.233/help)
* 本机IP信息 [http://222.195.81.233/](http://222.195.81.233/) 
* 查询IP信息 [http://222.195.81.233/202.38.64.1](http://222.195.81.233/202.38.64.1)

## 编译和运行

请首先参照 [https://github.com/bg6cq/dpdk-simple-web](https://github.com/bg6cq/dpdk-simple-web)准备好DPDK环境

```
cd /usr/src
git clone https://github.com/bg6cq/ipdesc-dpdk
cd ipdesc-dpdk
git submodule init
git submodule update --checkout
source env_vars
make

自行下载 http://ipip.net 的免费版 17monipdb.datx

#运行
build/ipdesc-dpdk -c1 -n1 x.x.x.x 80 [ --ip6 x:x:x::y ]
```

