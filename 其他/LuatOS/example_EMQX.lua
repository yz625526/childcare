PROJECT = "SYS"
VERSION = "1.0.0"

sys = require("sys")
sysplus = require("sysplus")

local mqtt_host = "lc400116.ala.cn-hangzhou.emqxsl.cn"
local mqtt_port = 8883
local mqtt_isssl = true
local client_id = "AIR780EG-01"
local user_name = "air780"
local password = "12345"

local mqtt_pub_topic = "GPS_Track"

sys.taskInit(function() -- 联网函数（只运行一次
    local device_id = mcu.unique_id():toHex()
    device_id = mobile.imei() -- 获取设备IMEI
    sys.waitUntil("IP_READY") -- 默认都等到联网成功
    sys.publish("AIR780_power_on") -- 表示air780算开机完成
end)

sys.taskInit(function() -- 串口等各类硬件初始化
    sys.waitUntil("AIR780_power_on") -- 默认都等到联网成功
    local device_id = mcu.unique_id():toHex()
    log.info("unique_id:" .. device_id)
    device_id = mobile.imei()
    log.info("IMEI" .. device_id)

    mqtt_air780 = mqtt.create(nil, mqtt_host, mqtt_port, mqtt_isssl, true) -- 创建一个mqtt实例
    -- 创建mqtt实例
    mqtt_air780:autoreconn(true, 3000) -- 配置自动重连
    mqtt_air780:auth(client_id, user_name, password) -- 配置MQTT验证信息
    mqtt_air780:on(function(mqtt_client, event, data, payload) -- 配置mqtt回调函数
        -- log.info("mqtt", "状态", event, mqtt_client, data, payload)
        log.info("mqtt", "状态", event)
        -- if event == "conack" then -- 连接成功
        -- log.info("连接成功")
        sys.publish("mqtt_conack") -- 向sys公用信箱发送消息链接成功
        -- mqtt_client:subscribe(sub_topic) -- 单主题订阅
        -- mqtt_client:subscribe({[topic1]=1,[topic2]=1,[topic3]=1})--多主题订阅

        -- elseif event == "recv" then -- 下发数据了，event状态为recv
        --     log.info("mqtt", "downlink", "topic", data, "payload", payload)
        --     sys.publish("mqtt_payload", data, payload) -- 把下发的数据和业务数据存到mqtt_payload主题内

        if event == "sent" then -- 发送完成
            log.info("发送完成")
            -- log.info("mqtt", "sent", "pkgid", data)
            -- elseif event == "disconnect" then
            -- 非自动重连时,按需重启mqttc
            -- mqtt_client:connect()
        end
    end)
    sys.wait(1000)
    mqtt_air780:connect() -- 发起连接服务器
    sys.waitUntil("mqtt_conack") -- 等待上面event状态为conack才会解除
    log.info("MQTT初始化和连接完成")

    uart.setup(1, 115200, 8, 1, uart.None)
    uart.on(1, "receive", function(id, len) -- 串口回调：接收收到的字符串
        local data = uart.read(id, len)
        log.info("UART_receive from " .. id, data)
        sys.publish("UART1_receive", data)
        local topic = mqtt_pub_topic
        log.info(topic, data)
        mqtt_air780:publish(topic, data)
    end)
    log.info("串口初始化")

    log.info("开机完成")
    topic = mqtt_pub_topic
    mqtt_air780:publish(topic, "初始化完成，开始正常运行")

end)

-- sys.taskInit(function() -- 串口接收

-- end)

-- sys.taskInit(function() -- 表示正在正常运行
--     while true do
--         log.info("AIR780EG", "running")
--         sys.wait(5000) -- 延时1秒，这段时间里可以运行其他代码
--     end
-- end)

sys.run()
