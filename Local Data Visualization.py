import paho.mqtt.client as mqtt
import datetime

broker = "m10.cloudmqtt.com"
port = 12038
user = "uthzmxvn"
pasw = "nDjWmfSZ-aUD"

def on_message(client, userdata, message):
    data = message.payload.decode('utf-8')
    time_now = datetime.datetime.now().strftime("%H:%M:%S")
    print(f"[{time_now}] Process Variable: {data}%")

client = mqtt.Client("PC_Subscriber_Main")
client.username_pw_set(user, password=pasw)
client.on_message = on_message

print(f"Connecting to {broker} on port {port}...")
client.connect(broker, port)
client.subscribe("GG")

try:
    client.loop_forever()
except KeyboardInterrupt:
    print("Session Ended.")
    client.disconnect()
