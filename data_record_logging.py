import csv
import time
import os
import serial

class logger:
    def __init__(self, port, baud_rate):
        self.port = port
        self.baud_rate = baud_rate
        self.ser = None
    
    def record_logging(self, emotion_label):
        os.makedirs("Data_Logs", exist_ok=True)
        filename = os.path.join("Data_logs", f"session_{time.strftime('%Y%m%d_%H%M%S')}_{emotion_label}.csv")

        try:
            self.ser = serial.Serial(self.port, self.baud_rate, timeout=1)
            time.sleep(2)

            with open(filename, mode='w', newline="") as file:
                writer = csv.writer(file)
                writer.writerow(["Timestamp", "Pulse", "GSR", "EMG", "Acc_X", "Acc_Y", "Acc_Z", "Label"])

                print("Sending command over to Arduino\n"f"Streaming data to {filename}")
                self.ser.write(b'SEND')

                while True:
                    if self.ser.in_waiting > 0:
                        line = self.ser.readline().decode('utf-8').strip()
                        data = line.split(",")

                        if len(data) == 6:
                            writer.writerow([time.time()] + data + [emotion_label])


        except KeyboardInterrupt:
            print("Session recording complete, sending command over to Arduino")
            if self.ser and self.ser.is_open:
                self.ser.write(b'END')
                self.ser.close()
