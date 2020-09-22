import asr_json
import main_py
import serial

ser=serial.Serial("/dev/ttyAMA0",9600)
while True:
    t=main_py.ones()
    result_str=asr_json.asr(t)
    if "前" in result_str:
        ser.write(b'w')
    if "后" in result_str:
        ser.write(b's')
    if "左" in result_str:
        ser.write(b'a')
    if "右" in result_str:
        ser.write(b'd')
    if "停" in result_str:
        ser.write(b'x')
    if "开" in result_str or "始" in result_str:
        ser.write(b'c')
ser.close()