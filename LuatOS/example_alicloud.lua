-- LuaTools需要PROJECT和VERSION这两个信息
PROJECT = "led"
VERSION = "1.0.0"

-- 引入必要的库文件(lua编写), 内部库不需要require
sys = require("sys")

log.info("main", "led")

print(_VERSION)

-- if wdt then
--     --添加硬狗防止程序卡死，在支持的设备上启用这个功能
--     wdt.init(9000)--初始化watchdog设置为9s
--     sys.timerLoopStart(wdt.feed, 3000)--3s喂一次狗
-- end

--用户代码开始---------------------------------------------------
--根据自己阿里云物联网平台的配置修改以下参数，下列参数仅作参考
local mqtt_host = "a1ZR8uuCkfP.iot-as-mqtt.cn-shanghai.aliyuncs.com"
local mqtt_port = 1883  
local mqtt_isssl = false
local client_id = "a1ZR8uuCkfP.air780e_test|securemode=2,signmethod=hmacsha256,timestamp=1681048410186|"
local user_name = "air780e_test&a1ZR81132134"
local password = "9b075c78b1a600065d28afa0d3b42www.funiot.xy&&www.funiot.xyz"
local mqtt_aliyun = nil
local devdata_topic="/sys/a1ZR8uuCkfP/air780e_test/thing/event/property/post" --订阅属性上报主题
local cmdrec_topic="/sys/a1ZR8uuCkfP/air780e_test/thing/service/property/set" --订阅属性设置主题
local dev_control="thing.service.property.set"   --订阅属性控制下发主题
local command_name="LED_Control"            --控制命令
local LED_PIN=27                        	--LED引脚编号
gpio.setup(LED_PIN,0, gpio.PULLUP)      	--设置LED上拉输出

sys.taskInit(function()
    print("connected to aliyun example\r\n")
    while 1 do
        --网络相关
        mobile.simid(2)
        LED = gpio.setup(27, 0, gpio.PULLUP)
        device_id = mobile.imei()
        sys.waitUntil("IP_READY", 30000)
        --mqtt客户端创建
        mqtt_aliyun = mqtt.create(nil,mqtt_host, mqtt_port, mqtt_isssl, ca_file)
        mqtt_aliyun:auth(client_id,user_name,password) 
        mqtt_aliyun:keepalive(60) -- 默认值240s
        mqtt_aliyun:autoreconn(true, 3000) -- 自动重连机制
        --注册mqtt回调
        mqtt_aliyun:on(function(mqtt_client, event, data, payload)
            -- 用户自定义代码
            log.info("mqtt", "event", event, mqtt_client, data, payload)
            if event == "conack" then   --连接响应成功
                sys.publish("mqtt_conack")--订阅主题
                mqtt_client:subscribe(pub_devdata_topic)
                mqtt_client:subscribe(pub_cmdrec_topic)
            elseif event == "recv" then
                log.info("mqtt", "downlink", "topic", data, "payload", payload)
                print("payload:",payload)
                --解析json
                --例如：
                --{"method":"thing.service.property.set","id":"273481693","params":{"LED_Control":1},"version":"1.0.0"}
                local mycmd=json.decode(payload)
                if mycmd then -- 若解码失败, 会返回nil
                    print("method :",mycmd["method"])
                    print("params is",mycmd["params"])
                    print("params->LED_Control is",mycmd["params"]["LED_Control"])
                    if mycmd["method"]==dev_control then
                        if  mycmd["params"]["LED_Control"]==1 then
                            print("led turn on")
                            gpio.set(LED_PIN, gpio.HIGH)
                        elseif mycmd["params"]["LED_Control"]==0 then
                            print("led turn off")
                            gpio.set(LED_PIN, gpio.LOW)
                        end
                    end            
                end 
            elseif event == "sent" then
                log.info("mqtt", "sent", "pkgid", data)
            -- elseif event == "disconnect" then
                -- 非自动重连时,按需重启mqtt_aliyun
                -- mqtt_client:connect()
            end
        end)
        --连接mqtt
        mqtt_aliyun:connect()
        sys.waitUntil("mqtt_conack")
        while true do
            -- mqtt_aliyun自动处理重连
            local ret, topic, data, qos = sys.waitUntil("mqtt_pub", 30000)
            if ret then
                if topic == "close" then break end
                mqtt_aliyun:publish(topic, data, qos)
            end
        end
        mqtt_aliyun:close()
        mqtt_aliyun = nil 
    end       
end)
--定时上报属性
sys.taskInit(function()
	local topic = devdata_topic --上报的topic
    local temp=0    --温度属性值
    local data = "{\"method\":\"thing.service.property.set\",\"params\":{\"IndoorTemperature\":"..tostring(temp).."}}"
	local qos = 1
    local temp=0
    while true do
        sys.wait(5000)
        if mqtt_aliyun and mqtt_aliyun:ready() then
			-- mqtt_aliyun:subscribe(topic)
            local pkgid = mqtt_aliyun:publish(topic, data, qos)
            temp=temp+1
            data = "{\"method\":\"thing.service.property.set\",\"params\":{\"IndoorTemperature\":"..tostring(temp).."}}"
            print(data)
            -- 也可以通过sys.publish发布到指定task去
            -- sys.publish("mqtt_pub", topic, data, qos)
        end
    end
end)

-- 用户代码已结束---------------------------------------------
-- 结尾总是这一句
sys.run()
-- sys.run()之后后面不要加任何语句!!!!!

