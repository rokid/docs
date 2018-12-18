
# HTTPDNS

---

####  httpdns功能简介
    - 1: httpdns 是一款递归DNS服务，与权威DNS不同，HTTPDNS 并不具备决定解析结果的能力，而是主要负责解析过程的实现。
    - 2：使用 HTTP 协议访问阿里云或者华为云的服务端，获得域名解析结果，绕过运营商的 Local DNS ，避免域名劫持。
    - 3：httpdns 能够直接得到客户端的出口网关 IP，从而更准确地判断客户端地区和运营商，得到更精准的解析结果。
    - 4: httpdns 支持全网域名的解析，包括在阿里云（万网）注册的域名，和其它第三方的域名。
#### GSLB：Global Service Load Balance
    功能：
    实现对公司设备入口流量的多维度调度策略，满足多云流量调度、灰度测试流量调度等多种需求
####  使用httpdns解析域名
    - 使用httpdns解析域名，请求示例："https://gslb-dev.rokid.com/api/v1/?sn=dev_sn&devicetype=dev_tyep"

####  API响应格式

-  解析结果JSON格式示例如下：
```
{


	"code":0,
   	"msg":"Successfully!",
	"tag":"Huawei",
	"data":[
			{
				"host":"apigwws.open.rokid.com",
				"client_ip":"183.129.185.66",
				"ips":["119.3.1.49"]
			},
			{
				"host":"apigwrest.open.rokid.com",
				"client_ip":"183.129.185.66",
				"ips":["119.3.1.49"]
			}
	   ]
} 
```
- 请求失败

| 错误码|  错误信息  | 错误说明  |
|:----:|:----:|:----:|:------:|:------:|
| 400 | Invalid Request Method, POST and GET Supported Only| !!请求方法错误，目前仅支持GET和POST |
| 401 |Invalid Request Body, Json Supported Only !! | 请求体JSON解析出错 |
| 402 |SN and DeviceType Must Provided !! | 请求体JSON解析出错 |

#### C库提供的HTTPDNS 接口说明

        typedef struct
        {
            char  *h_name;
            char  **h_ips;
            int32_t ips_num;
        }host_ips;

        typedef struct
        {
            host_ips **host;
            int32_t host_num;
        }ips_list;

- typedef int (*httpdns_finished_notify)(int status, void *userdata);

| 2个返回值 |  类型  | 参数含义 | 数值说明 | 备注 |
|:----:|:----:|:----:|:------:|:------:|
| 返回值 | int | -1 失败， 0 成功 ||
| 参数 1 | status |char* | 请求httpdns 服务结果| |  |
| 参数 2 | userdata |void* |用户回调函数要处理的数据| |

- int32_t  httpdns_service_init();

| 0个参数 |  类型  | 参数含义 | 数值说明 | 备注 |
|:----:|:----:|:----:|:------:|:------:|
| 参数 |  | httpdns 使用curl初始化类型| CURL_GLOBAL_ALL |  |

- int32_t httpdns_service_destroy()

| 0个参数 |  类型  | 参数含义 | 数值说明 | 备注 |
|:----:|:----:|:----:|:------:|:------:|
| 参数 |  | httpdns使用的curl释放空间的线程 |    |    |

- int32_t httpdns_resolve_gslb(char *sn, char *device_type, int timeout_ms,httpdns_finished_notify cb,void *userdata);

| 2个参数 |  类型  | 参数含义 | 数值说明 | 备注 |
|:----:|:----:|:----:|:------:|:------:|
| 参数1 | sn  |设备sn 号|||
| 参数2 | device_type  |设备deviceypeID| |
| 参数3 | timeout_ms |请求超时时间(Millisecond| |
| 参数4 | cb |用户回调处理的函数，通知用户请求dns完成| |
| 参数5 | userdata |用户回调处理的数据| |
-int httpdns_getips_by_host(char *host_name, char *ip);

| 1个返回值 |  类型  | 参数含义 | 数值说明 | 备注 |
|:----:|:----:|:----:|:------:|:------:|
| 返回值 | int | -1 失败， 0 成功 ||
| 参数 1 | host_name |char* | 要查训的hostname| |  |
| 参数 2 | ip |char* |查询到对应ip 返回给该参数| |


- 测试代码以及实例
1. sample 目录下的测试文件httpdns_samplae.c
2. 测试方式,测试调用接口已经在测试代码写好，如果测试 host name 直接编译运行就行
3. make package/httpdns/insall -j1 V=s
4. ./httpdns_samplae


