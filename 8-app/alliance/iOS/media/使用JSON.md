## 使用JSON

JSON的相关实现大致在以下几个地方：

* RBJSON，类似[SwiftyJSON](https://github.com/SwiftyJSON/SwiftyJSON)的实现
* RBJSONMappable，类似[ObjectMapper](https://github.com/Hearst-DD/ObjectMapper)的实现
* RBHTTPSession-JSON，RBHTTPSession的扩展，方便请求JSON数据
* RXRapi，通过RAPI获取JSON数据

#### RBJSON

RBJSON可以简化JSON结构中指定数据的读取

	if let userName = json[0]["wrong_key"]["wrong_name"].string {
	} else {
		// 错误处理
	}
	
不需要关心中间某个结构是否存在或者正确，比如即使不存在wrong_key这个key或者其值不是object类型，代码依然可以正确运行，只是userName值会为nil。

关键实现是subscript，如果没有对应的值就返回.null，之后继续subscript都会返回.null。

与SwiftyJSON不同的是RBJSON使用枚举类型，对应JSON中定义的数据类型，在构造时会逐级遍历整个object结构，生成完整的RBJSON。

主要的构造函数: 

	public init(object: Any) throws
	
需要注意的是：

* init(object: Any)中，没有处理所有的NSNumber类型，不是JSONSerialization.jsonObject(with:)产生的object，尽量不要转化成RBJSON
* 没有区分null和undefined
* 构造时会马上递归解析整个object，.object方法也会递归整个JSON生成object，对于比较复杂的数据，可能有效率问题

#### RBJSONMappable

RBJSONMappable用来把RBJSON转换成实现该协议的实例。在实现中RBJSON和ObjectMapper中的Map类有些类似，只是不支持mappable类实例转换成RBJSON实例。

为Bool、Int、Double、String、Array、Dictionary类型实现了RBJSONMappable协议，Swift还不支持为泛型类的部分类型扩展某协议，所以所有Array和Dictionary类型在语法上都支持RBJSONMappable协议，只是Element不支持RBJSONMappable时抛出异常。

同时也定义了`<-`和`<--`操作符：`<-`主要用于非集合类型，并且，当左操作符是非可选类型或者隐式可选类型，如果map失败就会抛出异常，对于可选类型，如果失败只是设为nil；`<--`主要用于集合类型，几乎不会抛出异常，并且总是设置有效值，即便左操作符是可选类型。

对于集合类型`<-`和`<--`还有一点不同，`<-`遇到任何错误都会终止解析并抛出异常，`<--`遇到错误会跳过，继续解析，如果所有元素都错误也不会抛出异常。

#### RBHTTPSession-JSON 和 RXRapi

见代码中注释

#### 实践

对于需要频繁使用的结构定义enum、struct或者class，实现RBJSONMappable协议；如果是struct或者class，**对于必需的成员，使用隐式可选类型(`<-`会抛出异常)，可选的成员使用可选类型(`<--`不会抛出异常)**，`<-`和`<--`的左操作数都不能是未经初始化的变量，这样不需要写额外的构造函数。

不需要频繁使用的变量直接使用RBJSON读取即可。

RBHTTPSession-JSON中的fetchJSON和fetchMappableJSON，如果没有得到JSON就会返回错误，RXRapi中不同，如果没有得到JSON会返回.null。

