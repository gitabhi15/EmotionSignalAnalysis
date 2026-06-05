import numpy as np

def normalize(df):
    df_norm = df.copy()
    for col in ["gsr", "temp", "heart_rate"]:
        if col in df:
            mean = df[col].mean()
            std = df[col].std()
            df_norm[col] = (df[col] - mean) / std
    return df_norm

def clean(df):
    df = df.dropna()
    return df
