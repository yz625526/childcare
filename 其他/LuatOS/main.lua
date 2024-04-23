-- LuaTools需要PROJECT和VERSION这两个信息
PROJECT = "Ali_Uart"
VERSION = "1.0.0"

-- 引入必要的库文件(lua编写), 内部库不需要require
sys = require("sys")

-- 用户代码开始---------------------------------------------------
-- 根据自己阿里云物联网平台的配置修改以下参数，下列参数仅作参考
local mqtt_host = "a1C5FkKES9U.iot-as-mqtt.cn-shanghai.aliyuncs.com" -- 连接地址
local mqtt_port = 1883 -- 连接端口
local mqtt_isssl = false -- 1883端口表明未加密，不需要打开SSL
local client_id = "a1C5FkKES9U.Air780E|securemode=2,signmethod=hmacsha256,timestamp=1713678672972|"
local user_name = "Air780E&a1C5FkKES9U"
local password = "3431b1fb9a032873da8d3ea4423e25cf1593edbb113e07f1071a172dcc1723b1"
local devdata_topic = "/sys/a1C5FkKES9U/Air780E/thing/event/property/post" -- 订阅属性上报主题

local mqtt_pub_topic = "/sys/a1C5FkKES9U/Air780E/thing/event/property/post" -- 上报的topic

sys.taskInit(function() -- 联网函数（只运行一次
    local device_id = mcu.unique_id():toHex()
    device_id = mobile.imei() -- 获取设备IMEI
    sys.waitUntil("IP_READY") -- 默认都等到联网成功
    sys.publish("AIR780_power_on") -- 表示air780算开机完成
end)

sys.taskInit(function() -- 串口等各类硬件初始化
    sys.waitUntil("AIR780_power_on") -- 默认都等到联网成功

    mqtt_air780 = mqtt.create(nil, mqtt_host, mqtt_port, mqtt_isssl, ca_file)
    mqtt_air780:autoreconn(true, 3000) -- 自动重连机制
    mqtt_air780:auth(client_id, user_name, password)
    mqtt_air780:keepalive(60) -- 默认值240s
    mqtt_air780:on(function(mqtt_client, event, data, payload) -- 配置mqtt回调函数
        log.info("mqtt", "状态", event)
        sys.publish("mqtt_conack")
        if event == "sent" then -- 发送完成
            log.info("发送完成")
        end
    end)
    -- sys.wait(1000)
    mqtt_air780:connect() -- 发起连接服务器
    sys.waitUntil("mqtt_conack") -- 等待上面event状态为conack才会解除
    log.info("MQTT初始化和连接完成")

    uart.setup(1, 115200, 8, 1, uart.None)
    uart.on(1, "receive", function(id, len) -- 串口回调：接收收到的字符串
        local data = uart.read(id, len)
        tmp = string.split(data, ":")
        log.info("str.split", tmp[2])
        data = "{\"method\":\"thing.service.property.set\",\"params\":{\"" .. tostring(tmp[1]) .. "\":" ..tostring(tmp[2]) .. "}}"
        log.info("end-data", data)
        mqtt_air780:publish(mqtt_pub_topic, data, 1)
    end)
    log.info("串口初始化")
end)

sys.run()
