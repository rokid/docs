## 通过Let’s Encrypt获取免费的SSL证书
 
Skill开发过程中，其中第三步是是填写https的服务地址。目前，我们支持大多数的主流根证书颁发机构（CA）的证书（当然也许会有些遗漏，您可以在论坛上提醒我们），暂时还没有开放私有的证书，这个会在未来开放。当然，能理解的是，大多数的CA，因为认证和盈利需要，都需要网站所有者支付一笔费用，有些大型CA甚至需要支付不菲的费用。所以，对于个人开发者来说这确实是一个门槛，今天，我们推荐一个免费的CA:Let’s Encrypt6 ，我们开放平台支持该CA证书，这很适合个人开发者使用。
其实，Let’s Encryp官网有提供工具来生成证书，但是相对有些繁琐，这里使用一个很小的简便工具:acme-tiny9 来生成。生成过程我写了一个Shell脚本generate-letsencrypt-certificate.sh24，如果你不想了解其中的流程，可以直接Copy到你的服务器上执行，希望一切顺利后可以如愿获得证书。下面，我简单介绍一下脚本执行过程，当然不会很详尽，过程中如果遇到问题，请在帖子下面留言。

从github上获取脚本后:
```
root@test-29.dev.rokid-inc.com:~/ssl#chmod +x generate-letsencrypt-certificate.sh
root@test-29.dev.rokid-inc.com:~/ssl#./generate-letsencrypt-certificate.sh testssl.rokid.com
```
如果您本地已经监听了80端口的web服务，那么需要您输入web server的根目录:
```
please input web service ROOT path:/var/www
```
一切顺利的话，脚本执行完后本地会生成:
```
root@test-29.dev.rokid-inc.com:~/ssl# tree
.
├── account.key
├── acme_tiny.py
├── generate-letsencrypt-certificate.sh
├── intermediate.pem
├── testssl.rokid.com.crt
├── testssl.rokid.com.csr
├── testssl.rokid.com.key
└── testssl.rokid.com.pem
```
获得证书后，根据自己web server需要配置ssl证书即可，这里用nginx举例:
```
server {
    listen 443;
    server_name testssl.rokid.com;
    ssl on;
    ssl_certificate /path/to/testssl.rokid.com.pem;
    ssl_certificate_key /path/to/testssl.rokid.com.key;
    ssl_session_timeout 5m;
    ssl_protocols TLSv1 TLSv1.1 TLSv1.2;
    ssl_ciphers ECDHE-RSA-AES256-GCM-SHA384:ECDHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES128-SHA256:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA;
    ssl_session_cache shared:SSL:50m;
    ssl_prefer_server_ciphers on;
    ...the rest of your config
}
```
配置完成后，就可以顺利地通过第三部https的证书校验部分了。