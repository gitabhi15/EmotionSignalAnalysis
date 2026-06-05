from data_record_logging import logger

def main():
    print("=== SESSION RECORDING ===")
    
    emotion_label = input("Please enter the emotion to be recorded during the session: ").strip()

    serial_port = '/dev/ttyUSB0'
    print(f"Session recording starting for {emotion_label}")

    log = logger(port=serial_port)
    log.record_logging(emotion_label)

    if __name__ == "__main__":
        main()
