import pandas as pd

def load_csv(path):
    df = pd.read_csv("data/sample_data.csv")
    return df
