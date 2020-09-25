from multiprocessing import Process
import pyaudio
import numpy as np
import asr_json
import pygame
# 子进程要执行的代码

def ones():
    CHUNK = 512
    FORMAT = pyaudio.paInt16
    CHANNELS = 1
    RATE = 16000
    RECORD_SECONDS = 0.5#检查长度
    p = pyaudio.PyAudio()
    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)
    frames = []
    bool_recording=False
    count_no_audio=0
    while(True):
        data = stream.read(CHUNK)
#        print(data)
        if(bool_recording):
            frames.append(data)
        audio_data = np.frombuffer(data, dtype=np.short)
        temp = np.max(audio_data)
        if temp > 2000 and bool_recording==False:
            print("检测到信号")
            print('当前阈值：',temp)
            bool_recording=True
            count_no_audio=0
        if temp < 2000 and bool_recording==True:
            count_no_audio+=1
            
        if count_no_audio>=int((RATE / CHUNK) * RECORD_SECONDS) and bool_recording==True:#正在录制，且连续0.5秒无声音，截断
            bool_recording=False
            break
    
    stream.stop_stream()
    stream.close()
    p.terminate()
    return b"".join(frames)

def music_play(namelist,song_id,play_flag=False):
    pygame.mixer.init()
    is_play=False
    while(True):
        if play_flag:
            result_str="开始"
        else:
            t=ones()
            result_str=asr_json.asr(t)
        print(result_str)
        if result_str != None:
            if ("开始" in result_str or "开" or "播" or "放" in result_str) and is_play==False:#这里用is_play控制是因为要区分开始和继续的“播放”
                is_play=True
                pygame.mixer.music.load(namelist[song_id%len(namelist)])
                pygame.mixer.music.play()
            elif "停" in result_str or "结束" in result_str or "止" in result_str:
                if "暂" in result_str:
                    pygame.mixer.music.pause()
                else:
                    pygame.mixer.music.stop()
                    is_play=False
                    break
            elif "继续" in result_str and is_play==True:
                pygame.mixer.music.unpause()
            elif "下" in result_str:
                pygame.mixer.music.stop()
                song_id+=1
                pygame.mixer.music.load(namelist[song_id%len(namelist)])
                pygame.mixer.music.play()
            elif "上" in result_str:
                pygame.mixer.music.stop()
                song_id+=1
                pygame.mixer.music.load(namelist[song_id%len(namelist)])
                pygame.mixer.music.play()
        result_str=""
        
def get_luyin_str():
    return asr_json.asr(ones())
    
if __name__=="__main__":
    music_play(['1.wav','2.mp3'],0,False)